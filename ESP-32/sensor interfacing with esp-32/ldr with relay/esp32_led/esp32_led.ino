int relay=4;
int ldr=13;
void setup() {
pinMode(relay, OUTPUT);
digitalWrite(relay,LOW);
Serial.begin(9600);
}

void loop() {
  int value=analogRead(ldr);
  Serial.print("Ldr:");
  Serial.println(value);
  delay(1000);
  if(value>3000)
  {
  digitalWrite(relay, HIGH);
  delay(1000);
  }
  else
  {
  digitalWrite(relay, LOW);
  delay(1000);
  }
}
