#include "../include/Leg.hpp"

Leg::Leg(i2c_master_dev_handle_t device, uint8_t pan_pin, uint8_t tilt1_pin, uint8_t tilt2_pin):
_pan_pin(pan_pin),
_tilt1_pin(tilt1_pin),
_tilt2_pin(tilt2_pin),
_device(device)
{}

void Leg::set_pos(double xpos, double ypos, double zpos)
{
    this->_xpos = xpos;
    this->_ypos = ypos;
    this->_zpos = zpos;
}
void Leg::move_degree(double pan_degree, double tilt1_degree, double tilt2_degree)
{
    uint16_t pan_pulse_us;
    uint16_t tilt1_pulse_us;
    uint16_t tilt2_pulse_us;

    pca9685_set_pulse_us(this->_device, this->_pan_pin, 50, pan_pulse_us);
    pca9685_set_pulse_us(this->_device, this->_tilt1_pin, 50, tilt1_pulse_us);
    pca9685_set_pulse_us(this->_device, this->_tilt2_pin, 50, tilt2_pulse_us);
}
