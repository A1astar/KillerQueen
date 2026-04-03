#ifndef MOTIONCONTROLLER_HPP
#define MOTIONCONTROLLER_HPP

#include "Leg.hpp"
#include "Pca9685.hpp"

class MotionController
{
    public:
        MotionController
        (
            Pca9685 &left_side_controller,
            Pca9685 &right_side_controller,
            Leg &_Leg_rf,
            Leg &_Leg_rm,
            Leg &_Leg_rb,
            Leg &_Leg_lf,
            Leg &_Leg_lm,
            Leg &_Leg_lb
        );

        void start_demo(uint64_t now_us);
        void update(uint64_t now_us);

    private:

        Pca9685 &_Right_side_driver;
        Pca9685 &_Left_side_driver;

        Leg &_Leg_rf;
        Leg &_Leg_rm;
        Leg &_Leg_rb;

        Leg &_Leg_lf;
        Leg &_Leg_lm;
        Leg &_Leg_lb;

        uint64_t _last_command_us;
        uint32_t _phase;
};

#endif
