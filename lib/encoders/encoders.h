#ifndef ENCODERS_H
#define ENCODERS_H

#include <Arduino.h>

class Encoder
{
public:
    // Constructor: takes the analog pin number
    Encoder(uint8_t analogPin);

    // Initialize the encoder
    void begin();

    // Get the angle from the encoder in degrees (0-360)
    float getAngle();

private:
    uint8_t _analogPin;                      // Pin for reading the encoder output
    const float _scaleFactor = 360.0 / 1023; // Scaling from 10-bit ADC to 360 degrees
};

#endif
