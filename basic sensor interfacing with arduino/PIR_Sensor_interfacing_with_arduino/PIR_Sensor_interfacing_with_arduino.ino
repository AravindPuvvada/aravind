// Define pins
const int pirPin = 2;        // PIR sensor output pin
const int ledPin = 4;       // LED output pin (built-in LED on many Arduino boards)

void setup() {
  // Initialize the PIR sensor pin as an input
  pinMode(pirPin, INPUT);

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Start the serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {
  // Read the PIR sensor output
  int pirState = digitalRead(pirPin);

  // Print the PIR sensor state to the Serial Monitor
  Serial.print("PIR State: ");
  Serial.println(pirState);

  // If motion is detected, turn on the LED
  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion detected - LED ON");
  } else {
    // If no motion, turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("No motion - LED OFF");
  }

  // Small delay to avoid rapid flickering
  delay(1500);
}
