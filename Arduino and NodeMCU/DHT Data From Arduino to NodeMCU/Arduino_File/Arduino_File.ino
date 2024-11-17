#include "DHT.h"
#include <SoftwareSerial.h> //instead of parenthesis () put angle bracket as YouTube description does not allow angle bracket 
#define DHTPIN A0

#define DHTTYPE DHT11 

SoftwareSerial espSerial(0,1);
DHT dht(DHTPIN, DHTTYPE);
String str;

void setup(){
Serial.begin(115200);
espSerial.begin(115200);
dht.begin();
delay(2000);
}
void loop()
{
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
Serial.print("H: ");
Serial.print(h); 
Serial.print("% ");
Serial.print(" T: ");
Serial.print(t); 
Serial.println("C");
str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);
espSerial.println(str);
delay(1000);
}
