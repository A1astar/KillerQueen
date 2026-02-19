#include "../include/const.hpp"
#include "../include/killerqueen.hpp"


extern "C" void app_main(void)
{
    pca9685_init(PCA9685_ADDR, GPIO_NUM_21, GPIO_NUM_22);
    pca9685_set_pwm(50);

    while (1)
    {
        pca9685_set_pulse_us(PIN14, 600);
        pca9685_set_pulse_us(PIN13, 600);
        pca9685_set_pulse_us(PIN12, 600);

        vTaskDelay(pdMS_TO_TICKS(1000));

        pca9685_set_pulse_us(PIN14, 1500);
        pca9685_set_pulse_us(PIN13, 1500);
        pca9685_set_pulse_us(PIN12, 1500);

        vTaskDelay(pdMS_TO_TICKS(1000));

        pca9685_set_pulse_us(PIN14, 2500);
        pca9685_set_pulse_us(PIN13, 2500);
        pca9685_set_pulse_us(PIN12, 2500);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
