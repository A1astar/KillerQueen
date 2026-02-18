#include "../include/const.hpp"
#include "../include/killerqueen.hpp"

extern "C" void app_main(void)
{
    pca9685_init(PCA9685_ADDR, GPIO_NUM_21, GPIO_NUM_22);
    pca9685_set_pwm(50);
    pca9685_output_control(PIN15, 8);
    while (1)
    {
    }
}
