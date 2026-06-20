/*
 * Project: ESP32 OLED Video Player
 * Creator: Akshit Builds
 *
 * Instagram: @akshit.builds
 *
 * Description:
 * This project plays pre-processed monochrome video files on a
 * 128x64 SSD1306 OLED display using an ESP32.
 *
 * The video is converted into individual monochrome frames,
 * packed into a binary file (video.bin), uploaded to LittleFS,
 * and rendered frame-by-frame on the OLED display.
 *
 * Features:
 * - 128x64 OLED video playback
 * - LittleFS storage support
 * - Frame-by-frame rendering
 * - Automatic video looping
 * - Optimized for ESP32
 * - SSD1306 I2C display support
 *
 * Hardware:
 * - ESP32 Development Board
 * - SSD1306 128x64 OLED Display
 *
 * Wiring:
 * -------------------------------
 * OLED SDA -> GPIO 21
 * OLED SCL -> GPIO 22
 * OLED VCC -> 3.3V
 * OLED GND -> GND
 * -------------------------------
 *
 * Video Preparation:
 * 1. Convert video to monochrome frames.
 * 2. Generate video.bin file.
 * 3. Upload video.bin to LittleFS.
 * 4. Flash firmware to ESP32.
 * 5. Enjoy OLED video playback.
 *
 * Credits:
 * Video conversion workflow inspired by:
 * https://github.com/younes-makhchan/ESP32_Video_Display
 *
 * Follow for more:
 * Instagram: @akshit.builds
 */

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define I2C_SDA 21
#define I2C_SCL 22
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Video settings
#define TARGET_FPS 20   // safer than 30 for OLED
#define FRAME_DELAY_MS (1000 / TARGET_FPS)

#define FRAME_WIDTH 128
#define FRAME_HEIGHT 64
#define BYTES_PER_FRAME (FRAME_WIDTH * FRAME_HEIGHT / 8)

File videoFile;
uint32_t totalFrames = 0;
uint32_t currentFrame = 0;

void displayFrame(uint8_t *frameData) {
    display.clearDisplay();

    for (int i = 0; i < BYTES_PER_FRAME; i++) {
        uint8_t b = frameData[i];

        int x = (i % (FRAME_WIDTH / 8)) * 8;
        int y = i / (FRAME_WIDTH / 8);

        for (int bit = 0; bit < 8; bit++) {
            if (b & (1 << (7 - bit))) {
                display.drawPixel(x + bit, y, SSD1306_WHITE);
            }
        }
    }

    display.display();
}

void setup() {
    Serial.begin(115200);
    delay(500);

    Wire.begin(I2C_SDA, I2C_SCL);

    Serial.println("\n=== ESP32 VIDEO PLAYER (FIXED) ===");

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println("OLED FAIL");
        while (1);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Starting...");
    display.display();

    // IMPORTANT: LittleFS
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS mount failed");
        while (1);
    }

    Serial.println("LittleFS mounted");

    Serial.println("Files:");
    File root = LittleFS.open("/");
    File f = root.openNextFile();

    while (f) {
        Serial.print("  ");
        Serial.print(f.name());
        Serial.print(" - ");
        Serial.println(f.size());
        f = root.openNextFile();
    }

    videoFile = LittleFS.open("/video.bin", "r");

    if (!videoFile) {
        Serial.println("video.bin NOT FOUND");
        while (1);
    }

    uint32_t fileSize = videoFile.size();
    totalFrames = fileSize / BYTES_PER_FRAME;

    Serial.print("File size: ");
    Serial.println(fileSize);
    Serial.print("Frames: ");
    Serial.println(totalFrames);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Video Loaded");
    display.print("Frames: ");
    display.println(totalFrames);
    display.display();

    delay(2000);
}

void loop() {
    static uint32_t last = 0;
    static uint8_t buffer[BYTES_PER_FRAME];

    if (millis() - last < FRAME_DELAY_MS) return;
    last = millis();

    if (!videoFile.available()) {
        Serial.println("Restart video");
        videoFile.seek(0);
        currentFrame = 0;
        return;
    }

    int bytes = videoFile.read(buffer, BYTES_PER_FRAME);

    if (bytes == BYTES_PER_FRAME) {
        displayFrame(buffer);
        currentFrame++;
    } else {
        videoFile.seek(0);
        currentFrame = 0;
    }
}