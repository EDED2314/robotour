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

    bool init(boolean cal);

    // Calibrate the sensor
    void calibrate();

    // Calculate the heading of the robot
    float calculateHeading();

    // Get the angular velocity (wx, wy, wz)
    void getAngularVelocity(float &wx, float &wy, float &wz);

private:
    Adafruit_BNO055 bno;
    float heading; // Holds the calculated heading
    void displayCalStatus();
    void restoreCalibration();
    void storeCalibrationData(const adafruit_bno055_offsets_t &calibData);
};

#endif // BNO_H
