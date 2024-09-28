#include "bno.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>
// Constructor
BNO::BNO(uint8_t address) : bno(55, address, &Wire) {}

// Initialize the sensor
bool BNO::init(boolean cal)
{
    if (!bno.begin())
    {
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        return false;
    }
    if (cal)
    {
        calibrate();
    }

    bno.setExtCrystalUse(true);
    return true;
}

void BNO::calibrate()
{
    Serial.println("Calibrating sensor... Please move it in a figure-eight pattern.");

    sensors_event_t event;
    while (!bno.isFullyCalibrated())
    {
        bno.getEvent(&event);
        displayCalStatus(); // Show calibration status
        delay(100);
    }

    adafruit_bno055_offsets_t newCalib;
    bno.getSensorOffsets(newCalib);
    storeCalibrationData(newCalib);
    Serial.println("Sensor calibrated and data stored.");
}

void BNO::restoreCalibration()
{
    long bnoID;
    int eeAddress = 0;

    EEPROM.get(eeAddress, bnoID);
    sensor_t sensor;
    bno.getSensor(&sensor);

    if (bnoID != sensor.sensor_id)
    {
        Serial.println("No Calibration Data found in EEPROM.");
        return;
    }

    adafruit_bno055_offsets_t calibrationData;
    eeAddress += sizeof(long);
    EEPROM.get(eeAddress, calibrationData);
    Serial.println("Restoring Calibration data to the BNO055...");
    bno.setSensorOffsets(calibrationData);
    Serial.println("Calibration data loaded.");
}
void BNO::storeCalibrationData(const adafruit_bno055_offsets_t &calibData)
{
    long bnoID;
    int eeAddress = 0;
    sensor_t sensor;
    bno.getSensor(&sensor);
    bnoID = sensor.sensor_id;

    EEPROM.put(eeAddress, bnoID);
    eeAddress += sizeof(long);
    EEPROM.put(eeAddress, calibData);
    Serial.println("Calibration data stored to EEPROM.");
}

// Display calibration status
void BNO::displayCalStatus()
{
    uint8_t sys, gyro, accel, mag;
    bno.getCalibration(&sys, &gyro, &accel, &mag);
    Serial.print("Sys: ");
    Serial.print(sys);
    Serial.print(" G: ");
    Serial.print(gyro);
    Serial.print(" A: ");
    Serial.print(accel);
    Serial.print(" M: ");
    Serial.println(mag);
}

float BNO::calculateHeading()
{
    // Get quaternion values
    imu::Quaternion quat;
    quat = bno.getQuat();

    // Rotate the north-pointing vector (1, 0, 0) using the quaternion
    float v[3] = {1, 0, 0}; // North vector as a quaternion
    float rotated[3];       // To hold the result

    // Quaternion rotation: qvq^-1
    // This is simplified since we can directly use quaternion multiplication

    rotated[0] = (quat.w() * v[0] - quat.x() * v[1] - quat.y() * v[2]);
    rotated[1] = (quat.x() * v[0] + quat.w() * v[1] + quat.z() * v[2]);
    rotated[2] = (quat.y() * v[0] - quat.z() * v[1] + quat.w() * v[2]);

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
