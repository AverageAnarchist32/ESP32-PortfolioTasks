#include <WiFi.h>//Library for Wifi connection on Webserver for Arduino
#include <WiFiClient.h>//Wifi client is anyt device that can connect to a network
#include <WebServer.h>

const char* ssid = "CGS-BYOD";
const char* password = "Carefful11well";
const int analogPin = 4;

WebServer server(80);

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;//rounding formula for analogue value
}

void handleVoltageRequest() {//getting data from potentiometer and converting to whole number
  int analogValue = analogRead(analogPin);
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

  String response = String(analogValue) + "," + String(voltage, 2);
  server.send(200, "text/plain", response);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);//wifi network and password to access are correct then confirm to console
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  server.on("/api/voltage", handleVoltageRequest);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();//https clinent handler looped 
}
