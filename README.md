# ESP32 LED Webserver &nbsp; <img src="https://github.com/user-attachments/assets/97268fe2-313f-4554-be48-3f112f8b0747" width="40" height="40" align="top" />

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
1. Build the simple circuit below:
<p align="center">
  <img width="500" alt="circuit-schematic" src="https://github.com/user-attachments/assets/5e363a8a-1a8d-4217-ac6b-e683f536464c" />
</p>

3. Import the project folder in **VS Code** with **platformIO** (platformio.ini must be in root)
4. Navigate to `src/main.cpp` and fill in your WIFI details (lines 8-13)
5. From the plugins bar, navigate to `PlatformIO > Upload Filesystem Image`, and run it to upload the website to the esp32
6. Connect your ESP32 via USB and upload the project
7. Open the serial monitor and connect to the IP mentioned using your browser
8. Send commands via the terminal interface and enjoy! 

## Possible Commands
`led red 100ms` ⇒ Turns on red LED for 100ms <br>
`led blue 10s blink` ⇒ Repeatedly blinks blue LED every 10s<br>
`led all 5` ⇒ Turns on all LEDs for 5s <br>
`led all 2 blink` ⇒ Repeatedly blinks all LEDs every 2s<br>
`led all 1s pattern` ⇒ Blinks the LEDs  a staggered offset pattern every 1s <br>

---

###### thanks for reading


