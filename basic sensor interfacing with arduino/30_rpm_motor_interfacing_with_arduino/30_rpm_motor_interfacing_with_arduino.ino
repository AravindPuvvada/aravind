String voice;

const int motor1of1 = A1;
const int motor1of2 = A2; 
const int motor2of1 = A3;
const int motor2of2 = A4;

int led=6;
int l2=7;


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

  Serial.println("1 for front");
  Serial.println("2 for back");
  Serial.println("3 for left");
  Serial.println("4 for right");
  Serial.println("5 for stop");

}

void loop() {
  while (Serial.available())
  {   
  char a = Serial.read(); 
  voice += a; 
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
    stop();
    delay(1000);
  }
  else if(voice == "6") 
  {
    Serial.println("Relay1");
    digitalWrite(led,HIGH);
    delay(1000);
  }
  else if(voice == "7") 
  {
    Serial.println("Relay2");
    digitalWrite(l2,HIGH);
    delay(1000);
  }
  else if(voice == "8") 
  {
    Serial.println("Relay1 off");
    digitalWrite(led,LOW);
    delay(1000);
  }
  else if(voice == "9") 
  {
    Serial.println("Relay2 off");
    digitalWrite(l2,LOW);
    delay(1000);
  }
 voice="";       
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

void stop(){
  digitalWrite(motor1of1, LOW);
  digitalWrite(motor1of2, LOW);
  digitalWrite(motor2of1, LOW);
  digitalWrite(motor2of2, LOW); 
}
