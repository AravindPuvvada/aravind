int sensor=A0;
int relay=2;
int relay1=3;
int led=12;
void setup() {
pinMode(sensor,INPUT);
pinMode(relay,OUTPUT);
pinMode(relay1,OUTPUT);
pinMode(led,OUTPUT);
Serial.begin(9600);
}

void loop() {
 int value=analogRead(A0);
 Serial.print("value:");
 Serial.println(value);
 if(value<150)
 {
  digitalWrite(relay,HIGH);
  delay(1000);
  digitalWrite(relay,LOW);
  delay(1000);
 }
 else if(value>=150 && value<=500)
 {
  digitalWrite(relay1,HIGH);
  delay(500);
  digitalWrite(relay1,LOW);
  delay(500);
 }
 else
 {
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
 }delay(1000);
}
