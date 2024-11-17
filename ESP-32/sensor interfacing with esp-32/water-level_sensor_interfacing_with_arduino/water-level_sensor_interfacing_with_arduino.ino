int red=18;
int water=12;
void setup() {
 pinMode(red,OUTPUT);
 Serial.begin(9600);
}

void loop() {
 int val=analogRead(water);
 Serial.print("Water-level:");
 Serial.println(val);
 delay(1000);
}
