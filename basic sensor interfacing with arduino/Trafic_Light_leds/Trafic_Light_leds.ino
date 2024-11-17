int red=13;
int yellow=12;
int green=11;
int g1=2;
int y1=3;
int r1=4;
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(y1, OUTPUT);
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(green,LOW);
}

void loop() {
  digitalWrite(green, HIGH);  
  delay(1000);                       
  digitalWrite(green, LOW);    
  delay(1000); 
  digitalWrite(yellow, HIGH);  
  delay(1000);                      
  digitalWrite(yellow, LOW);    
  delay(1000); 
  digitalWrite(red, HIGH);   
  delay(1000);                  
  digitalWrite(red, LOW);    
  delay(1000); 
  digitalWrite(g1, HIGH);  
  delay(1000);                       
  digitalWrite(g1, LOW);    
  delay(1000); 
  digitalWrite(y1, HIGH);  
  delay(1000);                      
  digitalWrite(y1, LOW);    
  delay(1000); 
  digitalWrite(r1, HIGH);   
  delay(1000);                  
  digitalWrite(r1, LOW);    
  delay(1000);
}
