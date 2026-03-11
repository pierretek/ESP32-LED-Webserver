#pragma once

#include <map>
#include <vector>

//Pairing each LED color to their physical pin
enum LEDPins {
	WHITE = 5,
	GREEN = 2,
	RED = 15,
	BLUE = 4,
	ALL = 0
};

//LED object
struct LED {
	bool isOn{false}; //on status
	bool isBlinking{false}; //if the LED should blink
	int blinkInterval{0}; //time between blinks
	unsigned long durationEnd{0}; //sheduled time to end
	unsigned long nextDuration{0}; //scheduled time to start

	LED() {};
};

//map of pin numbers to LED objects
inline std::map<int, LED> leds = {
	{WHITE, LED()},
	{GREEN, LED()},
	{RED,   LED()},
	{BLUE,  LED()}
};

//Actual order of the LEDs
inline std::vector<int> ledOrder = {WHITE, BLUE, GREEN, RED};

//Forward declarations (ledManager.cpp)
void setupLEDPins();
void setLEDPin(int pin, bool state);
void toggleLED(int pin);
void setLEDState(int pin, long duration, bool blinking);
void updateLEDs();
void clearLEDState(int pin);
void setLEDPattern(long duration);
