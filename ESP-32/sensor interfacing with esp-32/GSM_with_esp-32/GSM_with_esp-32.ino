#include <HardwareSerial.h>   
            
HardwareSerial sim800l(2); // RX, TX
void setup() {
  // Initialize SIM800L communication
  sim800l.begin(9600, SERIAL_8N1, 16, 17);
  delay(1000);
}

void loop() {
  
    sendSMS("+919398594569","Hello");
    delay(4000);
}

void sendSMS(const char* phoneNumber, const char* message) 
{
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.print(message);
  sim800l.write(0x1A); // Send Ctrl+Z to finish message
  delay(1000);
  Serial.println("SMS Sent");
}
