// Pin Configuration for Sensors

// DHT11 Sensor Pin Connections:
// 1. VCC (Pin 1) -> 3.3V on ESP32
// 2. GND (Pin 4) -> GND on ESP32
// 3. DATA (Pin 2) -> GPIO 4 on ESP32 (as defined by DHTPIN)

// MQ-2 Smoke Sensor Pin Connections:
// 1. VCC -> 5V (or 3.3V) on ESP32
// 2. GND -> GND on ESP32
// 3. A0 (Analog Output) -> GPIO 34 on ESP32 (as defined by MQ2_PIN)
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Pin Definitions
#define DHTPIN 4      // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11 // DHT 11
#define MQ2_PIN 34    // ADC pin connected to the MQ-2 sensor (ESP32 GPIO34)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi credentials
const char* ssid = "Nord3";            // Replace with your Wi-Fi SSID
const char* password = "yuck12345";    // Replace with your Wi-Fi password

// ThingSpeak settings
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "1Y1WF4O7O1NHWCAO";       // Replace with your ThingSpeak Write API Key

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  // Connect to Wi-Fi
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
  // Read values from DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius by default

  // Read value from MQ-2 smoke sensor
  int smokeValue = analogRead(MQ2_PIN);

  // Check if any reads from DHT11 failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print DHT11 sensor values to the Serial Monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  // Print MQ-2 sensor value to the Serial Monitor
  Serial.print("MQ-2 Sensor Value: ");
  Serial.println(smokeValue);

  // Send data to ThingSpeak if Wi-Fi is connected
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(temperature) + "&field2=" + String(humidity) + "&field3=" + String(smokeValue);
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

  // Add a delay for stability (15 seconds to comply with ThingSpeak's free API limit)
  delay(15000);
}
