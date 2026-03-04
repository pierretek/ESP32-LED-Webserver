#include "inputHandler.h"

//Helper function to recieve command input and send response back to webserver
void handleCommand(AsyncWebServerRequest* request) {

	String command = request->getParam("cmd")->value();
	String response = handleInput(command);

	request->send(200, "text/plain", response);
}

//Helper function to respond to watchdog requests
void sendHeartBeat(AsyncWebServerRequest* request) {
	request->send(200, "text/plain", "ok");
}

//Function to recieve command string and perform the appropiate actions
// 'led red 100s blink'
String handleInput(String input) {

	//Parsing the arguments
	std::vector<String> args = parseArgs(input);

	if (args[0] != "led") return "Invalid Command, try \'help\' for a full list of commands.";
	if (args.size() < 3) return "Error: not enough arguments (led &ltcolor&gt &ltduration&gt &ltblink&gt)";


	//Parsing the LED color
	int pin = getLEDColor(args[1]);

	if (pin == -1) {
		return "Error: Invalid color provided, try again (red|green|blue|white|all)";
	}

	//Parsing the LED duration
	double duration = getLEDDuration(args[2]);

	switch (static_cast<int>(duration)) {
		case -1:
			return "Error: invalid duration, try again (eg. 5, 10s, 100ms)";
		case -2:
			return "Error: cannot have negative time values";
		case -3:
			return "Error: time value is way too large (max 3600s)";
	}

	//detecting if user selects blinking or pattern
	bool blinking{false};
	bool pattern{false};

	if (args.size() >= 4) {
		blinking = (args[3] == "blink");
		pattern = (args[3] == "pattern");
	}

	String durationText = (args[2].charAt(args[2].length() - 2) == 'm' ?
		String(duration) + " milliseconds" : String(duration / 1000) + " seconds");

	//Actually applying user choices
	args[1].toUpperCase();

	if (pattern) {

		setLEDPattern(duration);
		return "Success! Set ALL leds to a pattern every " + durationText;
	}


	setLEDState(pin, duration, blinking);
	return "Success! Set " + args[1] + " led(s)" +
		+(blinking ? " to blink every " : " to ON for ") + durationText;

}


//Helper function to extract the time duration from the argument string
double getLEDDuration(String arg) {

	//rejecting invalid inputs
	if (arg.charAt(0) == '-') return -2;
	if (!isDigit(arg.charAt(0))) return -1;

	double timeValue{};

	if (arg.endsWith("ms")) {
		timeValue = arg.substring(0, arg.length() - 2).toDouble();

	} else if (arg.endsWith("s")) {
		timeValue = arg.substring(0, arg.length() - 1).toDouble() * 1000;

	} else {
		timeValue = arg.toDouble() * 1000;
	}

	if (timeValue > 3600 * 1000) return -3;

	return timeValue;

}

//Helper function to convert the color string into a usable pin number
int getLEDColor(String arg) {

	arg.trim();

	// Serial.printf("Color parsed: \"%s\"", arg);

	static std::map<String, int> ledColors = {
	{"white", WHITE},
	{"green", GREEN},
	{"red",   RED},
	{"blue",   BLUE},
	{"all",   ALL}
	};

	for (auto& [color, pin] : ledColors) {
		if (arg.equals(color)) return pin;
	}

	//returning -1 if the color is invalid
	return -1;

}

//Helper function to tokenise a string to parse args
std::vector<String> parseArgs(String input) {

	std::vector<String> args;

	char buffer[input.length() + 1];
	input.toCharArray(buffer, sizeof(buffer));

	char* token = strtok(buffer, " ");

	while (token != nullptr) {
		args.push_back(String(token));
		token = strtok(nullptr, " ");
	}

	return args;
}
