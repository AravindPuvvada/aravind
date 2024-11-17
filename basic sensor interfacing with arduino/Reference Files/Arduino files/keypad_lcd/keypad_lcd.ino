#include <Keypad.h>
//#include<LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  Serial.begin(9600);
 // lcd.begin(16, 2);
}

void loop()
{
  char key = keypad.getKey();// Read the key

  // Print if key pressed
  if (key)
  {
    Serial.print("Key Pressed : ");
    Serial.println(key);
   // lcd.setCursor( 0, 0);
   // lcd.print("Key Pressed:   ");
   // lcd.setCursor( 12, 0);
   // lcd.print(key);
    //lcd.setCursor( 0, 1);
    //lcd.print("               ");
  }
}
