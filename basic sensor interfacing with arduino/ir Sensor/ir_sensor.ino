int ir=3;
int led=5;
void setup() {
pinMode(ir,INPUT);
pinMode(led,OUTPUT);
// put your setup code here, to run once:

}

void loop() {
if(digitalRead(ir)==0)
{
  digitalWrite(led,HIGH);
  delay(1000);
  // put your main code here, to run repeatedly:
}
else{
  digitalWrite(led,LOW);
  delay(1000);
  
}
}
