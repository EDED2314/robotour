#include "bno.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>
#include <SimpleKalmanFilter.h>

/*
SimpleKalmanFilter(e_mea, e_est, q);

e_mea: Measurement Uncertainty
e_est: Estimation Uncertainty
q: Process Noise
*/
SimpleKalmanFilter w1kalman(0.03, 1.0, 0.001);

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
    else
    {
        restoreCalibration();
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

float BNO::getHeading()
{

    imu::Quaternion q = bno.getQuat();
    imu::Quaternion q_prime = q.conjugate();
    imu::Quaternion p{0, 0, 1, 0};
    imu::Quaternion p_prime = q * p * q_prime;
    heading = acos(p_prime.z()) * 180 / PI;

    if (isnan(heading))
    {
        return 0;
    }

    return heading;
}

float BNO::getHeadingGyro()
{
    long tnow = millis();
    long dt = tnow - lastTimeSampled;
    float wx, wy, wz;
    getAngularVelocity(wx, wy, wz);
    float E1 = w1kalman.updateEstimate(wx);
    heading += E1 * dt * 0.001 * 0.99;
    lastTimeSampled = tnow;
    return heading * (180.0 / M_PI);
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
