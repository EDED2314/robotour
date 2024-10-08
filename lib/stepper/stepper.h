

#ifndef Stepper_h
#define Stepper_h

// library interface description
class Stepper
{
public:
    Stepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
            int motor_pin_3, int motor_pin_4);
    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int number_of_steps);
    void stepMotor(int this_step);

private:
    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in us, based on speed
    int number_of_steps;      // total number of steps this motor can take
    int pin_count;            // how many pins are in use.
    int step_number;          // which step the motor is on

    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;

    unsigned long last_step_time; // timestamp in us of when the last step was taken
};

#endif
