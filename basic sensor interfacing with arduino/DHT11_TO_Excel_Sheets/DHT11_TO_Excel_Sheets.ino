#include <DHT.h>

#define DHTPIN   A0     // Define pin for DHT11
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);    // Initialize serial communications with the PC
  dht.begin();           // Initialize DHT11 sensor
  
  printHeadings();       // Print headings initially
}

void loop() {
  delay(2000);           // Wait a few seconds between measurements

  // Reading temperature and humidity values
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Read temperature as Celsius

  // Output the data with headings "Date", "Time", "Temperature", "Humidity"
  Serial.print("DATA,DATE,TIME,");

  // Check if any reads failed and print NaN if so
  if (isnan(t)) {
    Serial.print("NaN");  // Print "NaN" if temperature reading fails
  } else {
    Serial.print(t);      // Print valid temperature
  }

  Serial.print(",");

  if (isnan(h)) {
    Serial.println("NaN");  // Print "NaN" if humidity reading fails
  } else {
    Serial.println(h);      // Print valid humidity
  }
}

// Function to print headings
void printHeadings() {
  Serial.println("LABEL,Date,Time,Temperature (C),Humidity (%)");
}
