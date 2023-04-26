
#include "Inc/mpu.h"

#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

MPU6050 mpu;

uint8_t mpuIntStatus; // holds actual interrupt status byte from MPU
uint8_t devStatus;    // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;

void Init()
{
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    if (devStatus == 0)
    {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        mpuIntStatus = mpu.getIntStatus();

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

Quaternion q;
float euler[3];
uint8_t fifoBuffer[64];

float Get()
{

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
    {
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetEuler(euler, &q);
    }

    return euler[0] * 180 / M_PI + 180.0;
}