#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Wi-Fi Credentials
const char* ssid = "your_wifi_ssid";   // Replace with your Wi-Fi SSID
const char* password = "your_wifi_password";  // Replace with your Wi-Fi password

// ThingSpeak Credentials
unsigned long channelID = YOUR_CHANNEL_ID;  // Replace with your ThingSpeak Channel ID
const char* writeAPIKey = "your_write_api_key";  // Replace with your ThingSpeak Write API Key

WiFiClient client;

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read ECG sensor data from analog pin A0
  int ECGValue = analogRead(A0);  // Read ECG value from AD8232
  
  // Print ECG value to the Serial Monitor (for debugging)
  Serial.print("ECG Value: ");
  Serial.println(ECGValue);
  
  // Send the ECG data to ThingSpeak
  ThingSpeak.setField(1, ECGValue);  // Set Field 1 with ECG value
  
  // Write data to ThingSpeak
  int responseCode = ThingSpeak.writeFields(channelID, writeAPIKey);
  
  // Check if data was successfully sent to ThingSpeak
  if (responseCode == 200) {
    Serial.println("Data sent successfully to ThingSpeak");
  } else {
    Serial.println("Failed to send data to ThingSpeak");
  }
  
  // Delay before the next reading
  delay(2000);  // Wait for 2 seconds
}
