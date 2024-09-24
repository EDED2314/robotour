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
void ISR_CountTicks();

volatile long ticks = 0; // Make signed to handle decrementing
float angle = 0.0;
float targetAngle = 90;
const float encCPR = 12 * 29.86;

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

  attachInterrupt(digitalPinToInterrupt(M2_OUT_A), ISR_CountTicks, CHANGE);

  // motor_speed(motor_B, 0, 100);

  // delay(500);

  // motor_brake(motor_A);
  // // motor_brake(motor_B);
  // delay(2000);
}

void loop()
{
  motor_speed(motor_B, 0, 100);
}

void ISR_CountTicks()
{
  bool currentStateA = digitalRead(M2_OUT_A); // Read current state of OUT A
  bool currentStateB = digitalRead(M2_OUT_B); // Read current state of OUT B

  // Determine direction of rotation based on A and B
  if (currentStateA == currentStateB)
  {
    ticks--; // Counterclockwise: Decrement ticks
  }
  else
  {
    ticks++; // Clockwise: Increment ticks
  }

  angle = (ticks / encCPR) * 360.0;

  // Display ticks and angle
  Serial.print("Ticks: ");
  Serial.print(ticks);
  Serial.print("\tAngle (deg): ");
  Serial.println(angle);

  if (angle >= targetAngle)
  {
    motor_brake(motor_B); // Stop the motor when the target angle is reached
    ticks = 0;
    Serial.println("Target angle reached!");
    delay(2000);
  }
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
