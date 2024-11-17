int led=7;
void setup() {
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led,HIGH);
  delay(6000);
  digitalWrite(led,LOW);
  delay(4000);

}
