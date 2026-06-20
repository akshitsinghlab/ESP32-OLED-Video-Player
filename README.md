# ESP32 OLED Video Player

Play monochrome videos on a 128x64 SSD1306 OLED using ESP32 and LittleFS.

## Features

- SSD1306 OLED support
- LittleFS storage
- Frame-by-frame playback
- Automatic looping
- ESP32 compatible

## Hardware

- ESP32
- SSD1306 OLED

## Wiring

| OLED | ESP32 |
|-------|-------|
| SDA | GPIO21 |
| SCL | GPIO22 |
| VCC | 3.3V |
| GND | GND |

## Installation

1. Clone repository
2. Install libraries
3. Upload LittleFS image
4. Flash firmware
5. Reboot ESP32

## Converting Videos

Follow the guide in `/docs`.


## Credits
Inspired by and based on the ESP32 Video Display project by Younes Makhchan. Modified and adapted for SSD1306 OLED playback and LittleFS usage.
Video conversion workflow inspired by:
https://github.com/younes-makhchan/ESP32_Video_Display

## Author

Akshit Builds
Instagram: @akshit.builds
