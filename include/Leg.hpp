#ifndef LEG_HPP
#define LEG_HPP

#include "Servo.hpp"

class Leg
{
    public:
        Leg(Servo &Servo_yaw, Servo &Servo_elbow_pitch, Servo &Servo_foot_pitch);

        void move_servos_degree(float yaw_degree, float elbow_pitch_degree, float foot_pitch_degree);

    private:
        Servo &_Servo_yaw;
        Servo &_Servo_elbow_pitch;
        Servo &_Servo_foot_pitch;
};

#endif
