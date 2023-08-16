#include <WiFi.h>//Library for Wifi connection on Webserver for Arduino
#include <WiFiClient.h>//Wifi client is any device that can connect to a network
#include <WebServer.h>//Library for access to js server file

#include <ArduinoJson.h> // Include the ArduinoJson library

const char* ssid = "TKZ-10";
const char* password = "Careful11well";
const int analogPin = 36;

WebServer server(80);

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void handleVoltageRequest() {
  int analogValue = analogRead(analogPin);
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

  // Create a JSON object
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["analogValue"] = analogValue;
  jsonDoc["voltage"] = voltage;

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  server.send(200, "application/json", jsonString); // Set the content type to JSON
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);//wifi network and password to access are correct then confirm to console
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");//Messages to serial moniter to debug whether or not connected
  }
  Serial.println("Connected to WiFi!");//Confirms whether ESP32 is connected to network

  
    // Define the server URL including the route
  String serverUrl = "http://" + WiFi.localIP().toString() + "/api/voltage";

  server.on("/api/voltage", handleVoltageRequest);//Following url signposts after intial HTTP address
  server.begin();
  Serial.println("HTTP server started");//Debug to see if server logs request
}

void loop() {
  server.handleClient();//https client handler looped so server continues recieving data from ESP
}

