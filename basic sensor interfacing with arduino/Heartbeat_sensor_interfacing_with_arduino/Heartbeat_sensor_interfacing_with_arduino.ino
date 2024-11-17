int heart_beat=A0;
int value;
void setup() {
  Serial.begin(9600);
}

void loop() {
  value=analogRead(heart_beat);
  Serial.print("Heart-beat:");
  Serial.println(value);
  delay(1000);
}
