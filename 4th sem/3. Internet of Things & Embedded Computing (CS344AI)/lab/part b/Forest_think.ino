
//think
//flame D34
//LEP ground an D2

#include <WiFi.h>
#include <HTTPClient.h>

// Flame sensor pin
#define FLAME_SENSOR_PIN 34 // Connect D0 pin of the flame sensor to GPIO 34
#define LED_PIN 2           // Optional: LED connected to GPIO 2 for local alert

// Wi-Fi credentials
const char* ssid = "Nord3";            // Replace with your Wi-Fi SSID
const char* password = "yuck12345";    // Replace with your Wi-Fi password

// ThingSpeak settings
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "S72K845R7L49KNUS"; // Replace with your ThingSpeak Write API Key

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Set pin modes
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Start Wi-Fi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");
}

void loop() {
  // Read flame sensor value (0 = flame detected, 1 = no flame)
  int flameDetected = digitalRead(FLAME_SENSOR_PIN);

  // Print flame sensor status to Serial Monitor
  if (flameDetected == LOW) {
    Serial.println("Flame Detected!");
    digitalWrite(LED_PIN, HIGH); // Turn on LED when flame is detected
  } else {
    Serial.println("No Flame");
    digitalWrite(LED_PIN, LOW);  // Turn off LED when no flame
  }

  // If Wi-Fi is connected, send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(flameDetected);
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.println("Data sent to ThingSpeak");
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }

  // Delay for 15 seconds (compliant with ThingSpeak free account limit)
  delay(15000);
}
