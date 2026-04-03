#include "../include/Servo.hpp"

Servo::Servo
(
    uint8_t pin,
    uint16_t min_pulse_us,
    uint16_t max_pulse_us,
    uint16_t neutral_pulse_us,
    float home_deg
)
:   _pin(pin),
    _min_pulse_us(min_pulse_us),
    _max_pulse_us(max_pulse_us),
    _neutral_pulse_us(neutral_pulse_us),
    _start_pos_degree(home_deg),
    _current_pos_degree(home_deg),
    _target_pos_degree(home_deg),
    _start_time_us(0),
    _duration_us(0),
    _is_moving(false)
{}

void Servo::move_to(float target_deg, uint32_t duration_ms, uint64_t now_us)
{
    target_deg = this->clampf(target_deg, -90, +90);
    this->_start_pos_degree = this->_current_pos_degree;
    this->_target_pos_degree = target_deg;
    this->_start_time_us = now_us;
    this->_duration_us = (uint64_t)duration_ms * 1000ULL;

    if(this->_duration_us == 0)
    {
        this->_current_pos_degree = this->_target_pos_degree;
        this->_is_moving = false;
    }
    else
        this->_is_moving = true;
}

void Servo::update(uint64_t now_us)
{
    if(!this->_is_moving)
        return;

    uint64_t elapsed_time_us = now_us - this->_start_time_us;

    if(elapsed_time_us >= this->_duration_us)
    {
        this->_current_pos_degree = this->_target_pos_degree;
        this->_is_moving = false;
    }
    else
    {
        float normalized_time =  (float)elapsed_time_us / (float)this->_duration_us;
        float step = this->smootherstep(normalized_time);
        this->_current_pos_degree = this->lerp(this->_start_pos_degree, this->_target_pos_degree, step);
    }
}

uint16_t Servo::angle_to_pulse_ms(float angle) const
{
    if (angle < 0.0f)
        return this->_min_pulse_us + (angle + 90.0f) * (this->_neutral_pulse_us - this->_min_pulse_us) / 90;
    else if (angle > 0.0f)
        return this->_neutral_pulse_us + angle * (this->_max_pulse_us - this->_neutral_pulse_us) / 90;
    else
        return this->_neutral_pulse_us;
}

float Servo::clampf(float target_deg, float min_deg, float max_deg) const
{
    if (target_deg < min_deg)
        return min_deg;
    if (target_deg > max_deg)
        return max_deg;
    return target_deg;
}

float Servo::lerp(float a, float b, float t) const
{
    return a + (b - a) * t;
}

float Servo::smootherstep(float t) const
{
    t = this->clampf(t, 0.0f, 1.0f);
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

bool Servo::get_is_moving() const
{
    return this->_is_moving;
}

uint8_t Servo::get_channel() const
{
    return this->_pin;
}

uint16_t Servo::get_current_pulse() const
{
    return this->angle_to_pulse_ms(this->_current_pos_degree);
}

float Servo::get_current_pos_deg() const
{
    return this->_current_pos_degree;
}
