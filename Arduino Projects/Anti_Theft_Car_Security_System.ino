#include <SoftwareSerial.h>
#include <Keypad.h>

SoftwareSerial sim800l(10, 11); // GSM RX, TX
SoftwareSerial BTSerial(0,1); // Bluetooth RX, TX
const byte rows = 4;
const byte cols = 3;

char keys[rows][cols] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowpins[rows] = {9, 8, 7, 6};
byte colpins[cols] = {5, 4, 3};

Keypad keypad = Keypad(makeKeymap(keys), rowpins, colpins, rows, cols);

String password = "";
String correctpassword = "147";
String bluetoothCommand = "";

int buzzer = A0;
int relay = A1;
int flag = 0;
bool authorized = false;
int vibration = 2;

void setup() 
{
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(vibration, INPUT);
  sim800l.begin(9600);
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(100);
}

void loop() 
{
  // Keypad input handling
  char key = keypad.getKey();
  int val = digitalRead(vibration);
  if (key)
  {
    Serial.print("Key: ");
    Serial.println(key);
    if (key == '*')
    {
      if (password == correctpassword)
      {
        Serial.println("Correct Password");
        sendSMS("+919398594569", "Access Granted");
        flag = 0;
        authorized = true;
        // Turn relay ON when authorized
      }
      else
      {
        authorized = false;
        flag++;
        if (flag == 1)
        {
          Serial.println("Incorrect Password");
          Serial.println("Out of 2 Attempts, 1 Attempt is Completed");
        }

        if (flag >= 2)
        {
          Serial.println("Incorrect Password");
          digitalWrite(buzzer, HIGH);
          sendSMS("+919398594569", "Alert!!: Somebody tries to theft your car");
          delay(2000);
          digitalWrite(buzzer, LOW);
        }
      }
      password = "";
    }
    else
    {
      password += key;
    }
  }

  // Bluetooth input handling
  if (BTSerial.available())
  {
    char c = BTSerial.read();
    Serial.write(c); // Forward the received data to the Serial Monitor
    bluetoothCommand += c; // Accumulate Bluetooth command
  }

  // Process the accumulated Bluetooth command
  if (authorized && bluetoothCommand.endsWith("Start098"))
  {
    Serial.println("");
     digitalWrite(relay, HIGH);
    Serial.println("Car Engine Starts and Enjoy Your Ride");
    BTSerial.println("Car Engine Starts and Enjoy Your Ride");
    digitalWrite(relay, HIGH); // Turn relay ON when receiving Start098
    bluetoothCommand = ""; // Clear the command after processing
  }
  else if (bluetoothCommand.endsWith("Stop098"))
  {
    digitalWrite(relay, LOW);
    Serial.println("Car Engine Stops");
    

    BTSerial.println("");
    BTSerial.println("Car Engine Stops");
     // Turn relay OFF when receiving complete
    bluetoothCommand = ""; // Clear the command after processing
  }

  // Handle unauthorized access and vibration sensor
  if (!authorized)
  {
    if (val == LOW)
    {
      Serial.println("Vibrations are detected");
      digitalWrite(buzzer, HIGH);
      sendSMS("+919398594569", "Some Vibrations are detected without authentication");
      delay(1000);
      digitalWrite(buzzer, LOW);
    }
    else
    {
      digitalWrite(buzzer, LOW);
    }
  }
}

void sendSMS(const char* phoneNumber, const char* message)
{
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
