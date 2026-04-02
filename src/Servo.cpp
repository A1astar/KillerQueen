#include "../include/Servo.hpp"

Servo::Servo(pca9685_device_t device, uint8_t pin, uint16_t min_pulse_us, uint16_t max_pulse_us, uint16_t neutral_pulse_us) :
_device(device),
_pin(pin),
_min_pulse_us(min_pulse_us),
_max_pulse_us(max_pulse_us),
_neutral_pulse_us(neutral_pulse_us),
_current_pos_degree(0)
{}

void Servo::move_servo_to_degree(float target_pos_degree)
{
    uint16_t pulse = angle_to_pulse_ms(target_pos_degree);

    pca9685_set_pulse_us(this->_device, this->_pin, 0, pulse);
    this->_current_pos_degree = target_pos_degree;
    printf("angle: %f -> pulse: %d\n", target_pos_degree, pulse);
    printf("current_pos_degree: %f\n", this->_current_pos_degree);
}

uint16_t Servo::angle_to_pulse_ms(float angle)
{
    if (angle < 0.0f)
        return this->_min_pulse_us + (angle + 90.0f) * (this->_neutral_pulse_us - this->_min_pulse_us) / 90;
    else if (angle > 0.0f)
        return this->_neutral_pulse_us + angle * (this->_max_pulse_us - this->_neutral_pulse_us) / 90;
    else
        return this->_neutral_pulse_us;
}

uint16_t Servo::get_min_pulse_us() const
{
    return this->_min_pulse_us;
}

uint16_t Servo::get_max_pulse_us() const
{
    return this->_max_pulse_us;
}

uint16_t Servo::get_neutral_pulse_us() const
{
    return this->_neutral_pulse_us;
}

float Servo::get_current_pos_degree()
{
    return this->_current_pos_degree;
}
