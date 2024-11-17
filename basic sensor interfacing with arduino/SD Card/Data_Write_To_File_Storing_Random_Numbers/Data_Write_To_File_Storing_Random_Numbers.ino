# cs=13 miso=12 mosi=11 sck=10


#include <SPI.h>
#include <SD.h>
File data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("SD Card init...");
  //test if wiring is correct
  if (!SD.begin(10)) {
    Serial.println("init failed..");
    while (1);
  }
  Serial.println("init ok");
}
void loop() {
  // put your main code here, to run repeatedly:
  int number = random(0, 10); //create random number
  String stringData = (String)number; //convert number to string
  data = SD.open("data.txt", FILE_WRITE); //open file
  if (data) {
    data.println(stringData); //print the data to file
    data.close();
    Serial.println(stringData);
  } else {
    Serial.println("Cannot open file");
  }
}
