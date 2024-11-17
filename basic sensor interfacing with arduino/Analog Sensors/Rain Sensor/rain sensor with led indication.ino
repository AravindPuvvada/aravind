
int red=2;
int yellow=3;
int green=4;
void setup() {
pinMode(red,OUTPUT);
pinMode(yellow,OUTPUT);
pinMode(green,OUTPUT);
Serial.begin(9600);
}

void loop() {
 int value=analogRead(A0);
 Serial.print("value:");
 Serial.println(value);
 if(value<170)
 {
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
  digitalWrite(yellow,LOW);
  delay(1000);
 }
 else if(value>=170 && value<=550)
 {
  digitalWrite(yellow,HIGH);
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  delay(1000);
 }
 else
 {
  digitalWrite(green,HIGH);
  digitalWrite(yellow,LOW);
  digitalWrite(red,LOW);
 }delay(1000);
}
