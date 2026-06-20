# ESP32 OLED Video Player 🎬📟

Play monochrome videos on a 128×64 SSD1306 OLED display using an ESP32 and LittleFS.

This project stores a pre-converted video file (`video.bin`) inside the ESP32's flash memory using LittleFS and plays it back frame-by-frame on a 0.96" OLED display.

---

## ✨ Features

- SSD1306 OLED Video Playback
- LittleFS File Storage
- Automatic Video Looping
- ESP32 Compatible
- Lightweight and Easy to Use
- Supports Custom Videos

---

## 🛠 Hardware Required

| Component | Quantity |
|------------|------------|
| ESP32 Development Board | 1 |
| SSD1306 128×64 OLED Display | 1 |
| USB Cable | 1 |

---

## 🔌 Wiring

| OLED Pin | ESP32 Pin |
|-----------|-----------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## 📦 Software Requirements

- Arduino IDE 2.x
- ESP32 Board Package
- Adafruit SSD1306 Library
- Adafruit GFX Library
- LittleFS Upload Extension

---

# 🚀 Installation Guide

## 1. Install ESP32 Board Support

Open Arduino IDE:

```text
File → Preferences
```

Add the following URL to **Additional Board Manager URLs**:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

Then:

```text
Tools → Board → Boards Manager
```

Search:

```text
esp32
```

Install:

```text
esp32 by Espressif Systems
```

---

## 2. Install Required Libraries

Open:

```text
Sketch → Include Library → Manage Libraries
```

Install:

- Adafruit SSD1306
- Adafruit GFX Library

---

## 3. Install LittleFS Upload Extension

Arduino IDE does not include LittleFS upload support by default.

Follow the installation guide:

https://randomnerdtutorials.com/arduino-ide-2-install-esp32-littlefs/

After installation, restart Arduino IDE.

---

## 4. Project Structure

Your project should look like this:

```text
ESP32-OLED-Video-Player
│
├── data
│   └── video.bin
│
└── ESP32_OLED_Video_Player.ino
```

**Important:**  
The `video.bin` file must be placed inside the `data` folder.

---

## 5. Upload video.bin to LittleFS

Connect your ESP32.

Open the project in Arduino IDE.

Press:

```text
Ctrl + Shift + P
```

Search for:

```text
Upload LittleFS to Pico/ESP32
```

or

```text
Upload Filesystem Image
```

(depending on your extension version)

Wait until the upload completes successfully.

---

## 6. Upload Firmware

Select:

```text
Tools → Board → ESP32 Dev Module
```

Choose the correct COM Port.

Click:

```text
Upload
```

Once uploaded, open the Serial Monitor at:

```text
115200 baud
```

Expected output:

```text
=== ESP32 VIDEO PLAYER ===

LittleFS mounted
File size: xxxx
Frames: xxxx
```

---

# 🎥 Using the Included Demo Video

A sample `video.bin` file is included with this repository.

Simply:

1. Place it inside the `data` folder
2. Upload LittleFS
3. Upload firmware
4. Enjoy OLED video playback

No conversion required.

---

# 🎞 Creating Your Own Videos

You can generate custom OLED videos using the conversion workflow from:

https://github.com/younes-makhchan/ESP32_Video_Display

### Basic Workflow

1. Install Python
2. Download the conversion tools
3. Select your input video
4. Convert the video to monochrome frames
5. Generate a `video.bin` file
6. Copy `video.bin` into:

```text
data/video.bin
```

7. Upload LittleFS again

Your custom video will now play on the OLED display.

---

Recommended:
- OLED playback GIF
- Wiring diagram
- ESP32 setup photo

---

## 📁 File Structure

```text
ESP32-OLED-Video-Player
│
├── data/
│   └── video.bin
│
├── images/
│   ├── demo.gif
│   ├── wiring.png
│   └── setup.jpg
│
├── src/
│   └── main.cpp
│
└── README.md
```

---

## Credits

This project is inspired by and adapts the video conversion workflow from:

https://github.com/younes-makhchan/ESP32_Video_Display

Modifications include:

- SSD1306 OLED support
- LittleFS storage workflow
- Arduino IDE integration
- Simplified setup process

---

## 👨‍💻 Author

**Akshit Builds**

📸 Instagram: https://instagram.com/akshit.builds

Follow for more:
- IoT Projects
- ESP32 Tutorials
- Electronics Builds
- Embedded Systems
- Smart Home Projects

⭐ If you found this project useful, consider giving the repository a star.
