#ifndef SERVO_HPP
#define SERVO_HPP

#include "killerqueen.hpp"

class Servo
{
    public:
        Servo(pca9685_device_t const device, uint8_t const pin, uint16_t const min_pulse_us, uint16_t const max_pulse_us, uint16_t const neutral_pulse_us);

        void move_servo_to_degree(float target_pos_degree);
        uint16_t angle_to_pulse_ms(float angle);

        uint16_t get_min_pulse_us() const;
        uint16_t get_max_pulse_us() const;
        uint16_t get_neutral_pulse_us() const;
        float get_current_pos_degree();

    private:

        pca9685_device_t const _device;
        uint8_t const _pin;
        uint16_t const _min_pulse_us;
        uint16_t const _max_pulse_us;
        uint16_t const _neutral_pulse_us;
        float _current_pos_degree;
};

#endif
