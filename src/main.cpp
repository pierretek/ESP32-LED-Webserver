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

void setLED(int pin, bool state);
void toggleLED(int pin);
void handleInput(String input);

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

  // Handle 404
  server.onNotFound([](AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "Not found");
    });

    // Handle button press command
// Handle command endpoint
  server.on("/command", HTTP_POST, [](AsyncWebServerRequest* request) {

    String command = "";

    // Extract the 'cmd' parameter from the URL query string
    command = request->getParam("cmd")->value();

    // Process the command
    handleInput(command);

    // Send success response
    request->send(200, "text/plain", "Command '" + command + "' executed!");
    });

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

void handleInput(String input) {
  if (input == "white") {
    toggleLED(WHITE);
  } else if (input == "green") {
    toggleLED(GREEN);
  } else if (input == "red") {
    toggleLED(RED);
  } else if (input == "blue") {
    toggleLED(BLUE);
  }
}

void loop() {

}


