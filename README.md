# IoT-Based ECG Machine

This project demonstrates an **IoT-based Electrocardiogram (ECG) Machine** that collects ECG data using the **AD8232 ECG sensor** and sends it to **ThingSpeak** using an **ESP8266 (NodeMCU)**. The ECG data is visualized in real-time on the **ThingSpeak** platform, allowing remote monitoring.

## Features
- **Real-time ECG monitoring** using the AD8232 ECG sensor.
- **Wireless data transmission** via ESP8266 (NodeMCU).
- **Cloud-based monitoring** and visualization on **ThingSpeak**.
- **Simple, low-cost, and easy-to-assemble** ECG machine.

## Components Required

1. **AD8232 ECG Sensor** – Used to measure ECG signals.
2. **ESP8266 (NodeMCU)** – Microcontroller for Wi-Fi connectivity.
3. **Jumper Wires** and **Breadboard** – For making connections.
4. **Arduino IDE** – To write and upload code to the ESP8266.
5. **ThingSpeak Account** – To visualize and monitor ECG data.

## Circuit Diagram

The connections between the components are as follows:

### **AD8232 ECG Sensor to ESP8266 (NodeMCU)**:
- **AD8232 GND** → **ESP8266 GND**
- **AD8232 VCC** → **ESP8266 3.3V**
- **AD8232 Output (Pin)** → **ESP8266 A0 (Analog Pin)**
- **AD8232 LO+** → **ESP8266 GND**
- **AD8232 LO-** → **ESP8266 GND**

### **ESP8266 (NodeMCU)**:
- **VCC** → **3.3V**
- **GND** → **Ground**

## Setup Instructions

### 1. **Create ThingSpeak Account**:
   - Go to [ThingSpeak](https://thingspeak.com) and create a free account.
   - Create a new channel with **Field 1** called `ECG Reading`.
   - Copy the **Channel ID** and **Write API Key** from your channel settings for later use.

### 2. **Install Arduino Libraries**:
   - Install the **ESP8266WiFi** and **ThingSpeak** libraries in your Arduino IDE:
     - Go to **Sketch** > **Include Library** > **Manage Libraries**.
     - Search for **ESP8266WiFi** and **ThingSpeak**, and install them.

### 3. **Upload the Code**:
   - Open the Arduino IDE and select the **NodeMCU 1.0 (ESP-12E Module)** board under **Tools** > **Board**.
   - Copy the provided **Arduino code** into the Arduino IDE.
   - Replace the placeholders for **Wi-Fi SSID**, **Wi-Fi Password**, **ThingSpeak Channel ID**, and **Write API Key** with your actual credentials.
   - Upload the code to the ESP8266.

### 4. **Visualize ECG Data on ThingSpeak**:
   - Once the code is uploaded, open the **Serial Monitor** in Arduino IDE.
   - You should see messages indicating that the ESP8266 is connecting to your Wi-Fi.
   - After a successful connection, the ESP8266 will start sending ECG data to ThingSpeak.
   - Log in to **ThingSpeak** and view your channel’s **Field 1** to monitor the real-time ECG data as it is displayed on the graph.

## Code Description

- **Wi-Fi Setup**: The ESP8266 connects to your Wi-Fi using the credentials provided in the code.
- **Reading ECG Data**: The ECG data is read from the **AD8232 sensor** via the **analog pin A0**.
- **Sending Data to ThingSpeak**: The code sends the ECG data to **ThingSpeak** using the `ThingSpeak.setField()` method.
- **Data Visualization**: Once the data is sent, ThingSpeak plots it on a graph, enabling real-time visualization.

### Arduino Code

```cpp
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
