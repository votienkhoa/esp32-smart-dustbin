#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <ESP32Servo.h>

#define SERVO_PIN 19

Servo servo;
bool lidOpen = false;

void setupServo() {
  servo.attach(SERVO_PIN);
  servo.write(0);
}

void openLid() {
  servo.write(180);
  lidOpen = true;
}

void closeLid() {
  servo.write(0);
  lidOpen = false;
}

bool isLidOpen() {
  return lidOpen;
}

#endif