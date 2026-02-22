#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>


enum LED {
  WHITE = 15,
  GREEN = 2,
  RED = 4,
  BLUE = 5
};

const int ledPins[] = {WHITE, GREEN, RED, BLUE};

const char* ssid = "LIVING";
const char* password = "CAEE22FF";
const int port = 80;

AsyncWebServer server(port);

//Forward declarations
void setLED(int pin, bool state);
void toggleLED(int pin);
String handleInput(String input);
void handleRequest(AsyncWebServerRequest* request);

void setupLEDPins() {

  for (int pin : ledPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

}

void setup() {
  Serial.begin(115200);

  // Setup LED pin
  setupLEDPins();

  Serial.printf("Connecting to: %s", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize SPIFFS
  SPIFFS.begin(true);

  // Serve static files from SPIFFS
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  // Handle command endpoint
  server.on("/command", HTTP_POST, handleRequest);

  // Start server
  server.begin();
  Serial.println("\nHTTP Server Started!");
  Serial.print("WIFI CONNECTED: ");
  Serial.println(WiFi.localIP());
}

void setLED(int pin, bool state) {
  digitalWrite(pin, state);
}

void toggleLED(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

String handleInput(String input) {

  String response{"Invalid Command, try \'help\' for a full list of commands."};

  if (input == "white") {
    toggleLED(WHITE);
  } else if (input == "green") {
    toggleLED(GREEN);
  } else if (input == "red") {
    toggleLED(RED);
  } else if (input == "blue") {
    toggleLED(BLUE);
  }

  return response;
}

void handleRequest(AsyncWebServerRequest* request) {
  
  String command = request->getParam("cmd")->value();
  
  Serial.printf("[REQUEST] Received command: '%s'\n", command.c_str());
  
  String response = handleInput(command);
  
  Serial.printf("[RESPONSE] %s\n", response);
  
  request->send(200, "text/plain", response);
}

void loop() {
  //no need to use this loop lol
}

