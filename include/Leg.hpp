#pragma once

#ifndef LEG_HPP
#define LEG_HPP

#include "const.hpp"
#include "killerqueen.hpp"

class Leg
{
    public:
        Leg(uint8_t pan_pin, uint8_t tilt_pin, uint8_t foot_pin, i2c_master_dev_handle_t &device);
        void move(double x, double y, double z);

    private:
        uint8_t _pan_pin;
        uint8_t _tilt_pin;
        uint8_t _foot_pin;
        i2c_master_dev_handle_t &_device;
};

#endif
