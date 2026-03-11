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
- VS Code with the platformIO extensiona

## How to Use
1. Build the simple circuit below with the components listed above:
   
<p align="center">
  <img width="500" alt="circuit-schematic" src="https://github.com/user-attachments/assets/5e363a8a-1a8d-4217-ac6b-e683f536464c" />
</p>

2. Import the project folder in **VS Code** with **platformIO** (platformio.ini must be in root)
3. Navigate to `src/main.cpp` and fill in your WIFI details (lines 8-13)
4. From the plugins bar, navigate to `PlatformIO > Upload Filesystem Image`, and run it to upload the website to the esp32
5. Connect your ESP32 via USB and upload the project
6. Open the serial monitor and connect to the IP mentioned using your browser
7. Send commands via the terminal interface and enjoy! 

## Possible Commands
```
led red 100ms ⇒ Turns on red LED for 100ms 
led blue 10s blink ⇒ Repeatedly blinks blue LED every 10s
led all 5 ⇒ Turns on all LEDs for 5s 
led all 2 blink ⇒ Repeatedly blinks all LEDs every 2s
led all 1s pattern ⇒ Blinks the LEDs  a staggered offset pattern every 1s
```

## Bonus
Although **completely** redundant and unnecessary, I also decided to make a simple PCB for fun and to free up my breadboard for other projects. I made the PCB in KiCAD and the project files can be found under `PCBFiles/`.

### PCB Photos
<p align="center">
 <img src="https://github.com/user-attachments/assets/bb7921db-510c-4cec-9f63-857a1681a962" width="45%">
 <img src="https://github.com/user-attachments/assets/5c97f0a2-8817-4091-b2bf-864ba20aea4a" width="45%">
</p>

### Demo with PCB
https://github.com/user-attachments/assets/332d59a1-b7c1-4675-94df-a39690c8915f

---
_thanks for reading_


