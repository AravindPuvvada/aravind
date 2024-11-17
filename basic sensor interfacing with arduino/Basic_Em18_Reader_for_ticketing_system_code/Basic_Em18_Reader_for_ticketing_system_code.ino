#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// EM18 Reader setup
SoftwareSerial rfid(2, 3); // RX, TX
String rfidTag = "";
int userBalance = 0; // To store user's balance
const int ticketCost = 10; // Cost of each ticket

// Predefined RFID tags and their corresponding balances
const String rfidTags[] = {"120047D7CB49", "120048356B04"}; // Example tags
int initialBalances[] = {50, 30}; // Initial balances for the tags (change const to int for modification)

// Keypad and LCD setup
const byte ROWS = 4; // four rows
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {10, 9, 8, 7};  // connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4};      // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);    
  rfid.begin(9600);     
  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on the backlight
}

void loop() {
  char key = keypad.getKey();
  
  if (rfid.available()) {
    char c = rfid.read();  
    rfidTag += c;          

    if (rfidTag.length() == 12) { // Assume RFID tag length is 12 characters
      Serial.print("RFID Tag: ");
      Serial.println(rfidTag); 
      
      // Check balance for the RFID tag
      checkBalance(rfidTag);
      
      rfidTag = "";  // Reset RFID tag after processing
    }
  }

  // Your existing keypad handling logic...
}

void checkBalance(String tag) {
  for (int i = 0; i < sizeof(rfidTags) / sizeof(rfidTags[0]); i++) {
    if (tag == rfidTags[i]) {
      userBalance = initialBalances[i]; // Get balance

      // Display current balance
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Balance: ");
      lcd.setCursor(0, 1);
      lcd.print(userBalance);
      delay(3000); // Show balance for 3 seconds
      
      // Check if balance is sufficient for ticket cost
      if (userBalance >= ticketCost) {
        userBalance -= ticketCost; // Deduct the ticket cost
        initialBalances[i] = userBalance; // Update the initial balance
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ticket Booked!");
        lcd.setCursor(0, 1);
        lcd.print("New Balance: ");
        lcd.print(userBalance); // Show new balance
        delay(3000); // Show message for 3 seconds
      } else {
        // Insufficient balance message
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Insufficient");
        lcd.setCursor(0, 1);
        lcd.print("Balance!");
        delay(3000); // Show message for 3 seconds
      }
      return;
    }
  }
  
  // If tag not found
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag Not Found!");
  delay(3000); // Show error message for 3 seconds
}
