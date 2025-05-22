#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <ESP32Servo.h>

#define SERVO1_PIN 19
#define SERVO2_PIN 21

Servo servo1;
Servo servo2;
bool lidOpen = false;

void setupServo() {
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo1.write(0);
  servo2.write(0);
}

void openLid() {
  servo1.write(90);
  servo2.write(90);
  lidOpen = true;
}

void closeLid() {
  servo1.write(0);
  servo2.write(0);
  lidOpen = false;
  Serial.println("Đóng nắp: Hai servo chạy");
}

bool isLidOpen() {
  return lidOpen;
}

#endif