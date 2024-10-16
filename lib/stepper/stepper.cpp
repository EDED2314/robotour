/*
 * The sequence of control signals for 4 control wires is as follows:
 *
 * Step C0 C1 C2 C3
 *    1  1  0  1  0
 *    2  0  1  1  0
 *    3  0  1  0  1
 *    4  1  0  0  1
 *
 *
 * The circuits can be found at
 *
 * https://docs.arduino.cc/learn/electronics/stepper-motors#circuit
 */

#include "Arduino.h"
#include "Stepper.h"

/*
 *   constructor for four-pin version
 *   Sets which wires should control the motor.
 */
Stepper::Stepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
                 int motor_pin_3, int motor_pin_4, int wheelRadiusCM)
{
    this->step_number = 0;                   // which step the motor is on
    this->direction = 0;                     // motor direction
    this->last_step_time = 0;                // timestamp in us of the last step taken
    this->number_of_steps = number_of_steps; // total number of steps for this motor

    // Arduino pins for the motor control connection:
    this->motor_pin_1 = motor_pin_1;
    this->motor_pin_2 = motor_pin_2;
    this->motor_pin_3 = motor_pin_3;
    this->motor_pin_4 = motor_pin_4;

    // setup the pins on the microcontroller:
    pinMode(this->motor_pin_1, OUTPUT);
    pinMode(this->motor_pin_2, OUTPUT);
    pinMode(this->motor_pin_3, OUTPUT);
    pinMode(this->motor_pin_4, OUTPUT);

    // pin_count is used by the stepMotor() method:
    this->pin_count = 4;

    this->radius = wheelRadiusCM / 100.0;
}

/*
 * Sets the speed in revs per minute
 */
void Stepper::setSpeed(long whatSpeed)
{
    this->step_delay = 60L * 1000L * 1000L / this->number_of_steps / whatSpeed;
}

void Stepper::moveDis(int cm)
{
    float m = cm / 100.0;
    // TODO
}

void Stepper::stepTwo(int steps_to_move, Stepper other, void (*callback)())
{
    int steps_left = abs(steps_to_move); // how many steps to take

    if (steps_to_move > 0)
    {
        this->direction = 1;
    }
    if (steps_to_move < 0)
    {
        this->direction = 0;
    }
    while (steps_left > 0)
    {
        unsigned long now = micros();

        if (now - this->last_step_time >= this->step_delay)
        {

            this->last_step_time = now;

            if (this->direction == 1)
            {
                this->step_number++;
                if (this->step_number == this->number_of_steps)
                {
                    this->step_number = 0;
                }
            }
            else
            {
                if (this->step_number == 0)
                {
                    this->step_number = this->number_of_steps;
                }
                this->step_number--;
            }
            // decrement the steps left:
            steps_left--;
            // step the motor to step number 0, 1, ..., {3 or 10}

            stepMotor(this->step_number % 4);
            other.stepMotor(this->step_number % 4);
            if (callback != nullptr)
            {
                callback();
            }
        }
        else
        {
            yield();
            if (callback != nullptr)
            {
                callback();
            }
        }
    }
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void Stepper::step(int steps_to_move, void (*callback)())
{
    int steps_left = abs(steps_to_move); // how many steps to take

    // determine direction based on whether steps_to_mode is + or -:
    if (steps_to_move > 0)
    {
        this->direction = 1;
    }
    if (steps_to_move < 0)
    {
        this->direction = 0;
    }

    // decrement the number of steps, moving one step each time:
    while (steps_left > 0)
    {
        unsigned long now = micros();
        // move only if the appropriate delay has passed:
        if (now - this->last_step_time >= this->step_delay)
        {
            // get the timeStamp of when you stepped:
            this->last_step_time = now;
            // increment or decrement the step number,
            // depending on direction:
            if (this->direction == 1)
            {
                this->step_number++;
                if (this->step_number == this->number_of_steps)
                {
                    this->step_number = 0;
                }
            }
            else
            {
                if (this->step_number == 0)
                {
                    this->step_number = this->number_of_steps;
                }
                this->step_number--;
            }
            // decrement the steps left:
            steps_left--;
            // step the motor to step number 0, 1, ..., {3 or 10}

            stepMotor(this->step_number % 4);
            if (callback != nullptr)
            {
                callback();
            }
        }
        else
        {
            yield();
            if (callback != nullptr)
            {
                callback();
            }
        }
    }
}

/*
 * Moves the motor forward or backwards.
 */
void Stepper::stepMotor(int thisStep)
{

    switch (thisStep)
    {
    case 0: // 1010
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);
        break;
    case 1: // 0110
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, HIGH);
        digitalWrite(motor_pin_4, LOW);
        break;
    case 2: // 0101
        digitalWrite(motor_pin_1, LOW);
        digitalWrite(motor_pin_2, HIGH);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);
        break;
    case 3: // 1001
        digitalWrite(motor_pin_1, HIGH);
        digitalWrite(motor_pin_2, LOW);
        digitalWrite(motor_pin_3, LOW);
        digitalWrite(motor_pin_4, HIGH);
        break;
    }
}
