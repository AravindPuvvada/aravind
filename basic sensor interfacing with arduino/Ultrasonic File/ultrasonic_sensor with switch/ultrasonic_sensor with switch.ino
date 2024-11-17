int trig=3;
int echo=5;
int led=7;
long duration;
int distance;
int sw=4;
void setup()
{
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration * 0.034/2;
  Serial.print("distance:");
  Serial.print(distance);
  Serial.println("cm");
  int value=digitalRead(sw);
  Serial.print("Switch:");
  Serial.println(value);
  
  if(distance<30)
  {
    digitalWrite(led,HIGH);
    delay(1000);
    if(digitalRead(sw)==0)
    {
      digitalWrite(led,LOW);
      delay(3000);
    }
  }
  else
  {
    digitalWrite(led,LOW);
  }
  
}
