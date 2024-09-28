#ifndef BNO_H
#define BNO_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class BNO
{
public:
    // Constructor
    BNO(uint8_t address = 0x28);

    // Initialize the sensor
    bool init();

    // Calibrate the sensor
    void calibrate();

    // Calculate the heading of the robot
    float calculateHeading();

    // Get the angular velocity (wx, wy, wz)
    void getAngularVelocity(float &wx, float &wy, float &wz);

private:
    Adafruit_BNO055 bno;
    float heading; // Holds the calculated heading
};

#endif // BNO_H
