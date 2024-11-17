#include <WiFi.h>
#include <ESP32_MailClient.h>

// Wi-Fi credentials
const char* ssid = "projectpulse";
const char* password = "hailucky123";

// SMTP email credentials
const char* smtpServer = "smtp.gmail.com";
const int smtpPort = 587; // SMTP server port (usually 587 for TLS/STARTTLS)

const char* emailSender = "aravindpuvvada196@gmail.com";
const char* emailRecipient = "puvvadaadithya8@gmail.com";
const char* emailSubject = "Test Email";
const char* emailMessage = "Hello from ESP32! This is a test email.";

// Email account credentials
const char* emailUsername = "aravindpuvvada196@gmail.com";
const char* emailPassword = "mfbc obwt fbco jixg";

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");

  // Initialize email client
  MailClient.begin(smtpServer, smtpPort, emailUsername, emailPassword);

  // Send email
  if (MailClient.send(emailSender, emailRecipient, emailSubject, emailMessage)) {
    Serial.println("Email sent successfully");
  } else {
    Serial.println("Failed to send email");
  }

  // Close the connection
  MailClient.stop();
}

void loop() {
  // Your code here
}
