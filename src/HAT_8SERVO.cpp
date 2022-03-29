#include "HAT_8SERVO.h"

bool HAT_8SERVO::begin(TwoWire *wire, uint8_t sda, uint8_t scl, uint8_t addr) {
    _wire = wire;
    _addr = addr;
    _sda  = sda;
    _scl  = scl;
    _wire->begin(_sda, _scl);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

bool HAT_8SERVO::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                            uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->write(buffer, length);
    if (_wire->endTransmission() == 0) return true;
    return false;
}

bool HAT_8SERVO::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                           uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission();
    if (_wire->requestFrom(addr, length)) {
        for (uint8_t i = 0; i < length; i++) {
            buffer[index++] = _wire->read();
        }
        return true;
    }
    return false;
}

bool HAT_8SERVO::setServoAngle(uint8_t index, uint8_t deg) {
    uint8_t data = deg;
    uint8_t reg = index;
    return writeBytes(_addr, reg, &data, 1);
}

bool HAT_8SERVO::setAllServoAngle(uint8_t deg) {
    uint8_t data[8] = {0};
    memset(data, deg, 8);
    return writeBytes(_addr, M5_HAT_8SERVO_SERVO_ANGLE_REG, data, 8);
}

bool HAT_8SERVO::setServoPulse(uint8_t index, uint16_t pulse) {
    uint8_t data[2] = {0};
    data[1]         = pulse & 0xff;
    data[0]         = (pulse >> 8) & 0xff;
    uint8_t reg     = M5_HAT_8SERVO_SERVO_PULSE_REG + (2 * index);
    return writeBytes(_addr, reg, data, 2);
    ;
}

bool HAT_8SERVO::setAllServoPulse(uint16_t pulse) {
    for (uint8_t i = 0; i < 8; i++) {
        if (!setServoPulse(i, pulse)) {
            return false;
        }
    }
    return true;
}

bool HAT_8SERVO::enableServoPower(uint8_t state) {
    uint8_t data = state;
    return writeBytes(_addr, M5_HAT_8SERVO_MOS_CTL_REG, &data, 1);
}

uint8_t HAT_8SERVO::getServoAngle(uint8_t index) {
    uint8_t data = 0;
    uint8_t reg = M5_HAT_8SERVO_SERVO_ANGLE_REG + index;
    if (readBytes(_addr, reg, &data, 1)) {
        return data;
    } else {
        return 0;
    };
}

uint16_t HAT_8SERVO::getServoPulse(uint8_t index) {
    uint8_t data[2] = {0};
    uint8_t reg = M5_HAT_8SERVO_SERVO_PULSE_REG + index;
    if (readBytes(_addr, reg, data, 2)) {
        return (data[1] << 8) | data[0];
    } else {
        return 0;
    };
}
