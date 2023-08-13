#include <WiFi.h>//Library for Wifi connection on Webserver for Arduino
#include <WiFiClient.h>//Wifi client is any device that can connect to a network
#include <WebServer.h>//Library for access to js server file

const char* ssid = "TKZ-10";
const char* password = "Careful11";
const int analogPin = 4;//Connects to Analog Pin 4 (output)

WebServer server(80);

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;//rounding formula for analogue value
}//Scaling of voltages to 12 bit

void handleVoltageRequest() {//getting data from potentiometer and converting to whole number
  int analogValue = analogRead(analogPin);
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);//12 bit scaling 0-4095

  String response = String(analogValue) + "," + String(voltage, 2);//String Interpolation Answer
  server.send(200, "text/plain", response);
}

void setup() {
  Serial.begin(115200);//Baud Rate to begin Serilization at

  WiFi.begin(ssid, password);//wifi network and password to access are correct then confirm to console
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");//Messages to serial moniter to debug whether or not connected
  }
  Serial.println("Connected to WiFi!");//Confirms whether ESP32 is connected to network

  server.on("/api/voltage", handleVoltageRequest);//Following url signposts after intial HTTP address
  server.begin();
  Serial.println("HTTP server started");//Debug to see if server 
}

void loop() {
  server.handleClient();//https client handler looped so server continues recieving data from ESP
}
