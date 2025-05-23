#ifndef SENSOR_H
#define SENSOR_H

#define HAND_TRIG_PIN 26
#define HAND_ECHO_PIN 25
#define TRASH_TRIG_PIN 5
#define TRASH_ECHO_PIN 18
#define MAX_HEIGHT 20.0 
#define FULL_THRESHOLD 80.0

float trashLevel = 0.0;

void setupSensors() {
  pinMode(HAND_TRIG_PIN, OUTPUT);
  pinMode(HAND_ECHO_PIN, INPUT); 
  pinMode(TRASH_TRIG_PIN, OUTPUT);
  pinMode(TRASH_ECHO_PIN, INPUT);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

float getHandDistance() {
  float distance = getDistance(HAND_TRIG_PIN, HAND_ECHO_PIN);
  Serial.print("Khoảng cách tay: ");
  Serial.println(distance);
  return distance;
}

float getTrashDistance() {
  float distance = getDistance(TRASH_TRIG_PIN, TRASH_ECHO_PIN);
  Serial.print("Khoảng cách rác: ");
  Serial.println(distance);
  return distance;
}

void updateTrashLevel() {
  float distance = getTrashDistance();
  trashLevel = ((MAX_HEIGHT - distance) / MAX_HEIGHT * 1.00) * 100;
  if (trashLevel < 0) trashLevel = 0;
  if (trashLevel > 100) trashLevel = 100;
}

float getTrashLevel() {
  return trashLevel;
}

float getFullThreshold() {
  return FULL_THRESHOLD;
}

#endif