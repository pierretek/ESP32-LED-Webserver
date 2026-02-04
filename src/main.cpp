#include <Arduino.h>
#include <Wifi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "LIVING";
const char* password = "CAEE22FF";
const int port = 80;

AsyncWebServer server(port);  // Changed from NetworkServer

void setup() {
  Serial.begin(115200);

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

    // Start server
  server.begin();
  Serial.println("\nHTTP Server Started!");
  Serial.print("WIFI CONNECTED: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  //nothing needed here for now

  // WiFiClient client = server.available();


  // if (client) {
  //   Serial.println("New Client!")
  // }
}

