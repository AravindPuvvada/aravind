int sensor=A0;
int led=4;
void setup() {
 pinMode(sensor,INPUT);
 pinMode(led,OUTPUT);
 Serial.begin(9600);// put your setup code here, to run once:

}

void loop() {
int a=analogRead(A0);
Serial.println(a);
if(a>250)
{
  digitalWrite(led,HIGH);
  delay(1000);
 
}
else{
  digitalWrite(led,LOW),
  delay(1000);
  
}

}
