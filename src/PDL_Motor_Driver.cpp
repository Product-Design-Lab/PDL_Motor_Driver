#include "PDL_Motor_Driver.h"

#if defined(NRF52840_XXAA) || defined(NRF52833_XXAA)
#include <Adafruit_TinyUSB.h>
#endif

MotorDriver::MotorDriver()
    : PWM_pin(0), PWM_pin2(0), PWM_pin_count(0),
      DIR_pin(0), DIR_pin2(0), dir_pin_count(0),
      VISEN_pin(0), has_visen_pin(0), enable_pin(0),
      has_enable_pin(0), max_pwm(255), target_pwm_f32(0),
      target_pwm_u32(0), direction(FORWARD), current_feedback(0),
      visen_A_per_V(0), is_enabled(true), debug_enabled(false)
{
}

MotorDriver::~MotorDriver()
{
    // Do nothing
}

void MotorDriver::setPwmPin(uint8_t pin)
{
    PWM_pin = pin;
    pinMode(PWM_pin, OUTPUT);
    PWM_pin_count = 1;
}

void MotorDriver::setPwmPin(uint8_t pin1, uint8_t pin2)
{
    PWM_pin = pin1;
    PWM_pin2 = pin2;
    pinMode(PWM_pin, OUTPUT);
    pinMode(PWM_pin2, OUTPUT);
    PWM_pin_count = 2;
}

void MotorDriver::setDirPin(uint8_t pin)
{
    DIR_pin = pin;
    pinMode(DIR_pin, OUTPUT);
    dir_pin_count = 1;
}

void MotorDriver::setDirPin(uint8_t pin1, uint8_t pin2)
{
    DIR_pin = pin1;
    DIR_pin2 = pin2;
    pinMode(DIR_pin, OUTPUT);
    pinMode(DIR_pin2, OUTPUT);
    dir_pin_count = 2;
}

void MotorDriver::setDirNoPin()
{
    DIR_pin = 0;
    DIR_pin2 = 0;
    dir_pin_count = 0;
}

void MotorDriver::setVisenPin(uint8_t pin)
{
    VISEN_pin = pin;
    has_visen_pin = 1;
}

void MotorDriver::setVisenNoPin()
{
    VISEN_pin = 0;
    has_visen_pin = 0;
}

void MotorDriver::setEnablePin(uint8_t pin)
{
    enable_pin = pin;
    pinMode(enable_pin, OUTPUT);
    has_enable_pin = 1;
}

void MotorDriver::setEnableNoPin()
{
    enable_pin = 0;
    has_enable_pin = 0;
}

void MotorDriver::setEnable(bool enable)
{
    if (!has_enable_pin)
    {
        return;
    }
    digitalWrite(enable_pin, enable ? HIGH : LOW);
}

void MotorDriver::setMaxPwm(uint32_t max_pwm)
{
    this->max_pwm = max_pwm;
}

void MotorDriver::runMotor(float pwm)
{
    target_pwm_f32 = constrain(pwm, -1.0f, 1.0f);
    target_pwm_u32 = static_cast<uint32_t>(abs(target_pwm_f32) * max_pwm);
    direction = (target_pwm_f32 >= 0) ? FORWARD : BACKWARD;

    if (dir_pin_count == 1)
    {
        digitalWrite(DIR_pin, direction);
        if (debug_enabled)
            Serial.printf("Setting pin %d to %d\n", DIR_pin, direction);
    }
    else if (dir_pin_count == 2)
    {
        digitalWrite(DIR_pin, direction);
        digitalWrite(DIR_pin2, !direction);
        if (debug_enabled)
            Serial.printf("Setting pin %d to %d, pin %d to %d\n", DIR_pin, direction, DIR_pin2, !direction);
    }

    if (PWM_pin_count == 1)
    {
        analogWrite(PWM_pin, target_pwm_u32);
        if (debug_enabled)
            Serial.printf("Setting pin %d to %d\n", PWM_pin, target_pwm_u32);
    }
    else if (PWM_pin_count == 2)
    {
        analogWrite(PWM_pin, direction * target_pwm_u32);
        analogWrite(PWM_pin2, !direction * target_pwm_u32);
        if (debug_enabled)
            Serial.printf("Setting pin %d to %d, pin %d to %d\n", PWM_pin, direction * target_pwm_u32, PWM_pin2, !direction * target_pwm_u32);
    }
}

bool MotorDriver::hasCurrentPin() const
{
    return has_visen_pin;
}

int MotorDriver::getCurrent() const
{
    if (!has_visen_pin)
    {
        return 0;
    }
    return analogRead(VISEN_pin);
}

void MotorDriver::setVisenSensitivity(float A_per_V)
{
    visen_A_per_V = A_per_V;
}

float MotorDriver::getCurrent_mA() const
{
    if (!has_visen_pin || visen_A_per_V == 0)
    {
        return 0;
    }
    const float voltage_reference = 3.3f;
    const int adc_max_value = 1023;
    return visen_A_per_V * voltage_reference * analogRead(VISEN_pin) / adc_max_value;
}

void MotorDriver::setDebug(bool enable)
{
    debug_enabled = enable;
    if (!Serial)
    {
        Serial.begin(115200);
    }
}
