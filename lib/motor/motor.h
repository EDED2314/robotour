#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
public:
    // Constructor: Initialize with control pins
    Motor(uint8_t pwmPin, uint8_t in1Pin, uint8_t in2Pin);

    // Initialize motor (set pin modes)
    void init();

    // Set motor speed (with direction control)
    void setSpeed(float speed);

private:
    uint8_t _pwmPin; // PWM pin for motor speed
    uint8_t _in1Pin; // IN1 pin for direction
    uint8_t _in2Pin; // IN2 pin for direction
};

#endif
