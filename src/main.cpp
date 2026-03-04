#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include "ledManager.h"
#include "inputHandler.h"

const char* ssid = "WIFI_NAME"; //CHANGE THIS
const char* password = "WIFI_PASSWORD"; //CHANGE THIS
const int port = 80; //no need to change

//ip address 
IPAddress gateway(192, 168, 68, 1); //CHANGE THIS
IPAddress subnet(255, 255, 255, 0); //CHANGE THIS
IPAddress websiteIP(192, 168, 68, 180); //website's ip, no need to change

AsyncWebServer server(port);

//Function to set up and connect to WIFI
void setupWIFI() {

  Serial.printf("Connecting to: %s", ssid);
  WiFi.config(websiteIP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWIFI CONNECTED! ");
  Serial.print("Connect to: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  // Setup LED pins and WIFI
  setupLEDPins();
  setupWIFI();

  // Initialize storage
  SPIFFS.begin();

  //Serving the static website
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Asynchronously handle incoming messages 
  server.on("/command", HTTP_GET, handleCommand);
  server.on("/ping", HTTP_GET, sendHeartBeat);

  // Start server
  server.begin();
}

//Main Loop
void loop() {
  updateLEDs();
}

