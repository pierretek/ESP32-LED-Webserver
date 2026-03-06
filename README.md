# ESP32 LED Webserver &nbsp;<img src="data/favicon.png" style="vertical-align: bottom;" width="40" />
An asynchronous webserver hosted on an ESP32 that controls an array of four LEDs using a browser based terminal interface
 
## Details 
- Main program is in `src/main.cpp`, project libraries are in `lib/` and the web interface is in `data/`.
- The ESP32 hosts an asynchronous webserver that recieves commands and periodically sends watchdog signals
- Check out the [demo page!](https://pierretek.github.io/ESP32-LED-Webserver/)


## Requirements 

### Hardware
- `ESP32 WROOM 32`
- Four uniquely colored `LEDs`
- Four `220Ω` resistors
- Breadboard and connector wires
### Software
- VS Code with the platformIO extension

## How to Use
1. Import the project folder in VS Code with platformIO (platformio.ini must be in root)
2. Navigate to `src/main.cpp` and fill in your WIFI details (lines 8-13)
3. From the plugins bar, navigate to `PlatformIO > Upload Filesystem Image`, and run it to upload the website to the esp32
4. Connect your ESP32 via USB and upload the project
5. Open the serial monitor and connect to the IP mentioned using your browser
6. Send commands via the terminal interface and enjoy! 

## Possible Commands
`led red 100ms` ⇒ Turns on red LED for 100ms <br>
`led blue 10s blink` ⇒ Repeatedly blinks blue LED every 10s<br>
`led all 5` ⇒ Turns on all LEDs for 5s <br>
`led all 2 blink` ⇒ Repeatedly blinks all LEDs every 2s<br>
`led all 1s pattern` ⇒ Blinks the LEDs  a staggered offset pattern every 1s <br>

---

###### thanks for reading


