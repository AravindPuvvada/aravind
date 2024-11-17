const int trigPin = D1; // GPIO pin connected to the TRIG pin of the ultrasonic sensor
const int echoPin = D2; // GPIO pin connected to the ECHO pin of the ultrasonic sensor

void setup() {
  Serial.begin(115200);    // Initialize serial communication
  pinMode(trigPin, OUTPUT); // Set TRIG pin as OUTPUT
  pinMode(echoPin, INPUT);  // Set ECHO pin as INPUT
}

void loop() {
  // Send a pulse to the TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse on the ECHO pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance = duration * 0.0344 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // Wait for 0.5 seconds before the next measurement
}
