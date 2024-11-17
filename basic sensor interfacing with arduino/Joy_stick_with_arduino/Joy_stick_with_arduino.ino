const int x=A1;
const int y=A0;

int x_adc,y_adc;
float X_volt,y_volt;

void setup() {
  Serial.begin(9600);
}

void loop() {
  x_adc=analogRead(x);
  y_adc=analogRead(y);
  X_volt=((x_adc*5.0)/1023);
  y_volt=((y_adc*5.0)/1023);
  Serial.print("Voltage at X-axis:");
  Serial.print(X_volt);
  Serial.print("\t");
  Serial.print("Voltage at y-axis:");
  Serial.println(y_volt);
  delay(1000);
}
