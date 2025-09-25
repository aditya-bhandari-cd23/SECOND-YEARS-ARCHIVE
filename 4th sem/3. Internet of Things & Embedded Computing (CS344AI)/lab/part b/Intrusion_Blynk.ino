// PIR Sensor:
// VCC → 3.3V of ESP32
// GND → GND of ESP32
// OUT → GPIO 18 of ESP32

// LED:
// Positive leg (+) → GPIO 2 of ESP32
// Negative leg (-) → GND (chota wala pin)

// Buzzer:
// Positive leg (+) → GPIO 4 of ESP32
// Negative leg (-) → GND(chota wala pin)
#define BLYNK_TEMPLATE_ID "TMPL3LiNUxhhB"
#define BLYNK_TEMPLATE_NAME "Intrusion Detection System"
#define BLYNK_AUTH_TOKEN "gxkbtkJM-55DcciQE6Vrwd0so_0g_SA2"

#include <WiFi.h> // ESP32 WiFi library
#include <BlynkSimpleEsp32.h> // Blynk library for ESP32

// Pin Definitions for ESP32
#define PIR_PIN 18
#define LED_PIN 2
#define BUZZER_PIN 4

// Replace with your WiFi credentials
char ssid[] = "Nord3";
char pass[] = "yuck12345";

// Timer for Blynk
BlynkTimer timer;

// Variables to store the state of the system
bool intrusionDetected = false;
bool manualLEDControl = false;
bool manualBuzzerControl = false;
bool pirEnabled = true; // Variable to control PIR sensor (true = enabled, false = disabled)

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

// Function to control Buzzer from Blynk button (V3)
BLYNK_WRITE(V3) {
  manualBuzzerControl = true; // Enable manual override for Buzzer
  int buzzerState = param.asInt(); // Get value from the Blynk button (0 or 1)

  if (buzzerState == HIGH) {
    // Turn on Buzzer and update Blynk status
    digitalWrite(BUZZER_PIN, HIGH);
    Blynk.virtualWrite(V3, 1);  // Update Blynk to show Buzzer ON
    Serial.println("Manual Buzzer ON");
  } else {
    // Turn off Buzzer, reset system and update Blynk status
    digitalWrite(BUZZER_PIN, LOW);
    Blynk.virtualWrite(V3, 0);  // Update Blynk to show Buzzer OFF
    Serial.println("Manual Buzzer OFF - Resetting system");
    resetSystem();
  }
}

// Function to enable/disable PIR sensor (V4)
BLYNK_WRITE(V4) {
  int pirState = param.asInt(); // Get value from the Blynk button (0 or 1)

  if (pirState == HIGH) {
    pirEnabled = true;  // Enable PIR detection
    Serial.println("PIR sensor enabled");
    Blynk.virtualWrite(V4, 1);  // Update Blynk to show PIR sensor ON
  } else {
    pirEnabled = false; // Disable PIR detection
    Serial.println("PIR sensor disabled");
    Blynk.virtualWrite(V4, 0);  // Update Blynk to show PIR sensor OFF
    resetSystem();  // Reset system to no intrusion state when PIR is disabled
  }
}

// Function to check the intrusion state and act accordingly
void checkIntrusion() {
  if (manualLEDControl || manualBuzzerControl) {
    Serial.println("Manual override active, skipping intrusion check.");
    return;
  }

  if (!pirEnabled) {
    Serial.println("PIR sensor disabled, skipping intrusion check.");
    return;
  }

  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    // Intruder detected
    intrusionDetected = true;

    // Turn on LED and Buzzer automatically
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    // Update Blynk status
    Blynk.virtualWrite(V1, 1);  // Intrusion detected (Virtual Pin V1)
    Blynk.virtualWrite(V2, 1);  // Update Blynk to show LED ON
    Blynk.virtualWrite(V3, 1);  // Update Blynk to show Buzzer ON
    
    Serial.println("Intruder Detected!");
  } else {
    // No intrusion
    intrusionDetected = false;

    // Turn off LED and Buzzer if no manual control
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    // Update Blynk status
    Blynk.virtualWrite(V1, 0);  // No intrusion detected (Virtual Pin V1)
    Blynk.virtualWrite(V2, 0);  // Update Blynk to show LED OFF
    Blynk.virtualWrite(V3, 0);  // Update Blynk to show Buzzer OFF
    
    Serial.println("No Intrusion");
  }
}

// Function to reset the system to the "no intrusion detected" state
void resetSystem() {
  // Reset manual control flags
  manualLEDControl = false;
  manualBuzzerControl = false;

  // Turn off the LED and Buzzer
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Update Blynk
  Blynk.virtualWrite(V1, 0);  // Update Blynk to show no intrusion (Virtual Pin V1)
  Blynk.virtualWrite(V2, 0);  // Update Blynk to show LED OFF
  Blynk.virtualWrite(V3, 0);  // Update Blynk to show Buzzer OFF
  
  Serial.println("System reset to no intrusion state");
}

void setup() {
  Serial.begin(115200);

  // Set the PIR, LED, and Buzzer as input/output
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Start Blynk connection
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Checking sensor periodically
  timer.setInterval(1000L, checkIntrusion);
}

void loop() {
  Blynk.run();    // Run the Blynk library
  timer.run();    // Run the timer
}
