#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Nord3";            // Replace with your Wi-Fi SSID
const char* password = "yuck12345";    // Replace with your Wi-Fi password

// ThingSpeak settings
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "ECYA92K3G7QK9K91"; // 
int sensorPin = 34; // Moisture sensor analog pin
int ledPin = 25;    // LED digital pin
int threshold = 4000; // Moisture threshold value

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int moistureLevel = analogRead(sensorPin);
  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);

  // LED control
  if (moistureLevel < threshold) {
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn off LED
  }

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(moistureLevel);
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Data sent to ThingSpeak: " + payload);
    } else {
      Serial.println("Error sending data");
    }

    http.end();
  } else {
    Serial.println("WiFi disconnected");
  }

  delay(15000); // Wait 15 seconds before sending the next data
}
