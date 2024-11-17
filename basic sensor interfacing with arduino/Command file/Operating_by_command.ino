int led=5;

void setup() {
Serial.begin(9600);
pinMode(led,OUTPUT);
}
void loop() {
if(Serial.available()>0)
{
  //int light=Serial.read();
  Serial.print("led:");
  //Serial.println(light);
  if(light=='1')
  {
    digitalWrite(led, HIGH);
    Serial.println("HIGH");
    
  }
  if(light=='2')
  {
    digitalWrite(led, LOW);
    
  }
  delay(1000);
  /*else if(relay==2)
  {
    digitalWrite(relay,HIGH);
    
  }*/
}
}
