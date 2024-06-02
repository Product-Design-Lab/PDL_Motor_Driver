#pragma once

#include <Arduino.h>
#include <cstdint>

class MotorDriver
{
private:
    // Pins
    uint8_t PWM_pin = 0;
    uint8_t PWM_pin2 = 0;
    uint8_t PWM_pin_count = 0;
    uint8_t DIR_pin = 0;
    uint8_t DIR_pin2 = 0;
    uint8_t dir_pin_count = 0;
    uint8_t VISEN_pin = 0;
    uint8_t has_visen_pin = 0;
    uint8_t enable_pin = 0;
    uint8_t has_enable_pin = 0;

    // PWM
    uint32_t max_pwm = 255;
    float target_pwm_f32 = 0;
    uint32_t target_pwm_u32 = 0;

    // Direction
    enum Direction
    {
        BACKWARD = 0,
        FORWARD = 1
    };
    bool direction = FORWARD;

    // Current sensing
    int current_feedback = 0;
    float visen_A_per_V = 0;

    // Miscellaneous
    bool is_enabled = true;
    bool debug_enabled = false;

public:
    MotorDriver();
    ~MotorDriver();

    void setPwmPin(uint8_t pin);
    void setPwmPin(uint8_t pin1, uint8_t pin2);
    void setDirPin(uint8_t pin);
    void setDirPin(uint8_t pin1, uint8_t pin2);
    void setDirNoPin();
    void setVisenPin(uint8_t pin);
    void setVisenNoPin();
    void setEnablePin(uint8_t pin);
    void setEnableNoPin();

    void setEnable(bool enable);
    void setMaxPwm(uint32_t max_pwm);
    void runMotor(float pwm);

    bool hasCurrentPin() const;
    int getCurrent() const;
    void setVisenSensitivity(float A_per_V);
    float getCurrent_mA() const;

    void setDebug(bool enable);
};
