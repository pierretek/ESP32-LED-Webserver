#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <map>
#include "ledManager.h"


//Forward Declarations (inputHandler.cpp)
void handleCommand(AsyncWebServerRequest* request);
void sendHeartBeat(AsyncWebServerRequest* request);
String handleInput(String input);
std::vector<String> parseArgs(String input);
int getLEDColor(String arg);
double getLEDDuration(String arg);



