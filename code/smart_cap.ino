// Vision Beyond Sight - Smart Cap
// Arduino Uno, Ultrasonic Sensor, IR Sensor, Buzzer, Red LED

#define trigPin 9
#define echoPin 10
#define irPin 8
#define buzzer 7
#define redLED 6

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(redLED, LOW);

  Serial.begin(9600);
}

void loop() {
  // Read ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000UL);

  if (duration == 0) {
    distance = -1;
  } else {
    distance = duration * 0.034 / 2;
  }

  // Read IR sensor
  int irValue = digitalRead(irPin);

  // Display sensor readings
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | IR Sensor: ");
  Serial.println(irValue);

  // Detect obstacles within 50 cm
  bool ultrasonicObstacle =
      (distance > 0 && distance < 50);

  bool irObstacle = (irValue == LOW);

  bool obstacleDetected =
      ultrasonicObstacle || irObstacle;

  // Activate buzzer and red LED
  if (obstacleDetected) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(redLED, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(redLED, LOW);
  }

  delay(100);
}
