#include "../include/Leg.hpp"

Leg::Leg(Servo &Servo_yaw, Servo &Servo_elbow_pitch, Servo &Servo_foot_pitch)
:   _Servo_yaw(Servo_yaw),
    _Servo_elbow_pitch(Servo_elbow_pitch),
    _Servo_foot_pitch(Servo_foot_pitch)
{}

void Leg::move_servos_degree
(
    float yaw_deg,
    float elbow_pitch_deg,
    float foot_pitch_deg,
    uint32_t duration_ms,
    uint64_t now_us
)
{
    this->_Servo_yaw.move_to(yaw_deg, duration_ms, now_us);
    this->_Servo_elbow_pitch.move_to(elbow_pitch_deg, duration_ms, now_us);
    this->_Servo_foot_pitch.move_to(foot_pitch_deg, duration_ms, now_us);
}

void Leg::update(uint64_t now_us)
{
    this->_Servo_yaw.update(now_us);
    this->_Servo_elbow_pitch.update(now_us);
    this->_Servo_foot_pitch.update(now_us);
}

void Leg::write(Pca9685 &driver)
{
    driver.write_pulse_us(this->_Servo_yaw.get_channel(), 0, this->_Servo_yaw.get_current_pulse());
    driver.write_pulse_us(this->_Servo_elbow_pitch.get_channel(), 0, this->_Servo_elbow_pitch.get_current_pulse());
    driver.write_pulse_us(this->_Servo_foot_pitch.get_channel(), 0, this->_Servo_foot_pitch.get_current_pulse());
}
