#include<DHT.h>
#include<Servo.h>

//DHT
#define DHT_TYPE DHT11
#define DHT_PIN A0
DHT dht(DHT_PIN,DHT_TYPE);
int r1=5;

//ultrasonic
int r2=6;
int echo=3;
int trig=4;
int distance;
long duration;

//ldr
int ldr=A1;
int led=7;

//servo
Servo user;
int s1=9;
int s2=10;

//soil
int soil=A2;
int l2=11;

// pir
int pir=12;
int l3=13;

void setup() {
  Serial.begin(9600); 

  //DHT
  dht.begin();
  pinMode(r1,OUTPUT);

  //ultrasonic
  pinMode(trig,OUTPUT);
  pinMode(r2,OUTPUT);

  //ldr
  pinMode(led,OUTPUT);

  //servo
  user.attach(8);
  user.write(0);

  //soil
  pinMode(l2,OUTPUT);

  //pir
  pinMode(13,OUTPUT);
}

void loop() {
  // dht block
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.println("c");
  Serial.print("Humidity:");
  Serial.println(hum);
  delay(2000);
  if(hum>50)
  {
    digitalWrite(r1,HIGH);
  }
  else
  {
    digitalWrite(r1,LOW);
  }

  //ultrasonic block
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

  //condition
  if(distance<30)
  {
    digitalWrite(r2,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(r2,LOW);
  }

  //ldr block
  int value=analogRead(ldr);
  Serial.print("ldr:");
  Serial.println(value);
  //condition
  if(value>300)
  {
    digitalWrite(led,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  //servo block
  
  if(digitalRead(s1)==0)
  {
    user.write(180);
    delay(1000);
  }
  if(digitalRead(s2)==0)
  {
    user.write(0);
     delay(1000);
  }

  //soil
  int sensor=analogRead(soil);
  Serial.print("Soil value=");
  Serial.println(sensor);
  //condition
  if(sensor>350)
  {
    digitalWrite(l2,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(l2,LOW);
  }
  
  //pir block
  int val=digitalRead(pir);
  if(digitalRead(pir)==0)
  {
    digitalWrite(l3,HIGH);
 
  }
  else
  {
    digitalWrite(l3,LOW);
  }
}
