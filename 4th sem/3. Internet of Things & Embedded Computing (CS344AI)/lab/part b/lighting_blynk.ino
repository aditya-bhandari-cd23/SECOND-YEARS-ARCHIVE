// anubhavp.cd22@rvce.edu.in
// LDR-gpio34
// led-gpio2(long leg)
// led-grnd(short leg)
//blynk
#define BLYNK_TEMPLATE_ID "TMPL3UDYxdD8v"
#define BLYNK_TEMPLATE_NAME "Smart Lighting"
#define BLYNK_AUTH_TOKEN "60515FTU3_RgYrMSBBbNnocRB9a7lSjk"

#include <WiFi.h>               // ESP32 WiFi library
#include <BlynkSimpleEsp32.h>    // Blynk library for ESP32

// Pin Definitions for ESP32
#define LDR_PIN 34    // Analog pin for LDR (ADC1 channel 6)
#define LED_PIN 2     // Digital pin for LED

// Replace with your WiFi credentials
char ssid[] = "Nord3";
char pass[] = "yuck12345";

// Timer for Blynk
BlynkTimer timer;

// Variables to store the state of the system
bool manualLEDControl = false; // Manual override for LED
bool ldrEnabled = true;        // LDR sensor control (true = enabled, false = disabled)

// Function to control LED from Blynk button (V2)
BLYNK_WRITE(V2) {
  manualLEDControl = true; // Enable manual override for LED
  int ledState = param.asInt(); // Get value from the Blynk button (0 or 1)

  if (ledState == HIGH) {
    // Turn on LED and update Blynk status
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(V2, 1);  // Update Blynk to show LED ON
    Serial.println("Manual LED ON");
  } else {
    // Turn off LED, reset system and update Blynk status
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V2, 0);  // Update Blynk to show LED OFF
    Serial.println("Manual LED OFF - Resetting system");
    resetSystem();
  }
}

// Function to enable/disable LDR sensor (V3)
BLYNK_WRITE(V3) {
  int ldrState = param.asInt(); // Get value from the Blynk button (0 or 1)

  if (ldrState == HIGH) {
    ldrEnabled = true;  // Enable LDR-based control
    Serial.println("LDR sensor enabled");
    Blynk.virtualWrite(V3, 1);  // Update Blynk to show LDR ON
  } else {
    ldrEnabled = false; // Disable LDR-based control
    Serial.println("LDR sensor disabled");
    Blynk.virtualWrite(V3, 0);  // Update Blynk to show LDR OFF
    resetSystem();  // Reset system to LED OFF state when LDR is disabled
  }
}

// Function to check ambient light and control the LED automatically
void checkLight() {
  if (manualLEDControl) {
    Serial.println("Manual override active, skipping LDR check.");
    return;
  }

  if (!ldrEnabled) {
    Serial.println("LDR sensor disabled, skipping LDR check.");
    return;
  }

  int ldrValue = analogRead(LDR_PIN);  // Read the LDR sensor value (0-4095)
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Send LDR value to Blynk app (Virtual Pin V4)
  Blynk.virtualWrite(V4, ldrValue);

  // Set a threshold for high light (adjust as necessary)
  int lightThreshold = 2000;

  if (ldrValue < lightThreshold) {
    // Dark environment detected, turn off the LED
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V2, 0);  // Update Blynk to show LED OFF
    Serial.println("Dark environment detected - LED OFF");
  } else {
    // Light environment detected, turn on the LED
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(V2, 1);  // Update Blynk to show LED ON
    Serial.println("Light environment detected - LED ON");
  }
}

// Function to reset the system to the default state
void resetSystem() {
  manualLEDControl = false; // Disable manual override for LED

  // Turn off the LED
  digitalWrite(LED_PIN, LOW);

  // Update Blynk
  Blynk.virtualWrite(V2, 0);  // Update Blynk to show LED OFF
  
  Serial.println("System reset to default state");
}

void setup() {
  Serial.begin(115200);

  // Set the LED as output
  pinMode(LED_PIN, OUTPUT);

  // Start Blynk connection
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Checking the light level periodically (every 1 second)
  timer.setInterval(1000L, checkLight);
}

void loop() {
  Blynk.run();    // Run the Blynk library
  timer.run();    // Run the timer
}
