#include "bno.h"

// Constructor
BNO::BNO(uint8_t address) : bno(55, address, &Wire) {}

// Initialize the sensor
bool BNO::init()
{
    if (!bno.begin())
    {
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        return false;
    }
    bno.setExtCrystalUse(true);
    return true;
}

// Calibrate the sensor
void BNO::calibrate()
{
    uint8_t system, gyro, accel, mag;
    bno.getCalibration(&system, &gyro, &accel, &mag);

    Serial.print("Calibration: ");
    Serial.print("Sys: ");
    Serial.print(system);
    Serial.print(" G: ");
    Serial.print(gyro);
    Serial.print(" A: ");
    Serial.print(accel);
    Serial.print(" M: ");
    Serial.print(mag);
    Serial.println();
}

// Calculate the heading of the robot
float BNO::calculateHeading()
{
    // Get quaternion values
    quat_t quat;
    bno.getQuat(&quat);

    // Rotate the north-pointing vector (1, 0, 0) using the quaternion
    float v[3] = {1, 0, 0}; // North vector as a quaternion
    float rotated[3];       // To hold the result

    // Quaternion rotation: qvq^-1
    // This is simplified since we can directly use quaternion multiplication

    rotated[0] = (quat.w * v[0] - quat.x * v[1] - quat.y * v[2]);
    rotated[1] = (quat.x * v[0] + quat.w * v[1] + quat.z * v[2]);
    rotated[2] = (quat.y * v[0] - quat.z * v[1] + quat.w * v[2]);

    // Calculate heading using atan2(y, x)
    heading = atan2(rotated[1], rotated[0]) * (180.0 / M_PI); // Convert to degrees
    if (heading < 0)
    {
        heading += 360; // Normalize to 0-360 degrees
    }

    return heading;
}

// Get the angular velocity (wx, wy, wz)
void BNO::getAngularVelocity(float &wx, float &wy, float &wz)
{
    sensors_event_t event;
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_GYROSCOPE);
    wx = event.gyro.x;
    wy = event.gyro.y;
    wz = event.gyro.z;
}
