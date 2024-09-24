#include <Arduino.h>
// Configure these to fit your design...
// #define out_STBY 5
#define out_A_PWM 0
#define out_A_IN2 1
#define out_A_IN1 2
#define M1_OUT_A 3
#define M1_OUT_B 4

#define out_B_IN1 6
#define out_B_IN2 5
#define out_B_PWM 7
#define M2_OUT_A 8
#define M2_OUT_B 9

#define motor_A 0
#define motor_B 1
#define motor_AB 2

void motor_speed2(boolean motor, char speed);
void motor_speed(boolean motor, boolean direction, byte speed);
void motor_brake(boolean motor);
void ISR_CountTicksM1();

volatile long ticksM1 = 0; // Make signed to handle decrementing
float angleM1 = 0.0;

#define encCPR 12 * 29.86

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  //  pinMode(out_STBY, OUTPUT);
  pinMode(out_A_PWM, OUTPUT);
  pinMode(out_A_IN1, OUTPUT);
  pinMode(out_A_IN2, OUTPUT);
  pinMode(out_B_PWM, OUTPUT);
  pinMode(out_B_IN1, OUTPUT);
  pinMode(out_B_IN2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(M1_OUT_A), ISR_CountTicksM1, CHANGE);

  motor_speed(motor_A, 0, 100);
  motor_speed(motor_B, 0, 100);

  delay(500);

  motor_brake(motor_A);
  motor_brake(motor_B);
  delay(2000);
}

void loop()
{
}

void ISR_CountTicksM1()
{
  bool currentStateA = digitalRead(M1_OUT_A); // Read current state of OUT A
  bool currentStateB = digitalRead(M1_OUT_B); // Read current state of OUT B

  // Determine direction of rotation based on A and B
  if (currentStateA == currentStateB)
  {
    ticksM1--; // Counterclockwise: Decrement ticks
  }
  else
  {
    ticksM1++; // Clockwise: Increment ticks
  }

  angleM1 = fmod((ticksM1 / encCPR) * (360 / (2 * PI)), 360); // Angle = (ticks * 360) / CPR

  // Display ticks and angle
  Serial.print("TicksM1: ");
  Serial.print(ticksM1);
  Serial.print("\tAngleM1 (deg): ");
  Serial.println(angleM1);
}

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
