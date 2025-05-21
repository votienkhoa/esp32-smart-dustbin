#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncWebServer.h>
#include "sensor.h"

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Smart Dustbin</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; }
    h1 { color: #333; }
    .gauge { font-size: 24px; margin: 20px; }
    .status { font-size: 18px; color: #555; }
    .full { color: red; font-weight: bold; }
  </style>
</head>
<body>
  <h1>Smart Dustbin</h1>
  <div class="gauge">Bin Level: <span id="trashLevel">0</span>%</div>
  <div class="status">Status: <span id="status">Bình thường</span></div>
  <script>
    function updateData() {
      fetch('/data').then(response => response.json()).then(data => {
        document.getElementById('trashLevel').innerText = data.trashLevel.toFixed(1);
        document.getElementById('status').innerText = data.status;
        if (data.status === 'Full') {
          document.getElementById('status').classList.add('full');
        } else {
          document.getElementById('status').classList.remove('full');
        }
      });
    }
    setInterval(updateData, 2000);
    updateData();
  </script>
</body>
</html>)rawliteral";

void setupWebServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = "{\"trashLevel\":" + String(getTrashLevel(), 1) + ",\"status\":\"" + (getTrashLevel() >= getFullThreshold() ? "Đầy" : "Bình thường") + "\"}";
    request->send(200, "application/json", json);
  });
  server.begin();
  Serial.println("Web server started");
}

void handleWebServer() {
  
}

#endif