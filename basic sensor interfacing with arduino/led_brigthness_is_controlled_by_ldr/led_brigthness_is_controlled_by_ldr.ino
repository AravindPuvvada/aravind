int led=9;
int ldr=A0;
int val;
int brigthness=0;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  
}

void loop()
{
 val=analogRead(ldr);
 brigthness=map(val,0,1023,0,255);
 analogWrite(led,brigthness);
 Serial.print("Ldr value:");
 Serial.println(val);
 Serial.print("Brigthness:");
 Serial.println(brigthness);
 delay(1000);
}
