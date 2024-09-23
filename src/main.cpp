// #include <Arduino.h>
// #include <SparkFun_TB6612.h>

// // Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// // the default pins listed are the ones used on the Redbot (ROB-12097) with
// // the exception of STBY which the Redbot controls with a physical switch

// #define AIN1 1
// #define AIN2 2
// #define PWMA 0
// #define PWMB 6
// #define BIN1 7
// #define BIN2 8
// #define STBY 9

// // these constants are used to allow you to make your motor configuration
// // line up with function names like forward.  Value can be 1 or -1
// const int offsetA = 1;
// const int offsetB = 1;

// // Initializing motors.  The library will allow you to initialize as many
// // motors as you have memory for.  If you are using functions like forward
// // that take 2 motors as arguements you can either write new functions or
// // call the function more than once.
// Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
// Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

// void setup()
// {
//   // Nothing here
// }

// void loop()
// {
//   // Use of the drive function which takes as arguements the speed
//   // and optional duration.  A negative speed will cause it to go
//   // backwards.  Speed can be from -255 to 255.  Also use of the
//   // brake function which takes no arguements.
//   motor1.drive(255, 1000);
//   motor1.drive(-255, 1000);
//   motor1.brake();
//   delay(1000);

//   // Use of the drive function which takes as arguements the speed
//   // and optional duration.  A negative speed will cause it to go
//   // backwards.  Speed can be from -255 to 255.  Also use of the
//   // brake function which takes no arguements.
//   motor2.drive(255, 1000);
//   motor2.drive(-255, 1000);
//   motor2.brake();
//   delay(1000);

//   // Use of the forward function, which takes as arguements two motors
//   // and optionally a speed.  If a negative number is used for speed
//   // it will go backwards
//   forward(motor1, motor2, 150);
//   delay(1000);

//   // Use of the back function, which takes as arguments two motors
//   // and optionally a speed.  Either a positive number or a negative
//   // number for speed will cause it to go backwards
//   back(motor1, motor2, -150);
//   delay(1000);

//   // Use of the brake function which takes as arguments two motors.
//   // Note that functions do not stop motors on their own.
//   brake(motor1, motor2);
//   delay(1000);

//   // Use of the left and right functions which take as arguements two
//   // motors and a speed.  This function turns both motors to move in
//   // the appropriate direction.  For turning a single motor use drive.
//   left(motor1, motor2, 100);
//   delay(1000);
//   right(motor1, motor2, 100);
//   delay(1000);

//   // Use of brake again.
//   brake(motor1, motor2);
//   delay(1000);
// }
#include <Arduino.h>
// Configure these to fit your design...
// #define out_STBY 5
// #define out_B_PWM 3
#define out_A_PWM 0
#define out_A_IN2 1
#define out_A_IN1 2
// #define out_B_IN1 8
// #define out_B_IN2 7
#define motor_A 0
#define motor_B 1
#define motor_AB 2

void motor_speed2(boolean, char);
void motor_speed(boolean, boolean, byte);
void motor_brake(boolean);

void setup()
{
  //  pinMode(out_STBY, OUTPUT);
  pinMode(out_A_PWM, OUTPUT);
  pinMode(out_A_IN1, OUTPUT);
  pinMode(out_A_IN2, OUTPUT);
  // pinMode(out_B_PWM, OUTPUT);
  //  pinMode(out_B_IN1, OUTPUT);
  // pinMode(out_B_IN2, OUTPUT);

  // motor_standby(false);

  motor_speed2(motor_A, -100);
  delay(2000);
  motor_speed2(motor_A, 0);

  // motor_speed2(motor_A, -100);
  // motor_speed2(motor_B, -100);
  // delay(2000);
  // for (int i = -100; i < 100; i++)
  // {
  //     motor_speed2(motor_A, i);
  //     motor_speed2(motor_B, i);
  //     delay(50);
  // }
  // delay(2000);
  // motor_standby(true);
}

void loop()
{
}

void motor_speed2(boolean motor, char speed)
{ // speed from -100 to 100
  byte PWMvalue = 0;
  PWMvalue = map(abs(speed), 0, 100, 50, 255); // anything below 50 is very weak
  if (speed > 0)
    motor_speed(motor, 0, PWMvalue);
  else if (speed < 0)
    motor_speed(motor, 1, PWMvalue);
  else
  {
    motor_brake(motor);
  }
}
void motor_speed(boolean motor, boolean direction, byte speed)
{ // speed from 0 to 255
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
    // if (direction == 0)
    // {
    //     digitalWrite(out_B_IN1, HIGH);
    //     digitalWrite(out_B_IN2, LOW);
    // }
    // else
    // {
    //     digitalWrite(out_B_IN1, LOW);
    //     digitalWrite(out_B_IN2, HIGH);
    // }
    // analogWrite(out_B_PWM, speed);
  }
}
// void motor_standby(boolean state)
// { // low power mode
//     if (state == true)
//         digitalWrite(out_STBY, LOW);
//     else
//         digitalWrite(out_STBY, HIGH);
// }

void motor_brake(boolean motor)
{
  if (motor == motor_A)
  {
    digitalWrite(out_A_IN1, HIGH);
    digitalWrite(out_A_IN2, HIGH);
  }
  else
  {
    // digitalWrite(out_B_IN1, HIGH);
    // digitalWrite(out_B_IN2, HIGH);
  }
}
// void motor_coast(boolean motor)
// {
//     if (motor == motor_A)
//     {
//         digitalWrite(out_A_IN1, LOW);
//         digitalWrite(out_A_IN2, LOW);
//         digitalWrite(out_A_PWM, HIGH);
//     }
//     else
//     {
//         digitalWrite(out_B_IN1, LOW);
//         digitalWrite(out_B_IN2, LOW);
//         digitalWrite(out_B_PWM, HIGH);
//     }
// }