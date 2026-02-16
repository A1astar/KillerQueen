#include "../include/Leg.hpp"

Leg::Leg(uint8_t pan_pin, uint8_t tilt_pin, uint8_t foot_pin) :
_pan_pin(pan_pin),
_tilt_pin(tilt_pin),
_foot_pin(foot_pin)
{}

void Leg::move(double x, double y, double z)
{
    (void)x;
    (void)y;
    (void)z;
}
