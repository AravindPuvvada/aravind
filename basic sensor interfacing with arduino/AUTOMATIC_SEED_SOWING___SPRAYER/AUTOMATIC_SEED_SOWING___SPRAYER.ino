String voice;

const int motor1of1 = A1;
const int motor1of2 = A2; 
const int motor2of1 = A3;
const int motor2of2 = A4;

void setup() {
  Serial.begin(9600);
  
  pinMode(motor1of1, OUTPUT);
  pinMode(motor1of2, OUTPUT);
  pinMode(motor2of1, OUTPUT);
  pinMode(motor2of2, OUTPUT);
  
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, LOW);

}

void loop() {
  while (Serial.available())
  {  
  delay(1); 
  char c = Serial.read(); 
  voice += c; 
  }  
  if (voice.length() > 0) 
  {
    Serial.println(voice); 
  if(voice == "1") 
  {
    Serial.println("Front");
    front();
    delay(1000);
  } 
  else if(voice == "2") 
  {
    Serial.println("Back");
    back();
    delay(1000);
  }
  else if(voice == "3") 
  {
    Serial.println("Left");
    left();
    delay(1000);
  }
  else if(voice == "4") 
  {
    right();
    Serial.println("Right");
    delay(1000);
  }
  else if(voice == "5") 
  {
    Serial.println("Stop");
    stopR();
    delay(1000);
  }
 voice="";       //Reset the variable after initiating
 }
}

void front(){
  digitalWrite(motor1of1, HIGH);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, HIGH);
  digitalWrite(motor2of2, LOW);
}

void back(){
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, HIGH);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, HIGH);
}


void left(){
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, HIGH);
  digitalWrite(motor2of1, HIGH);
  digitalWrite(motor2of2, LOW);
}


void right(){
  digitalWrite(motor1of1, HIGH);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, HIGH);
}

void stopR(){
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, LOW); 
}
