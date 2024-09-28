#include "encoders.h"

Encoder::Encoder(uint8_t analogPin) : _analogPin(analogPin) {}

void Encoder::begin()
{
    pinMode(_analogPin, INPUT); // Initialize the analog pin
}

float Encoder::getAngle()
{
    int rawValue = analogRead(_analogPin); // Read the raw analog value (0-1023)
    float angle = rawValue * _scaleFactor; // Convert to degrees
    return angle;
}
