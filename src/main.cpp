#include <Arduino.h>
#include "encoders.h"

// Define motor control pins
#define out_M1_PWM 0
#define out_M1_IN2 1
#define out_M1_IN1 2
#define out_M2_PWM 7
#define out_M2_IN1 6
#define out_M2_IN2 5

// Define encoder objects
Encoder motor1Encoder(A0); // Assuming the first AS5600 is connected to A0
Encoder motor2Encoder(A1); // Assuming the second AS5600 is connected to A1

// PID control variables
float kp = 1.0, ki = 0.1, kd = 0.01;
float prevErrorMotor1 = 0, integralMotor1 = 0;
float prevErrorMotor2 = 0, integralMotor2 = 0;

void setup()
{
  Serial.begin(9600);

  // Initialize the encoders
  motor1Encoder.begin();
  motor2Encoder.begin();

  // Initialize motor control pins
  pinMode(out_M1_PWM, OUTPUT);
  pinMode(out_M1_IN1, OUTPUT);
  pinMode(out_M1_IN2, OUTPUT);

  pinMode(out_M2_PWM, OUTPUT);
  pinMode(out_M2_IN1, OUTPUT);
  pinMode(out_M2_IN2, OUTPUT);
}

// Move function to control motor position based on target angle
void move(float targetAngleMotor1, float targetAngleMotor2)
{
  // Read the current angles from the encoders
  float currentAngleMotor1 = motor1Encoder.getAngle();
  float currentAngleMotor2 = motor2Encoder.getAngle();

  // Calculate PID for Motor 1
  float errorMotor1 = targetAngleMotor1 - currentAngleMotor1;
  integralMotor1 += errorMotor1;
  float derivativeMotor1 = errorMotor1 - prevErrorMotor1;
  float motor1Speed = kp * errorMotor1 + ki * integralMotor1 + kd * derivativeMotor1;
  prevErrorMotor1 = errorMotor1;

  // Calculate PID for Motor 2
  float errorMotor2 = targetAngleMotor2 - currentAngleMotor2;
  integralMotor2 += errorMotor2;
  float derivativeMotor2 = errorMotor2 - prevErrorMotor2;
  float motor2Speed = kp * errorMotor2 + ki * integralMotor2 + kd * derivativeMotor2;
  prevErrorMotor2 = errorMotor2;

  // Control Motor 1 based on PID output
  setMotorSpeed(1, motor1Speed);

  // Control Motor 2 based on PID output
  setMotorSpeed(2, motor2Speed);
}

// Function to set motor speed and direction
void setMotorSpeed(int motor, float speed)
{
  if (motor == 1)
  {
    if (speed > 0)
    {
      // Move forward
      digitalWrite(out_M1_IN1, HIGH);
      digitalWrite(out_M1_IN2, LOW);
    }
    else
    {
      // Move backward
      digitalWrite(out_M1_IN1, LOW);
      digitalWrite(out_M1_IN2, HIGH);
      speed = -speed;
    }
    analogWrite(out_M1_PWM, constrain(speed, 0, 255)); // Limit PWM to 0-255
  }
  if (motor == 2)
  {
    if (speed > 0)
    {
      // Move forward
      digitalWrite(out_M2_IN1, HIGH);
      digitalWrite(out_M2_IN2, LOW);
    }
    else
    {
      // Move backward
      digitalWrite(out_M2_IN1, LOW);
      digitalWrite(out_M2_IN2, HIGH);
      speed = -speed;
    }
    analogWrite(out_M2_PWM, constrain(speed, 0, 255)); // Limit PWM to 0-255
  }
}

void loop()
{
  // Example move calls:
  // Move motor 1 to 90 degrees and motor 2 to 180 degrees
  move(90.0, 180.0);

  delay(500); // Optional delay to slow the loop down
}
