// Define pins
const int pirPin = 2;        // PIR sensor output pin
const int ledPin = 4;        // LED output pin
const int ldrPin = A0;       // LDR sensor analog pin

// Threshold for LDR
const int lightThreshold = 700;  // Adjust based on your lighting condition

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  int pirState = digitalRead(pirPin);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Check if it's dark (LDR reading is above threshold)
  if (ldrValue > lightThreshold) {
    // Check if motion is detected
    if (pirState == HIGH) {
      digitalWrite(ledPin, HIGH);  // Turn on the LED
      Serial.println("Motion detected - Light ON");
    } else {
      digitalWrite(ledPin, LOW);   // Turn off the LED
      Serial.println("No motion - Light OFF");
    }
  } else {
    // It's bright, so keep the light off
    digitalWrite(ledPin, LOW);
    Serial.println("It's bright - Light OFF");
  }

  delay(1000);  // Delay for stability
}
