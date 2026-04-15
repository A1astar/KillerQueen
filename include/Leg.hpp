#ifndef LEG_HPP
#define LEG_HPP

#include "Servo.hpp"
#include "Pca9685.hpp"

#pragma once

class Leg
{
    public:
        Leg(Servo &Servo_yaw, Servo &Servo_elbow_pitch, Servo &Servo_foot_pitch);

        void move_servos_degree
        (
            float yaw_deg,
            float elbow_pitch_deg,
            float foot_pitch_deg,
            uint32_t duration_ms,
            uint64_t now_us
        );

        void update(uint64_t now_us);
        void write(Pca9685 &driver);

    private:

        Servo &_Servo_yaw;
        Servo &_Servo_elbow_pitch;
        Servo &_Servo_foot_pitch;
};

#endif
