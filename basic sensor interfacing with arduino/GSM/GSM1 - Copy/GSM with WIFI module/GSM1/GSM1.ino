#include <SoftwareSerial.h>

#include <DHT.h>
#define DHT_TYPE DHT11
#define DHT_PIN A0
DHT dht(DHT_PIN,DHT_TYPE);
// Create instances for SoftwareSerial and LiquidCrystal
SoftwareSerial sim800l(0,1); // RX, TX


void setup() {
  // Initialize SIM800L communication
  sim800l.begin(9600);
  delay(1000);

  // Initialize LCD


  dht.begin();
}

void loop() {
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  Serial.print("Temperature:");
  Serial.println(temp);
  Serial.print("Humidity:");
  Serial.println(hum);
  delay(2000);
  if(hum>40)
  {
  sendSMS("+919398594569",("Alert"+String(hum)).c_str());
  delay(5000); 
  }
  if(temp>20)
  {
    sendSMS("+919398594569",("Alert"+String(temp)).c_str());
    delay(5000);
  }
  
  // You can add more logic or functionality here if needed
}

void sendSMS(const char* phoneNumber, const char* message) {
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.print(message);
  sim800l.write(0x1A); // Send Ctrl+Z to finish message
  delay(1000);
}
