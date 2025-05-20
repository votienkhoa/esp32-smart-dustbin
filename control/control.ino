// Blynk IoT configuration
#define BLYNK_TEMPLATE_ID "TMPL6i_TCZ76N"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"
#define BLYNK_AUTH_TOKEN "uGbbs_ebUn2KrFNfmvfFqj8BZmYWAmf0"

// Comment out to disable Blynk debug prints
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Wi-Fi credentials
char ssid[] = "TIEN KHOA";
char pass[] = "0905029920";

// Pin definitions
#define TRIG_PIN 5    // HC-SR04 TRIG
#define ECHO_PIN 18   // HC-SR04 ECHO
#define SERVO_PIN 19  // Servo SIGNAL

Servo servo;
const float maxHeight = 30.0; // Trash can height (cm), adjust as needed
const float fullThreshold = 80.0; // Full threshold (%)
bool lidOpen = false; // Lid state

void setup() {
  Serial.println("Begin");
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize servo
  servo.attach(SERVO_PIN);
  servo.write(0);
  Serial.println("Setup complete 1");

  // Connect to Wi-Fi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Setup complete");
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // Calculate distance (cm)
  return distance;
}

void loop() {
  Blynk.run();
  float distance = getDistance();

  // Detect hand to open lid
  if (distance < 10 && distance > 0 && !lidOpen) {
    servo.write(90); // Open lid
    lidOpen = true;
    delay(3000); // Wait 3 seconds
    servo.write(0); // Close lid
    lidOpen = false;
    delay(1000); 
  }

  if (!lidOpen) {
    float trashLevel = ((maxHeight - distance) / maxHeight) * 100; // Calculate percentage
    if (trashLevel < 0) trashLevel = 0; // Limit value
    if (trashLevel > 100) trashLevel = 100;

    Blynk.virtualWrite(V1, trashLevel); 
    Serial.println(trashLevel);
    if (trashLevel >= fullThreshold) {
      Blynk.logEvent("trash_full", "Trash can is full! Please empty it.");
      delay(10000); 
    }
  }

  delay(500); 
}