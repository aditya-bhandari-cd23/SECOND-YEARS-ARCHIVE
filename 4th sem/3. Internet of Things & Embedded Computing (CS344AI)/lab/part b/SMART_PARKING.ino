#define BLYNK_TEMPLATE_ID "TMPL3d_N_XT_Z"
#define BLYNK_TEMPLATE_NAME "Smart Lighting"
#define BLYNK_AUTH_TOKEN "h2jorxfjmSNdwB_M9mgNubFRpFnE7Z5k"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Replace with your network credentials
char ssid[] = "Nord3";
char password[] = "yuck12345";

// Define IR sensor pins
const int irSensorPin1 = 23; // GPIO 23 for Sensor 1
const int irSensorPin2 = 22; // GPIO 22 for Sensor 2

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  Blynk.run(); // Keep Blynk running

  // Read sensor values
  int sensorValue1 = digitalRead(irSensorPin1);
  int sensorValue2 = digitalRead(irSensorPin2);
  Serial.print(sensorValue1);
  Serial.print(sensorValue2);

  // Send sensor data to Blynk
  Blynk.virtualWrite(V4, sensorValue1); // V1 is the virtual pin for Sensor 1's LED widget
  Blynk.virtualWrite(V3, sensorValue2); // V2 is the virtual pin for Sensor 2's LED widget

  // Optional: Short delay to reduce rapid updates
  delay(100); // Adjust as needed to balance responsiveness and update rate
}