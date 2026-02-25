#ifndef LEG_HPP
#define LEG_HPP

#include "killerqueen.hpp"

class Leg
{
    public:
        Leg(i2c_master_dev_handle_t device, uint8_t pan_pin, uint8_t tilt1_pin, uint8_t tilt2_pin);
        void set_pos(double xpos, double ypos, double zpos);
        void move_degree(double pan_degree, double tilt1_degree, double tilt2_deree);

    private:
        i2c_master_dev_handle_t _device;

        uint8_t _pan_pin;
        uint8_t _tilt1_pin;
        uint8_t _tilt2_pin;

        double _xpos;
        double _ypos;
        double _zpos;

        double _pan_degree;
        double _tilt1_degree;
        double _tilt2_degree;
};

#endif
