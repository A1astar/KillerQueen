#include "../include/MotionController.hpp"
#include <math.h>

MotionController::MotionController
(
    Pca9685 &left_side_controller,
    Pca9685 &right_side_controller,
    Leg &_Leg_rf,
    Leg &_Leg_rm,
    Leg &_Leg_rb,
    Leg &_Leg_lf,
    Leg &_Leg_lm,
    Leg &_Leg_lb,
    QueueHandle_t &data_queue
)
:   _Right_side_driver(right_side_controller),
    _Left_side_driver(left_side_controller),
    _Leg_rf(_Leg_rf),
    _Leg_rm(_Leg_rm),
    _Leg_rb(_Leg_rb),
    _Leg_lf(_Leg_lf),
    _Leg_lm(_Leg_lm),
    _Leg_lb(_Leg_lb),
    _last_command_us(0),
    _phase(0),
    _data_queue(data_queue),
    _data_buffer(0)
{}

void MotionController::start_demo(uint64_t now_us)
{
    this->_last_command_us = now_us;
    this->_phase = 0;
    this->_Leg_rf.move_servos_degree(0.0f, 0.0f, 0.0f, 500, now_us);
}

void MotionController::update(uint64_t now_us)
{
    if ((now_us - this->_last_command_us) >= 800000ULL)
    {
        if (this->_phase == 0)
            this->_Leg_rf.move_servos_degree(0.0f, 90.0f, 0.0f, 500, now_us);
        else if (this->_phase == 1)
            this->_Leg_rf.move_servos_degree(0.0f, -90.0f, 0.0f, 500, now_us);
        else
            this->_Leg_rf.move_servos_degree(0.0f, 0.0f, 0.0f, 500, now_us);

        this->_phase = (this->_phase + 1) % 3;
        this->_last_command_us = now_us;
    }

    this->_Leg_rf.update(now_us);
    this->_Leg_rf.write(this->_Right_side_driver);
}

void MotionController::move(float forward, float lateral, float rotation)
{
    (void)forward;
    (void)lateral;
    (void)rotation;
}

uint8_t *MotionController::get_data()
{
    xQueueReceive(this->_data_queue, &this->_data_buffer, portMAX_DELAY);
    return this->_data_buffer;
}
