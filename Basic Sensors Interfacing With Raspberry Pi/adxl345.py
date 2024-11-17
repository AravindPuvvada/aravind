#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup() {
    Serial.begin(9600);
    if (!accel.begin()) {
        Serial.println("No ADXL345 detected");
        while (1);
    }
    Serial.println("ADXL345 detected!");
}

void loop() {
    // Your loop code here
}
