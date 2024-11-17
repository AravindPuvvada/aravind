int led=4;
int sw=13;
void setup() {
  pinMode(led,OUTPUT);
  pinMode(sw,INPUT);
}

void loop() {
  if(digitalRead(sw)==0)
  {
   digitalWrite(led,HIGH);
   delay(1000);
  }
  else
  {
  digitalWrite(led,LOW);
  delay(1000);
  }
}
