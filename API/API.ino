#include <HTTPClient.h>  //Library for HTTP requests
#include <WiFi.h>        //WiFi library
#include <WiFiClient.h>
#include <WebServer.h>    //Library for connecting to webserver
#include <ArduinoJson.h>  //JSON functions Library

const char* ssid = "TKZ-10";
const char* password = "Careful11";
const int analogPin = 4;

WebServer server(80);

// Function to map the analog value to the voltage range
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Handler for the "/api/voltage" route
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

  // Send the JSON response
  server.send(200, "application/json", jsonString);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Define the route handler
  server.on("/api/voltage", handleVoltageRequest);

  // Start the HTTP server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int analogValue = analogRead(analogPin);
    float voltage = floatMap(analogValue, 0, 4095, 0, 3.3) / 1000.0;

    // Create JSON data to send to the server
    String jsonData = "{\"analogValue\":" + String(analogValue) + "}";

    // Create an HTTP client instance
    HTTPClient http;

    // Define the server URL including the route
    String serverUrl = "http://" + WiFi.localIP().toString() + "/api/voltage";

    // Add headers and begin the HTTP request
    http.addHeader("Content-Type", "application/json");
    http.begin(serverUrl);

    // Send the POST request and get the response code
    int httpCode = http.POST(jsonData);

    // Check the response code
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("HTTP Response: " + payload);
    } else {
      Serial.println("Error on HTTP request");
    }

    // Close the HTTP connection
    http.end();
  } else {
    Serial.println("Connection Lost");
  }

  delay(10000);           // Delay for 10 seconds before sending the next data
  server.handleClient();  // Continue handling client requests for the HTTP server
}


