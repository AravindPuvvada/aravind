#include<Keypad.h>
const byte ROWS=4;
const byte COLS=3;
char keys[ROWS][COLS]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowpins[ROWS]={9,8,7,6};
byte colpins[COLS]={5,4,3};
String password="";

Keypad keypad=Keypad(makeKeymap(keys),rowpins,colpins,ROWS,COLS);
void setup() {
  Serial.begin(9600);
}

void loop() {
 char key=keypad.getKey();
 while(key)
 {
 if(key)
 {
  Serial.print("key:");
  Serial.println(key);
 }
 password+=key;
 }
 if(password=="1234")
 {
  Serial.println("Corrected");
 }
 else
 {
  Serial.println("Wrong Password");
 }
}
