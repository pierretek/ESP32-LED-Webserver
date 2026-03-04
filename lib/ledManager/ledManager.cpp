#include <iostream>
#include <Arduino.h>

#include "ledManager.h"

//Function to update all LEDs (called every cycle)
void updateLEDs() {

	for (auto& [pin, led] : leds) {

		//Normal mode, turn off after duration ends
		if (!led.isBlinking) {

			if (millis() > led.durationEnd) {
				led.isOn = false;
			}


		//Blinking mode, blink every x seconds
		} else {

			if (led.isOn && millis() > led.durationEnd) {
				led.isOn = false;
				led.nextDuration = millis() + led.blinkInterval;

			} else if (!led.isOn && millis() > led.nextDuration) {
				led.isOn = true;
				led.durationEnd = millis() + led.blinkInterval;
			}
		}

		//Applying the LED state
		setLEDPin(pin, led.isOn);

	}
}


//Initializing all LED pins
void setupLEDPins() {

	for (auto& [pin, led] : leds) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}

}

//Helper function to apply the LED state to the physical pin
void setLEDPin(int pin, bool state) {

	digitalWrite(pin, state);
}

//Function to assign LED states from given parameters
void setLEDState(int pin, long duration, bool blinking) {

	//Applying state to all pins
	if (pin == ALL) {

		for (auto& [pin, led] : leds) {
			leds[pin].isOn = true;
			leds[pin].durationEnd = millis() + duration;
			leds[pin].isBlinking = blinking;
			leds[pin].blinkInterval = blinking ? duration : 0;
		}


	//Applying state to single pin
	} else {
		leds[pin].isOn = true;
		leds[pin].durationEnd = millis() + duration;
		leds[pin].isBlinking = blinking;
		leds[pin].blinkInterval = blinking ? duration : 0;

	}


}

//Clearing led state
void clearLEDState(int pin) {

	leds[pin].isOn = false;
	leds[pin].durationEnd = 0;
	leds[pin].isBlinking = false;

}

//Helper function to apply a staggered pattern
void setLEDPattern(long duration) {

	int offset{0};

	//Blinking the leds with an offset
	for (int pin : ledOrder) {

		leds[pin].isOn = false;
		leds[pin].nextDuration = millis() + offset;
		leds[pin].isBlinking = true;
		leds[pin].blinkInterval = duration;

		offset += 150;
	}
}
