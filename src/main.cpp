#include "../include/const.hpp"
#include "../include/killerqueen.hpp"

extern "C" void app_main(void)
{
    i2c_master_bus_handle_t master_bus;
    i2c_master_dev_handle_t device1;

    master_bus_init(&master_bus,GPIO_NUM_21, GPIO_NUM_22);
    pca9685_init(PCA9685_ADDR, master_bus, &device1);
    pca9685_set_pwm(device1, 50);

    while (1)
    {
        pca9685_set_pulse_us(device1, PIN14, 50, 600);
        pca9685_set_pulse_us(device1, PIN13, 50, 600);
        pca9685_set_pulse_us(device1, PIN12, 50, 600);

        vTaskDelay(pdMS_TO_TICKS(1000));

        pca9685_set_pulse_us(device1, PIN14, 50, 1500);
        pca9685_set_pulse_us(device1, PIN13, 50, 1500);
        pca9685_set_pulse_us(device1, PIN12, 50, 1500);

        vTaskDelay(pdMS_TO_TICKS(1000));

        pca9685_set_pulse_us(device1, PIN14, 50, 2500);
        pca9685_set_pulse_us(device1, PIN13, 50, 2500);
        pca9685_set_pulse_us(device1, PIN12, 50, 2500);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
