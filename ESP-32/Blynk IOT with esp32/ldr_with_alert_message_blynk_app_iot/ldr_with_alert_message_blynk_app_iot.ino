#define BLYNK_TEMPLATE_ID "TMPL3yU5__Pfn"
#define BLYNK_TEMPLATE_NAME "LDR alert message"
#define BLYNK_AUTH_TOKEN "H5jSIZHD3WUbPPM_MoOkjB71Izz-da_T"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "projectpulse";  // type your wifi name
char pass[] = "hailucky123";  // type your wifi password
int led=2;
 
#define ldrpin 34
BlynkTimer timer;
int flag=0;
void sendSensor(){ 
   int ldrvalue = analogRead(ldrpin);
   Serial.print("LDR:");
   Serial.println(ldrvalue);
   Blynk.virtualWrite(V0, ldrvalue);
  if (ldrvalue>3500 && flag==0) {
    Serial.println("LEDS on");  
    Blynk.logEvent("ldr_alert_message","leds on");
    digitalWrite(led,HIGH);
    
    flag=1;
  }
  else if (ldrvalue<=3500)
  {
    flag=0;
    digitalWrite(led,LOW);   
  }
 
}

void setup(){
  pinMode(ldrpin, INPUT);
  pinMode(led,OUTPUT); 
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
