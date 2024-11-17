int relay=3;
int ldr=A5;
int val;

void setup() {
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
}

void loop() 
{
 val=analogRead(ldr);
 Serial.print("Value:");
 Serial.println(val);
 if(val>650)
 {
  digitalWrite(relay,HIGH);
 }
 else
 {
  digitalWrite(relay,LOW);
 }
  delay(1000);
}
