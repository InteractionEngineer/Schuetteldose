**Context**
This repository holds the "firmware" for a digitalized spray can and supplements the main repo at https://github.com/InteractionEngineer/SprayAR
See intstructions below to learn about how we build the spray can.

# Firmware

We are working with an Adafruit HUZZAH32 - ESP32 Feather Board. Find it's documentaion here: https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview

## How to contribute

* Clone this repo
* Download Arduino IDE
* Open any .ino file of this repo in that Arduino IDE
* Navigate to Tools > Board […] > Board Management > select and install ESP32
* Choose Tools > Board […] > Adafruit ESP32 Feather
* Download necessary libraries
* Start programming

## Note

The ESP32 uses a fair amount of current, so if you're getting flakey behavior make sure you are plugging your console cable into either a motherboard USB port or a powered USB hub. Don't use the 'extra' USB port on your monitor or keyboard.

# Hardware

## What to get

For one controller (spray can) you need theses parts:
* microcontroller ‘HUZZAH32 - ESP32 Feather Board’
  * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/3405?qs=sGAEpiMZZMuqBwn8WqcFUj2aNd7i9W7uSZjXap7f6kc9F64rOxbbhw%3D%3D), Adafruit 3405
* micro USB extension cable
  * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/3258?qs=0X/VfLRQkeNhaqgEgABzjA%3D%3D), Adafruit 3258
* _optional:_ position sensor 9-DOF orientation ‘IMU Fusion Breakout - BNO085’
  * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/4754?qs=hd1VzrDQEGjjfej09NGRTw%3D%3D), Adafruit 4754
* _optional:_ touch sensor - button ‘Momentary Capacitive Touch SNSR Breakout’
  * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/1374?qs=GURawfaeGuBM%252BW52u31eLw%3D%3D), Adafruit 1374
* circular vibrating motor ‘Vibrating Mini Motor Disc’
  * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/1201?qs=GURawfaeGuD/75V/XdSvMw%3D%3D), Adafruit 1201
* motor controller ‘DRV2605L Haptic Motor Controller’
  * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/2305?qs=GURawfaeGuAbGO9ndi1lpg%3D%3D), Adafruit 2305
* battery ‘18650 3.7V 2600mAh with BMS’
 * @[Conrad](https://www.conrad.de/de/p/keeppower-1s1p-18650-2600mah-li-ion-akku-mit-bms-schutz-18650-26j-kabel-und-stecker-836099468.html) - Keeppower 1S1P18650
* choose a pressure sensor that fits your spring:
  * pressure sensor ‘Round High Force Sensitive Resistor (FSR) - 1 - 100 Newton’
    * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/5475?qs=mELouGlnn3ceocbOvsWz0A%3D%3D), Adafruit 5475
  * pressure sensor ‘Round Force Sensitive Resistor (FSR) - 0.3 - 10 Newton’
    * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/166?qs=GURawfaeGuBZazGyM1uUyQ%3D%3D), Adafruit 166
* switch with LED ‘Rugged Metal On/Off Switch with Green LED Ring, 16 mm’
  * [@Mouser](https://www.mouser.de/ProductDetail/Adafruit/482?qs=GURawfaeGuCSwD3nFtDjxw%3D%3D), Afafruit 482
* From your own stock: spray can, pressure coil spring, resistors, cables, connectors, 3D printing filament, solder, etc.

## What to print



## How to build it



## Known issues
* The 9-DOF Sensor is not utilized yet but will be helpful when we implement a virtual representation of the spray can in Unity.
* The touch sensor recalibrates itslef after a while so it can not check for "grab duration" as intendet - it's better for detecting changes.
