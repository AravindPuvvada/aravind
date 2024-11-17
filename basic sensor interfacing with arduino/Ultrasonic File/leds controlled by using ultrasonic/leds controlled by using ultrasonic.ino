/*
 if the distance is <= 10 then it indicates green which means safe
 if the distance is <=20 then it indicates yellow which means caution
 if the ditance is <=40 then it indicates red which means red
 */
int red=10;
int yellow=11;
int green=12;
int trig=2;
int echo=3;
int distance;
long duration;
void setup() {
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(2);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration * 0.034/2;
  Serial.print("distance=");
  Serial.print(distance);
  Serial.println("cm");
  if (distance<=10)
  {
    digitalWrite(yellow,LOW);
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    delay(1000);
  }
  else if(distance<=20)
  {
    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    digitalWrite(yellow,HIGH);
    delay(1000);
  }
  else if(distance<=40)
  { digitalWrite(yellow,LOW);
    digitalWrite(red,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(red,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,LOW);
  }
}
