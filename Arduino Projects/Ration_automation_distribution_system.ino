#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial rfid(2, 3); // RX, TX
#include <Servo.h>

Servo rice; 

Servo oil; 

String rfidTag = "";  // Variable to store RFID tag
String currentUser = ""; // Variable to store the current user
const int maxUsedTags = 10; // Adjust size as needed
String usedTags[maxUsedTags]; // Array to track used tags
int usedTagsCount = 0; // Count of used tags
SoftwareSerial sim800l(11,12);
// Initialize the I2C LCD with address 0x27 (or adjust if your LCD uses a different address)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;  // four rows
const byte COLS = 3;  // three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4};     // connect to the column pinouts of the keypad

// Create an object of keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Function to match RFID tag with username
String getUserFromTag(String tag) {
  if (tag == "120047D7CB49") {
    return "Aravind";
  } else if (tag == "120048356B04") {
    return "Vishnu";
  } else {
    return "Unknown";
  }
}

// Function to validate password based on user
bool validatePassword(String user, String enteredPassword) {
  if (user == "Aravind" && enteredPassword == "211") {
    return true;
  } else if (user == "Vishnu" && enteredPassword == "216") {
    return true;
  } else {
    return false;
  }
}

// Function to check if the RFID tag has already been used
bool isTagUsed(String tag) {
  for (int i = 0; i < usedTagsCount; i++) {
    if (usedTags[i] == tag) {
      return true; // Tag has been used
    }
  }
  return false; // Tag has not been used
}

// Function to mark the RFID tag as used
void markTagAsUsed(String tag) {
  if (usedTagsCount < maxUsedTags) {
    usedTags[usedTagsCount] = tag; // Add tag to used list
    usedTagsCount++; // Increment count
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init(); // Initialize the I2C LCD
  lcd.backlight(); // Turn on the backlight
  project_name(); // Display project name
  rice.attach(A0);
  oil.attach(13);
    sim800l.begin(9600);
  rfid.begin(9600); // Start communication with EM18 reader
}

void loop() {
  char key = keypad.getKey(); // Read the key

  // Reset tagUsed at the beginning of each loop if there's no RFID input
  if (!rfid.available()) {
    // No need to reset tagUsed here anymore
  }

  // RFID Tag reading logic
  if (rfid.available()) {
    char c = rfid.read();  // Read one character
    rfidTag += c;          // Append the character to the RFID tag string

    // Check if we have received the full tag (EM18 typically sends 12 characters)
    if (rfidTag.length() == 12) {
      // Check if the tag has already been used
      if (isTagUsed(rfidTag)) {
        // If tag has been used, display message
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Already taken!!");
        lcd.setCursor(0, 1);
        lcd.print("Try next month"); // Display message for waiting period
        delay(3000); // Show message for 3 seconds
        sendSMS("+917013984982", "Your already taken your essential items please wait for next month ");
        lcd.clear();
        rfidTag = ""; // Clear the RFID tag for the next scan
        project_name(); // Display project name again
      } else {
        currentUser = getUserFromTag(rfidTag);  // Get the username for the tag
        
        Serial.print("RFID Tag: ");
        Serial.println(rfidTag);  // Print the full tag to Serial Monitor
        
        // Display welcome message with username on LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Welcome ");
        lcd.print(currentUser); // Print the user name
        
        markTagAsUsed(rfidTag); // Mark the current tag as used
        rfidTag = ""; // Clear the string for the next tag
        delay(2000);  // Wait for 2 seconds before asking for password
        
        // Ask for password
        String enteredPassword = "";
        bool passwordCorrect = false; // Variable to track if the password is correct

        while (!passwordCorrect) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter password:");  // Prompt to enter password
          enteredPassword = ""; // Reset entered password for each attempt

          // Capture password using keypad
          while (enteredPassword.length() < 3) {
            key = keypad.getKey(); // Read the key
            if (key) {
              enteredPassword += key;  // Append the key to the password
              lcd.setCursor(enteredPassword.length() - 1, 1);  // Show entered keys on LCD
              lcd.print('*'); // Display * for each entered character
            }
          }

          // Validate password
          lcd.clear();
          if (validatePassword(currentUser, enteredPassword)) {
            lcd.setCursor(0, 0);
            lcd.print("Correct password");
            passwordCorrect = true; // Set flag to true if password is correct
          } else {
            lcd.setCursor(0, 0);
            lcd.print("Wrong password");
            lcd.setCursor(0, 1);
            lcd.print("Try again"); // Prompt to try again
            delay(2000); // Wait before allowing another attempt
          }
        }

        delay(3000);  // Wait for 3 seconds before clearing the display
        lcd.clear();

        // Select rice, oil, or exit
        lcd.setCursor(0, 0);
        lcd.print("Press 1 for Rice");
        lcd.setCursor(0, 1);
        lcd.print("Press 2 for Oil ");

        bool selectionMade = false;
        
        while (!selectionMade) {
          key = keypad.getKey(); // Read the key
          
          if (key) {
            lcd.clear();
            if (key == '1') {
              lcd.setCursor(0, 0);
              lcd.print("You selected Rice");
              rice.write(90);       // Tell the servo to go to the specified angle 
              delay(2000); // Show selection for 2 seconds
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Press 2 for Oil");
              lcd.setCursor(0, 1);
              lcd.print("Press 3 to Exit");
            } else if (key == '2') {
              lcd.setCursor(0, 0);
              lcd.print("You selected Oil");
              rice.write(90);       // Tell the servo to go to the specified angle
              delay(2000); // Show selection for 2 seconds
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Press 3 to Exit");
            } else if (key == '3') {
              lcd.setCursor(0, 0);
              lcd.print("Exiting...");
              delay(2000); // Show exit message for 2 seconds
              lcd.clear();
              selectionMade = true; // Exit the loop
            } else {
              continue; // Ignore any other keys
            }
          }
        }

        // Reset variables for the next RFID scan
        rfidTag = "";  // Clear RFID tag
        currentUser = ""; // Clear current user
        lcd.clear(); // Clear the display

        // Restart the process for scanning a new RFID tag
        project_name(); // Re-display project name
      }
    }
  }
}

// Function to display project name on the LCD
void project_name() {
  lcd.setCursor(0, 0);  // Move cursor to the first row
  lcd.print("Automation");
  lcd.setCursor(0, 1);  // Move cursor to the second row
  lcd.print("Ration System");
  delay(3000);
}
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
