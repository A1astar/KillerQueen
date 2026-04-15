#ifndef SERVO_HPP
#define SERVO_HPP

#include <stdint.h>

class Servo
{
    public:
        Servo
        (
            uint8_t const pin,
            uint16_t const min_pulse_us,
            uint16_t const max_pulse_us,
            uint16_t const neutral_pulse_us,
            float home_deg
        );

        void move_to(float target_deg, uint32_t duration_ms, uint64_t now_us);
        void update(uint64_t now_us);

        bool get_is_moving() const;
        uint8_t get_channel() const;
        uint16_t get_current_pulse() const;
        float get_current_pos_deg() const;

    private:
        uint16_t angle_to_pulse_us(float angle) const;
        float clampf(float current_val, float min_val, float max_val) const;
        float lerp(float a, float b, float t) const;
        float smootherstep(float t) const;

        uint8_t const _pin;
        uint16_t const _min_pulse_us;
        uint16_t const _max_pulse_us;
        uint16_t const _neutral_pulse_us;

        float _start_pos_degree;
        float _current_pos_degree;
        float _target_pos_degree;

        uint64_t _start_time_us;
        uint64_t _duration_us;

        bool _is_moving;
};

#endif
