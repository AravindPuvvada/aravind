nt relay=2;
int sensor=A0;
void setup() {
  pinMode(relay,OUTPUT);
  pinMode(sensor,INPUT);
  Serial.begin(9600);
}

void loop() {
  int value=analogRead(A0);
  Serial.print("value:");
  Serial.println(value);
  if(value>200)
  {
    digitalWrite(relay,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(relay,LOW);
    delay(1000);
  }
}
