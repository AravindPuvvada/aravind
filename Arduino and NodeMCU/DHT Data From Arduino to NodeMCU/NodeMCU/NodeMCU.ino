void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  // Check if data is available from the Arduino
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // Read the incoming data as a string

    // Extract temperature and humidity values
    int humidityIndex = data.indexOf("H= ");
    int temperatureIndex = data.indexOf("T= ");
    
    if (humidityIndex != -1 && temperatureIndex != -1) {
      // Extract the substring containing the humidity value
      String humidityString = data.substring(humidityIndex + 3, data.indexOf(' ', humidityIndex + 3));
      // Extract the substring containing the temperature value
      String temperatureString = data.substring(temperatureIndex + 3);

      // Convert the strings to float
      float humidity = humidityString.toFloat();
      float temperature = temperatureString.toFloat();

      // Print the extracted values
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print("%, Temperature: ");
      Serial.print(temperature);
      Serial.println("C");
    }
  }
}
