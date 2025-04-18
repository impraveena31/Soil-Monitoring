#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// WiFi Credentials
const char* ssid = "impraveena";  
const char* password = "abcdefgh";  

WebServer server(80);
double moistureLevel;
bool serialEnabled = true; // Flag to control Serial printing

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connected to WiFi!");
    Serial.print("📡 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi Connection Failed! Check SSID/Password.");
  }
}

void setup() {
  pinMode(34, INPUT);  // ADC pin
  Serial.begin(115200);

  connectWiFi();  // Call WiFi connection function

  server.on("/data.txt", []() {
    double sensorValue = analogRead(34);
    moistureLevel = (sensorValue / 4095.0) * 100;  // ✅ Corrected formula
    String text = String(moistureLevel) + "%";
    server.send(200, "text/html", text);
  });

 server.on("/", []() {
    String page = "<!DOCTYPE html><html><head>";
    page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; text-align: center; background-color: #1e1e2e; color: white; padding: 20px; }";
    page += "h1 { font-size: 28px; color: #00ccff; }";
    page += ".container { max-width: 500px; margin: auto; padding: 20px; background: #29293d; border-radius: 10px; box-shadow: 0px 0px 10px rgba(0, 255, 255, 0.3); }";
    page += ".status { font-size: 20px; margin-top: 10px; font-weight: bold; }";
    page += ".gauge { width: 200px; height: 100px; position: relative; margin: auto; }";
    page += ".gauge::after { content: ''; width: 200px; height: 100px; background: conic-gradient(#ff0000 0%, #ffaa00 30%, #00ff00 100%); display: block; border-radius: 100px 100px 0 0; }";
    page += "#moisture { font-size: 24px; margin-top: 10px; font-weight: bold; }";
    page += "</style>";
    page += "</head><body>";

    page += "<h1>Soil Moisture Monitoring</h1>";
    page += "<div class='container'>";
    page += "<h2>Moisture Level</h2>";
    page += "<div class='gauge'></div>";
    page += "<p id='moisture'>Loading...</p>";
    page += "<p class='status' id='status'>Checking soil condition...</p>";
    page += "</div>";

    page += "<script>";
    page += "function updateData() {";
    page += "fetch('data.txt').then(response => response.text()).then(data => {";
    page += "document.getElementById('moisture').innerHTML = data;";
    page += "let value = parseFloat(data);";
    page += "let status = document.getElementById('status');";
    page += "if (value >= 60) { status.innerHTML = 'Soil is good!'; status.style.color = '#00ff00'; }";
    page += "else { status.innerHTML = 'Needs Watering!'; status.style.color = '#ff4444'; }";
    page += "});";
    page += "}";
    page += "setInterval(updateData, 1000);";
    page += "</script>";

    page += "</body></html>";

    server.send(200, "text/html", page);
});


  server.begin();
  Serial.println("🌍 Web server started! Access it via your IP above.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("STOP")) {
      serialEnabled = false;
      Serial.println("⛔ Stopping Serial Output!");
    } else if (command.equalsIgnoreCase("START")) {
      serialEnabled = true;
      Serial.println("✅ Resuming Serial Output!");
    }
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("🔄 WiFi Lost! Reconnecting...");
    connectWiFi();
  }

  double sensorValue = analogRead(34);
  moistureLevel = (sensorValue / 4095.0) * 100;  // ✅ Corrected calculation

  if (serialEnabled) {
    Serial.print("🔢 Raw ADC Value: ");
    Serial.println(sensorValue);
    Serial.print("💧 Corrected Moisture Percentage: ");
    Serial.println(moistureLevel);

    if (moistureLevel >= 60) {
      Serial.println("✅ Soil is good");
    } else {
      Serial.println("🚰 Needs watering");
    }
  }

  server.handleClient();
  delay(1000);
}
