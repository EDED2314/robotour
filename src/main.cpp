#include <Arduino.h>
#include "encoders.h"

// Define motor control pins for 4 motors
#define out_M1_PWM 0
#define out_M1_IN2 1
#define out_M1_IN1 2

#define out_M2_PWM 7
#define out_M2_IN1 6
#define out_M2_IN2 5

#define out_M3_PWM 10 // Example pins for motor 3
#define out_M3_IN1 11
#define out_M3_IN2 12

#define out_M4_PWM 14 // Example pins for motor 4
#define out_M4_IN1 15
#define out_M4_IN2 16

// Define encoder objects for 4 motors
Encoder motor1Encoder(A0);
Encoder motor2Encoder(A1);
Encoder motor3Encoder(A2); // Example pins for additional encoders
Encoder motor4Encoder(A3);

// PID control variables (same for all motors for now, but can be tuned individually)
float kp = 1.0, ki = 0.1, kd = 0.01;
float prevError[4] = {0, 0, 0, 0}; // Previous error for each motor
float integral[4] = {0, 0, 0, 0};  // Integral term for each motor

void setup()
{
  Serial.begin(9600);

  // Initialize encoders
  motor1Encoder.begin();
  motor2Encoder.begin();
  motor3Encoder.begin();
  motor4Encoder.begin();

  // Initialize motor control pins for all motors
  pinMode(out_M1_PWM, OUTPUT);
  pinMode(out_M1_IN1, OUTPUT);
  pinMode(out_M1_IN2, OUTPUT);

  pinMode(out_M2_PWM, OUTPUT);
  pinMode(out_M2_IN1, OUTPUT);
  pinMode(out_M2_IN2, OUTPUT);

  pinMode(out_M3_PWM, OUTPUT);
  pinMode(out_M3_IN1, OUTPUT);
  pinMode(out_M3_IN2, OUTPUT);

  pinMode(out_M4_PWM, OUTPUT);
  pinMode(out_M4_IN1, OUTPUT);
  pinMode(out_M4_IN2, OUTPUT);
}

// Move function with delta angle and motor selection
void move(float DELTAangle, int motorSelector)
{
  // Variables for the target angle and current angle of the selected motor
  float currentAngle = 0;
  float targetAngle = 0;
  int motorIndex = motorSelector - 1; // Motor selector: 1-4, corresponding to array index 0-3

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

  // Calculate the target angle
  targetAngle = currentAngle + DELTAangle;

  // Calculate PID control variables for the selected motor
  float error = targetAngle - currentAngle;
  integral[motorIndex] += error;
  float derivative = error - prevError[motorIndex];
  float motorSpeed = kp * error + ki * integral[motorIndex] + kd * derivative;
  prevError[motorIndex] = error;

  // Apply motor speed and direction
  setMotorSpeed(motorSelector, motorSpeed);
}

// Function to set motor speed and direction for the selected motor
void setMotorSpeed(int motor, float speed)
{
  int pwmPin = 0, in1Pin = 0, in2Pin = 0;

  // Set pins based on the motor selector
  switch (motor)
  {
  case 1:
    pwmPin = out_M1_PWM;
    in1Pin = out_M1_IN1;
    in2Pin = out_M1_IN2;
    break;
  case 2:
    pwmPin = out_M2_PWM;
    in1Pin = out_M2_IN1;
    in2Pin = out_M2_IN2;
    break;
  case 3:
    pwmPin = out_M3_PWM;
    in1Pin = out_M3_IN1;
    in2Pin = out_M3_IN2;
    break;
  case 4:
    pwmPin = out_M4_PWM;
    in1Pin = out_M4_IN1;
    in2Pin = out_M4_IN2;
    break;
  default:
    Serial.println("Invalid motor selector");
    return;
  }

  // Control motor direction based on speed sign
  if (speed > 0)
  {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
  }
  else
  {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    speed = -speed;
  }

  // Apply PWM speed control (constrain to valid range)
  analogWrite(pwmPin, constrain(speed, 0, 255));
}

void loop()
{
  // Example move commands:
  move(45.0, 1);  // Move motor 1 by 45 degrees
  move(-30.0, 2); // Move motor 2 by -30 degrees

  delay(1000);
