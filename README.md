# NRXN Car

An ESP32-based **WiFi Controlled ROBO Car** that can be controlled directly from any phone or laptop browser . The ESP32 creates its own WiFi access point and serves a control webpage with Forward, Backward, Left, Right, Stop buttons and a live speed slider to change the speed of the car.
## Why i made this car ?
I made this car because i really wanna build a remote control car from the childhood that runs with my own code and which code can be changed by me .. i really wanna make the car with my own hands so i built it .

## The ROBO Supports

- Forward and Backward Movement
- Left and Right Turning
- Stop Command
- Live Speed Control (0-255 via web slider)
- Browser-based control (no app install needed) 

## Features

-Can walk forward ,Backward ,Left and Right

## Hardware Required

- ESP32 Devkit V1
- L298N (or L293D) Motor Driver
- TT Motors ( BO Motor )
- A Chassis (i made it by hand of ply wood)
- Battery Holder
- Battery
- Jumper Wires and some of wires

## Pin Configuration

| ESP32 Pin | Function |
|-----------|----------|
| D13 | ENA (Left Motor PWM) |
| D12 | IN1 |
| D14 | IN2 |
| D15 | ENB (Right Motor PWM) |
| D27 | IN3 |
| D26 | IN4 |

## How It Works

1. Flash the code to the ESP32 via PlatformIO.
2. On boot, the ESP32 creates its own WiFi network:
   - **SSID:** `Niranjan Robo car`(You Can Change it later 😉)
   - **Password:** `12345678`
3. Connect your phone/laptop to that network.
4. Open a browser and go to `192.168.4.1`
5. Use the on-screen buttons to drive, and the slider to adjust speed live.

**Note:** Since the ESP32 hosts its own access point, there's no internet access while connected , this is a local-only control link between your device and the car.

## Libraries Used

- Arduino Framework
- WiFi (ESP32)
- WebServer (ESP32)
- PlatformIO

## Schematic
![Schematic](https://github.com/niranjansthaa11-code/NRXN-ROBO-CAR/blob/master/Skematics/Schematic_Bot_Car_2026-08-12.png)

## Bill of Materials (BOM)
See [BOM.md](./BOM.md) for full parts list with quantities and specs.

## Images
![Robo car image ](https://github.com/niranjansthaa11-code/NRXN-ROBO-CAR/blob/master/Images/1.jpg)

## Known Issues
- L298N runs hot after a few minutes of continuous use(heat sink should be used
<br>
<hr>
<p><b>Made with Love <3</b></p>
