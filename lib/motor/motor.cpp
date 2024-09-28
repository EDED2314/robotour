#include "motor.h"

// Constructor to initialize motor pins
Motor::Motor(uint8_t pwmPin, uint8_t in1Pin, uint8_t in2Pin)
    : _pwmPin(pwmPin), _in1Pin(in1Pin), _in2Pin(in2Pin) {}

// Initialize motor pins
void Motor::init()
{
    pinMode(_pwmPin, OUTPUT);
    pinMode(_in1Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);
}

// Set motor speed and direction
void Motor::setSpeed(float speed)
{
    if (speed > 0)
    {
        digitalWrite(_in1Pin, HIGH);
        digitalWrite(_in2Pin, LOW);
    }
    else
    {
        digitalWrite(_in1Pin, LOW);
        digitalWrite(_in2Pin, HIGH);
        speed = -speed; // Reverse the direction
    }
    // Apply PWM to control speed, constrained to 0-255 range
    analogWrite(_pwmPin, constrain(speed, 0, 255));
}
