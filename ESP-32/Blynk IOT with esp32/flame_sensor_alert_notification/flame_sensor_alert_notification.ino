#define BLYNK_TEMPLATE_ID "TMPL397csZV4h"
#define BLYNK_TEMPLATE_NAME "FIRE ALERT NOTIFICATION"
#define BLYNK_AUTH_TOKEN "TuiaGb7KXd6JQTf8lGVuWqCXoCbB0Qvs"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "projectpulse";  // type your wifi name
char pass[] = "hailucky123";  // type your wifi password
 
#define FLAME_SENSOR  4
BlynkTimer timer;
int flag=0; 
void sendSensor(){ 
   int isButtonPressed = digitalRead(FLAME_SENSOR);
  if (isButtonPressed==0 && flag==0) {
    Serial.println("Fire in the House");  
    Blynk.logEvent("fire_alert","Fire Detected");
    
    flag=1;
  }
  else if (isButtonPressed==1)
  {
    flag=0;
    
  }
 
}

void setup(){
  pinMode(FLAME_SENSOR, INPUT); 
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
