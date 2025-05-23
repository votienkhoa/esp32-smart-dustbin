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
  servo1.write(180);
  servo2.write(180);
  lidOpen = true;
}

void closeLid() {
  Serial.println("Đóng nắp từ từ: Hai servo chạy");
  for (int angle = 90; angle >= 0; angle -= 2) {
    servo1.write(angle);
    servo2.write(angle);
    delay(50);
  }
  lidOpen = false;
  Serial.println("Đóng nắp hoàn tất");
}

bool isLidOpen() {
  return lidOpen;
}

#endif