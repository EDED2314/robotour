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
}
