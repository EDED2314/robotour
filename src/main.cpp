#include <Arduino.h>
// Configure these to fit your design...
// #define out_STBY 5
#define out_A_PWM 0
#define out_A_IN2 1
#define out_A_IN1 2

#define out_B_IN1 6
#define out_B_IN2 5
#define out_B_PWM 7

#define motor_A 0
#define motor_B 1
#define motor_AB 2

void motor_speed2(boolean motor, char speed);
void motor_speed(boolean motor, boolean direction, byte speed);
void motor_brake(boolean motor);

void setup()
{
  //  pinMode(out_STBY, OUTPUT);
  pinMode(out_A_PWM, OUTPUT);
  pinMode(out_A_IN1, OUTPUT);
  pinMode(out_A_IN2, OUTPUT);
  pinMode(out_B_PWM, OUTPUT);
  pinMode(out_B_IN1, OUTPUT);
  pinMode(out_B_IN2, OUTPUT);
}

void loop()
{
  motor_speed(motor_A, 0, 100);
  motor_speed(motor_B, 0, 100);
  delay(2000);

  motor_brake(motor_A);
  motor_brake(motor_B);
  delay(2000);
}

// void motor_speed2(boolean motor, char speed)
// { // speed from -100 to 100
//   byte PWMvalue = 0;
//   PWMvalue = map(abs(speed), 0, 100, 50, 255); // anything below 50 is very weak
//   if (speed > 0)
//     motor_speed(motor, 0, PWMvalue);
//   else if (speed < 0)
//     motor_speed(motor, 1, PWMvalue);
//   else
//   {
//     motor_brake(motor);
//   }
// }

void motor_speed(boolean motor, boolean direction, byte speed)
{ // speed from 0 to 255, direction: 0/false is forward, 1/true
  if (motor == motor_A)
  {
    if (direction == 0)
    {
      digitalWrite(out_A_IN1, HIGH);
      digitalWrite(out_A_IN2, LOW);
    }
    else
    {
      digitalWrite(out_A_IN1, LOW);
      digitalWrite(out_A_IN2, HIGH);
    }
    analogWrite(out_A_PWM, speed);
  }
  else
  {
    if (direction == 0)
    {
      digitalWrite(out_B_IN1, HIGH);
      digitalWrite(out_B_IN2, LOW);
    }
    else
    {
      digitalWrite(out_B_IN1, LOW);
      digitalWrite(out_B_IN2, HIGH);
    }
    analogWrite(out_B_PWM, speed);
  }
}

void motor_brake(boolean motor)
{
  if (motor == motor_A)
  {
    digitalWrite(out_A_IN1, HIGH);
    digitalWrite(out_A_IN2, HIGH);
  }
  else
  {
    digitalWrite(out_B_IN1, HIGH);
    digitalWrite(out_B_IN2, HIGH);
  }
}
