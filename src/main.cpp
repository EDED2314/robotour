#include <Arduino.h>
#include "motor.h"
#include "encoders.h"

// Define encoder objects for 4 motors
Encoder motor1Encoder(A0);
Encoder motor2Encoder(A1);
Encoder motor3Encoder(A2);
Encoder motor4Encoder(A3);

// Define Motor objects for 4 motors
Motor motor1(0, 2, 1); // Motor 1: PWM, IN1, IN2 pins
Motor motor2(7, 6, 5); // Motor 2: PWM, IN1, IN2 pins

// CHECK THIS PLEASE THESE ARE DEFAULT VALUES LMAOOO
Motor motor3(10, 12, 11); // Motor 3: PWM, IN1, IN2 pins
Motor motor4(14, 16, 15); // Motor 4: PWM, IN1, IN2 pins

// PID control variables
float kp = 1.0, ki = 0.1, kd = 0.01;
float prevError[4] = {0, 0, 0, 0}; // Previous error for each motor
float integral[4] = {0, 0, 0, 0};  // Integral term for each motor

// Tracking total cumulative angles for each motor
float cumulativeAngle[4] = {0, 0, 0, 0}; // Cumulative angle for each motor

void setup()
{
  Serial.begin(9600);

  // Initialize encoders
  motor1Encoder.begin();
  motor2Encoder.begin();
  motor3Encoder.begin();
  motor4Encoder.begin();

  // Initialize motor objects
  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();
}

// Move function with delta angle and motor selection
void move(float DELTAangle, int motorSelector)
{
  int motorIndex = motorSelector - 1; // Motor selector: 1-4, corresponding to array index 0-3
  float currentAngle = 0;

  // Select the appropriate encoder and read the current angle
  switch (motorSelector)
  {
  case 1:
    currentAngle = motor1Encoder.getAngle();
    break;
  case 2:
    currentAngle = motor2Encoder.getAngle();
    break;
  case 3:
    currentAngle = motor3Encoder.getAngle();
    break;
  case 4:
    currentAngle = motor4Encoder.getAngle();
    break;
  default:
    Serial.println("Invalid motor selector");
    return;
  }

  // Calculate the difference between the current reading and the last cumulative angle
  float previousCumulativeAngle = cumulativeAngle[motorIndex];
  float angleDifference = currentAngle - fmod(previousCumulativeAngle, 360);

  // Handle angle wrapping (0-360) range
  if (angleDifference > 180)
  {
    // Encoder wrapped from 360 to 0
    angleDifference -= 360;
  }
  else if (angleDifference < -180)
  {
    // Encoder wrapped from 0 to 360
    angleDifference += 360;
  }

  // Update cumulative angle by adding the corrected angle difference
  cumulativeAngle[motorIndex] += angleDifference;

  // Calculate the target angle after the delta movement
  float targetAngle = cumulativeAngle[motorIndex] + DELTAangle;

  // Calculate PID control variables for the selected motor
  float error = targetAngle - cumulativeAngle[motorIndex];
  integral[motorIndex] += error;
  float derivative = error - prevError[motorIndex];
  float motorSpeed = kp * error + ki * integral[motorIndex] + kd * derivative;
  prevError[motorIndex] = error;

  // Apply motor speed and direction using the Motor class
  switch (motorSelector)
  {
  case 1:
    motor1.setSpeed(motorSpeed);
    break;
  case 2:
    motor2.setSpeed(motorSpeed);
    break;
  case 3:
    motor3.setSpeed(motorSpeed);
    break;
  case 4:
    motor4.setSpeed(motorSpeed);
    break;
  }
}

void loop()
{
  // Example move commands:
  move(45.0, 1);  // Move motor 1 by 45 degrees
  move(400.0, 2); // Move motor 2 by 400 degrees (should handle angle wrapping)

  delay(1000); // Delay for stability between moves
}
