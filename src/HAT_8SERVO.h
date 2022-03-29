#ifndef _M5_HAT_8SERVO_H_
#define _M5_HAT_8SERVO_H_

#include <Arduino.h>
#include <Wire.h>

#define M5_HAT_8SERVO_DEVICE_ADDR    0x36
#define M5_HAT_8SERVO_SERVO_ANGLE_REG 0x00
#define M5_HAT_8SERVO_SERVO_PULSE_REG 0x10
#define M5_HAT_8SERVO_MOS_CTL_REG    0x30

class HAT_8SERVO {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t sda = 0, uint8_t scl = 26,
               uint8_t addr = M5_HAT_8SERVO_DEVICE_ADDR);
    bool setServoAngle(uint8_t index, uint8_t deg);
    bool setAllServoAngle(uint8_t deg);
    bool setServoPulse(uint8_t index, uint16_t pulse);
    bool setAllServoPulse(uint16_t pulse);
    bool enableServoPower(uint8_t state);
    uint8_t getServoAngle(uint8_t index);
    uint16_t getServoPulse(uint8_t index);
};

#endif
