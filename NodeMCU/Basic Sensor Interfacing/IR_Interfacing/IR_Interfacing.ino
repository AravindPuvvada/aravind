const int irSensorPin = D2; // Digital pin connected to the IR sensor
int sensorValue = 0;       // Variable to store the sensor value

void setup() {
  Serial.begin(115200);    // Initialize serial communication
  pinMode(irSensorPin, INPUT); // Set the pin mode to input
}

void loop() {
  sensorValue = digitalRead(irSensorPin); // Read the digital value from the IR sensor

  // Print the sensor value (HIGH or LOW)
  Serial.print("Sensor Value: ");
  if (sensorValue == LOW) {
    Serial.println("Obstacle detected");
  } else {
    Serial.println("No obstacle");
  }

  delay(500); // Wait for 0.5 seconds before the next reading
}
