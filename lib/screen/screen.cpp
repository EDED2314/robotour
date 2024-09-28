#include "screen.h"

// Constructor
Screen::Screen(uint8_t width, uint8_t height, int8_t reset_pin, uint8_t address)
    : screenWidth(width), screenHeight(height), resetPin(reset_pin), screenAddress(address),
      display(Adafruit_SSD1306(width, height, &Wire, reset_pin)) {}

// Initialize the display
bool Screen::init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, screenAddress))
    {
        Serial.println(F("SSD1306 allocation failed"));
        return false; // Initialization failed
    }
    display.display();                   // Show initial Adafruit splash screen
    delay(2000);                         // Pause for 2 seconds
    display.clearDisplay();              // Clear the buffer
    display.setTextSize(1);              // Set default text size
    display.setTextColor(SSD1306_WHITE); // Set default text color
    return true;
}

// Print text to the screen (without newline)
void Screen::print(const String &text)
{
    display.print(text);
    display.display(); // Make sure to update the display after each change
}

// Print text to the screen (with newline)
void Screen::println(const String &text)
{
    display.println(text);
    display.display(); // Update display after text change
}

// Clear the screen
void Screen::clear()
{
    display.clearDisplay();
    display.display(); // Update display after clearing
}

void Screen::setTextSize(uint8_t size)
{
    display.setTextSize(size);
}

void Screen::setTextColor(uint16_t color)
{
    display.setTextColor(color);
}

void Screen::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    display.drawPixel(x, y, color);
}
