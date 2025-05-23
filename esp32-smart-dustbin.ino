#include <WiFi.h>
#include "config.h"
#include "hc-sr04.h"
#include "servo.h"
#include "web_server.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Khởi động...");

  // Kết nối Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("Kết nối WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi đã kết nối");
  Serial.print("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());

  // Khởi động các thành phần
  setupSensors();
  setupWebServer();
  setupServo();
  Serial.println("Khởi động hoàn tất");
}

void loop() {
  handleWebServer();

  float handDistance = getHandDistance();
  if (handDistance < 10 && handDistance > 0 && !isLidOpen()) {
    Serial.println("Phát hiện tay, mở nắp");
    openLid();
    delay(3000);
    closeLid();
    Serial.println("Đóng nắp");
    delay(1000);
  }

  if (!isLidOpen()) {
    updateTrashLevel();
    Serial.print("Mức rác: ");
    Serial.println(getTrashLevel());
  }

  delay(500);
}