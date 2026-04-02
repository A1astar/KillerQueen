#include "../include/Leg.hpp"

Leg::Leg(Servo &Servo_yaw, Servo &Servo_elbow_pitch, Servo &Servo_foot_pitch) :
_Servo_yaw(Servo_yaw),
_Servo_elbow_pitch(Servo_elbow_pitch),
_Servo_foot_pitch(Servo_foot_pitch)
{}

void Leg::move_servos_degree(float yaw_degree, float elbow_pitch_degree, float foot_pitch_degree)
{
    this->_Servo_yaw.move_servo_to_degree(yaw_degree);
    this->_Servo_elbow_pitch.move_servo_to_degree(elbow_pitch_degree);
    this->_Servo_foot_pitch.move_servo_to_degree(foot_pitch_degree);
}
