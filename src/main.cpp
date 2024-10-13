#include <Arduino.h>
#include "motor.h"
#include "encoders.h"
#include "bno.h"
#include "screen.h"
#include "stepper.h"

BNO myBNO;
Screen myScreen(128, 32);

Encoder motor1Encoder(A0);
Encoder motor2Encoder(A1);

const int stepsPerRev = 200;
Stepper leftStepper(stepsPerRev, 8, 9, 10, 11);
Stepper rightStepper(stepsPerRev, 3, 4, 5, 6);

void callback()
{
  float currentAngle = motor2Encoder.getAngle();
  myScreen.clear();
  myScreen.println(String(currentAngle));
}

void setup()
{
  Serial.begin(9600);
  analogReadResolution(12); // Set ADC resolution to 12 bits (0-4095)

  motor1Encoder.begin();
  motor2Encoder.begin();

  myScreen.init();
  myScreen.print("hello");

  if (!myBNO.init(false))
  {
    myScreen.clear();
    myScreen.println("BNO wamp wamp");
    while (1)
      ; // Initialization failed, halt here
  }

  leftStepper.setSpeed(30);
  rightStepper.setSpeed(30);
}

void loop()
{

  // motor1.setSpeed(100);
  // motor2.setSpeed(200);
  // delay(2000);
  // motor1.brake();
  // motor2.brake();
  // delay(2000);
  // Example move commands:
  // move(45.0, 1);  // Move motor 1 by 45 degrees

  // motor2.brake();
  // prev = currentAngle;
  // myStepper.step(100, &callback);
  // // myStepper.stepMotor(0);
  // // myStepper.stepMotor(1);
  // // myStepper.stepMotor(2);
  // // myStepper.stepMotor(3);
  // delay(1000);
}
