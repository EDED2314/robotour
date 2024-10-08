

// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 32 // OLED display height, in pixels

// void testdrawline();
// void testdrawrect();

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// // The pins for I2C are defined by the Wire-library.
// // On an arduino UNO:       A4(SDA), A5(SCL)
// // On an arduino MEGA 2560: 20(SDA), 21(SCL)
// // On an arduino LEONARDO:   2(SDA),  3(SCL), ...
// #define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
// #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// #define NUMFLAKES 10 // Number of snowflakes in the animation example

// #define LOGO_HEIGHT 16
// #define LOGO_WIDTH 16
// static const unsigned char PROGMEM logo_bmp[] =
//     {0b00000000, 0b11000000,
//      0b00000001, 0b11000000,
//      0b00000001, 0b11000000,
//      0b00000011, 0b11100000,
//      0b11110011, 0b11100000,
//      0b11111110, 0b11111000,
//      0b01111110, 0b11111111,
//      0b00110011, 0b10011111,
//      0b00011111, 0b11111100,
//      0b00001101, 0b01110000,
//      0b00011011, 0b10100000,
//      0b00111111, 0b11100000,
//      0b00111111, 0b11110000,
//      0b01111100, 0b11110000,
//      0b01110000, 0b01110000,
//      0b00000000, 0b00110000};

// void setup()
// {
//     Serial.begin(9600);

//     // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//     if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
//     {
//         Serial.println(F("SSD1306 allocation failed"));
//         for (;;)
//             ; // Don't proceed, loop forever
//     }

//     // Show initial display buffer contents on the screen --
//     // the library initializes this with an Adafruit splash screen.
//     display.display();
//     delay(2000); // Pause for 2 seconds

//     // Clear the buffer
//     display.clearDisplay();

//     // Draw a single pixel in white
//     display.drawPixel(10, 10, SSD1306_WHITE);

//     // Show the display buffer on the screen. You MUST call display() after
//     // drawing commands to make them visible on screen!
//     display.display();
//     delay(2000);
//     // display.display() is NOT necessary after every single drawing command,
//     // unless that's what you want...rather, you can batch up a bunch of
//     // drawing operations and then update the screen all at once by calling
//     // display.display(). These examples demonstrate both approaches...

//     testdrawline();

//     testdrawrect();
// }

// void loop()
// {
// }

// void testdrawline()
// {
//     int16_t i;

//     display.clearDisplay(); // Clear display buffer

//     for (i = 0; i < display.width(); i += 4)
//     {
//         display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
//         display.display(); // Update screen with each newly-drawn line
//         delay(1);
//     }
//     for (i = 0; i < display.height(); i += 4)
//     {
//         display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
//         display.display();
//         delay(1);
//     }
//     delay(250);

//     display.clearDisplay();

//     for (i = 0; i < display.width(); i += 4)
//     {
//         display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
//         display.display();
//         delay(1);
//     }
//     for (i = display.height() - 1; i >= 0; i -= 4)
//     {
//         display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1306_WHITE);
//         display.display();
//         delay(1);
//     }
//     delay(250);

//     display.clearDisplay();

//     for (i = display.width() - 1; i >= 0; i -= 4)
//     {
//         display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1306_WHITE);
//         display.display();
//         delay(1);
//     }
//     for (i = display.height() - 1; i >= 0; i -= 4)
//     {
//         display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1306_WHITE);
//         display.display();
//         delay(1);
//     }
//     delay(250);

//     display.clearDisplay();

//     for (i = 0; i < display.height(); i += 4)
//     {
//         display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
//         display.display();
//         delay(1);
//     }
//     for (i = 0; i < display.width(); i += 4)
//     {
//         display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1306_WHITE);
//         display.display();
//         delay(1);
//     }

//     delay(2000); // Pause for 2 seconds
// }

// void testdrawrect(void)
// {
//     display.clearDisplay();

//     for (int16_t i = 0; i < display.height() / 2; i += 2)
//     {
//         display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
//         display.display(); // Update screen with each newly-drawn rectangle
//         delay(1);
//     }

//     delay(2000);
// }
