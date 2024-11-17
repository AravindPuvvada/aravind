const int ldrPin = D1; 
int ldrValue = 0;     

void setup() {
  Serial.begin(115200); 
}

void loop() {
  ldrValue = analogRead(ldrPin); 

  // Print the LDR value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  delay(500); 
}
