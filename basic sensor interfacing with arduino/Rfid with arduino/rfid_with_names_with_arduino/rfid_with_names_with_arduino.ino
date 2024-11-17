#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Place your card to read personal data...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return;

  // Show UID on serial monitor
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println(content);

  // Authenticate using the key A
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF; // default key for authentication

  byte buffer[18];
  byte size = sizeof(buffer);
  MFRC522::StatusCode status;

  // Read data from block 1
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(1, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Read() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  String namePart1 = "";
  for (uint8_t i = 0; i < 16; i++) {
    if (buffer[i] != 0 && buffer[i] != '\n') { // Skip newline characters
      namePart1 += (char)buffer[i];
    }
  }
  namePart1.trim(); // Trim trailing spaces

  // Read data from block 4
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(4, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Read() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  String namePart2 = "";
  for (uint8_t i = 0; i < 16; i++) {
    if (buffer[i] != 0 && buffer[i] != '\n') { // Skip newline characters
      namePart2 += (char)buffer[i];
    }
  }
  namePart2.trim(); // Trim trailing spaces

  // Concatenate the parts to form the full name
  String fullName = namePart1 + " " + namePart2;

  // Print the name read from the card
  Serial.print("Name: ");
  Serial.println(fullName);

  // Halt PICC
  mfrc522.PICC_HaltA();
  
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();

  // Add a delay so that the card can be removed and re-presented
  delay(5000);
}
