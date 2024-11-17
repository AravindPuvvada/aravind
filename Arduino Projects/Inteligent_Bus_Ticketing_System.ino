#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Arduino.h> // This is usually included by default in Arduino sketches.


const byte ROWS = 4; // four rows
const byte COLS = 3;
int flag = 0;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

int flag2 = 0;
int flag3=0;
byte rowPins[ROWS] = {10, 9, 8, 7};  // connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4};      // connect to the column pinouts of the keypad
int designation = false;

// Create an object of keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int userBalance = 0; // To store user's balance
String userName = ""; // To store user's name

// Predefined RFID tags and their corresponding balances
const String rfidTags[] = {"120047D7CB49", "120048356B04"}; // Example tags
int initialBalances[] = {500, 300};
LiquidCrystal_I2C lcd(0x27, 16, 2); 
SoftwareSerial rfid(2, 3); // RX, TX
String rfidTag = "";
bool invalidKeyPressed = false;  // Track if an invalid key was pressed
int currentState = 0; // Track current state for selecting location or designation
String loc = "";
String des = "";

// Price for each designation
const int ticketPrices[] = {250, 350, 400}; // Prices for Hyderabad, Bangalore, Chennai
SoftwareSerial sim800l(11,12);

void setup() {
  Serial.begin(9600);    
       
  sim800l.begin(9600);
  rfid.begin(9600);
  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on the backlight
  project_name();        // Display project name
  
  printLocations();      // Show location options on LCD
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key Pressed: ");
    Serial.println(key);
    
    if (invalidKeyPressed) {
      if (key == '0') {
        invalidKeyPressed = false;  
        printLocations();           
      }
    } else {
      if (currentState == 0) { // State for selecting location
        if (key == '1') {
          loc = "GNT";
          showLocation("Guntur");
          currentState = 1; // Move to designation selection
        } else if (key == '2') {
          showLocation("Vijayawada");
          loc = "BZA";
          currentState = 1; // Move to designation selection
        } else if (key == '3') {
          showLocation("Gudivada");
          loc = "GDV";
          currentState = 1; // Move to designation selection
        } else if (key == '*') {
          showLocation("Gudivada");
          currentState = 0; // Move to designation selection
        } else {
          showInvalidKeyMessage();  
          invalidKeyPressed = true; 
        }
      } else if (currentState == 1 && flag == 0) { // State for selecting designation
        if (key == '1') {
          showDesignation("Hyderabad");
          des = "HYD";
          designation = true;
          flag = 1;
          flag2 = 0;
        } 
        else if (key == '*') {  
          printLocations(); // Go back to locations
          currentState = 0; // Reset state
        } 
        else if (key == '2') {
          showDesignation("Bangalore");
          des = "BLR";
          designation = true;
          flag2 = 0;
          flag = 1;
        } else if (key == '3') {
          showDesignation("Chennai");
          des = "CHN";
          designation = true;
          flag = 1;
          flag2 = 0;
        } else {
          showInvalidKey();   
        }
      }
    }
  }
  
  if (designation) {
    if (key == '*') {
      currentState = 1;
      flag = 0;
      flag2 = 1;
      printDesignations();
      delay(1000);
    }
    if (flag2 == 0) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print(loc);
      lcd.print("->");
      lcd.print(des);
      lcd.setCursor(0, 1);
      lcd.print(" Press # to Go");
      delay(1000);
    }
 
    if (key == '#') {
      lcd.clear();
      userName = ""; // Reset user name
      lcd.print("Place Your Card");
      delay(1000);
      Serial.println("Place the RFID card/tag near the reader...");
      flag2 = 1;
    }
  }
  
  if (rfid.available()) {
    char c = rfid.read();  
    rfidTag += c;          

    if (rfidTag.length() == 12) { // Assume RFID tag length is 12 characters
      Serial.print("RFID Tag: ");
      Serial.println(rfidTag); 
      if (rfidTag == "120047D7CB49")
      {
        userName="Yashwanth anna";
      }
      else if (rfidTag == "120048356B04")
      {
        userName="Vishnu";
      }
      else
      {
        userName="";
      }
      
      // Check balance for the RFID tag
      checkBalance(rfidTag);
      
      rfidTag = "";  // Reset RFID tag after processing
    }
  }
 
}

// Function to display project name on the LCD
void project_name() {
  lcd.setCursor(0, 0);        // Set cursor to the first row, first column
  lcd.print(" Intelligent Bus");
  lcd.setCursor(0, 1);        // Set cursor to the second row, first column
  lcd.print("   Ticketing");
  delay(4000);                // Wait for 4 seconds before proceeding
  lcd.clear();
}

// Function to print locations on the LCD
void printLocations() {
  lcd.clear();                // Clear the LCD
  lcd.setCursor(0, 0);        // Set cursor to the first row, first column
  lcd.print("Enter Location"); // Show message
  lcd.setCursor(0, 1);        // Set cursor to the second row
  lcd.print("  GNT BZA GDV");  // Show location options
}

// Function to display the selected location on the LCD
void showLocation(String location) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You selected:");
  lcd.setCursor(0, 1);
  lcd.print(location);  
  delay(3000);  
          printFares();
        
  printDesignations(); // Show designations after selection
}

// Function to print designations on the LCD
void printDesignations() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Dest.....");
  lcd.setCursor(0, 1);
  lcd.print("Hyd Blr Chn");
  delay(1000);
}

// Function to display the selected designation on the LCD
void showDesignation(String designation) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Selected:");
  lcd.setCursor(0, 1);
  lcd.print(designation);  
  delay(3000);          
}

// Function to display invalid key message
void showInvalidKeyMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Invalid Option!");
  lcd.setCursor(0, 1);
  lcd.print("Press 0 to Retry");  // Display message to press '*' to retry
  delay(2000);                    // Hold message for 2 seconds
}

void showInvalidKey() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Invalid Option!");
  lcd.setCursor(0, 1);
  lcd.print("Press Retry");
  delay(1000);
  lcd.clear();
  currentState = 1;
  flag = 0;
  printDesignations();
  delay(1000); // Hold message for 2 seconds
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
      
      // Determine ticket price based on the selected designation
      int ticketCost = 0;
      if (des == "HYD") ticketCost = ticketPrices[0]; // Hyderabad
      else if (des == "BLR") ticketCost = ticketPrices[1]; // Bangalore
      else if (des == "CHN") ticketCost = ticketPrices[2]; // Chennai
      
      // Check if balance is sufficient for ticket cost
      if (userBalance >= ticketCost) {
        userBalance -= ticketCost; // Deduct the ticket cost
        initialBalances[i] = userBalance; // Update the user's balance
            
        // Show successful transaction
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ticket Booked!");
        lcd.setCursor(0, 1);
        lcd.print("Balance: " + String(userBalance));        
        // Send SMS with booking details
String message = userName + ", your ticket is successfully booked from " + loc + " to " + des + " !! and your new balance is " + String(userBalance) + "\nThanks for booking from Intelligent bus ticketing system";

        Serial.print("UserName: ");
Serial.println(userName);
Serial.print("Location: ");
Serial.println(loc);
Serial.print("Designation: ");
Serial.println(des);
Serial.print("UserBalance: ");
Serial.println(userBalance);

       
sendSMS("+919441348531", ( "Congratulation!! " + userName + 
                         " Successfully booked a ticket from " + loc + 
                         " to " + des + ".").c_str());
delay(2000);



sendSMS("+919441348531", ("Your current balance is "+String(userBalance)).c_str());

        
      } else {
        // Show insufficient balance message
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Insufficient!");
        lcd.setCursor(0, 1);
        lcd.print("Balance!");
        sendSMS("+919441348531", (userName+"Sorry!! you don't have sufficient balance.").c_str());
      }
      
      delay(3000); // Hold the message for 3 seconds
      
      // Reset the system to initial state for new user
      resetSystem();
      return; // Exit the function after processing the RFID tag
    }
  }
  
  // If tag is not found, show an error message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag Not Found!");
  delay(3000); // Show message for 3 seconds
  
  // Reset the system to initial state
}

void resetSystem() {
  // Reset the system to initial state
  userBalance = 0;
  loc = "";
  des = "";
  flag = 0;
  currentState = 0;
  designation = false;
  lcd.clear();
  printLocations(); // Show location options again
}

// Function to send SMS
void sendSMS(const char* phoneNumber, const char* message) {
  sim800l.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.print(message);
  sim800l.write(0x1A); // Send Ctrl+Z to finish message
  delay(1000);
  Serial.println("SMS SENT");
}
void printFares() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  HYD BLR CHN");
  
  lcd.setCursor(0, 1);
  lcd.print("  250 350 400");
  
  delay(3000); // Show the fares for 5 seconds
}
