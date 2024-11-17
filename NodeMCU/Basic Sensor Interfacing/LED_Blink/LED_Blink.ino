
const int relayPin = D2; // GPIO4 (D2) is connected to the relay

void setup() {
  // Start serial communication
  Serial.begin(115200);
  
  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
  
  // Initialize relay as OFF
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Turn relay ON
  digitalWrite(relayPin, HIGH);
  Serial.println("Relay ON");
  delay(2000); // Wait for 2 seconds

  // Turn relay OFF
  digitalWrite(relayPin, LOW);
  Serial.println("Relay OFF");
  delay(2000); // Wait for 2 seconds
}
