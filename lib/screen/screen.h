#ifndef SCREEN_H
#define SCREEN_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Screen
{
public:
    // Constructor
    Screen(uint8_t width, uint8_t height, int8_t reset_pin = -1, uint8_t address = 0x3C);

    // Initialize the display
    bool init();

    void print(const String &text);
    void println(const String &text);
    void setTextSize(uint8_t size);
    void setTextColor(uint16_t color);
    void drawPixel(int16_t x, int16_t y, uint16_t color);

    void clear();

    Adafruit_SSD1306 display;

private:
    uint8_t screenWidth;
    uint8_t screenHeight;
    int8_t resetPin;
    uint8_t screenAddress;
};

#endif
