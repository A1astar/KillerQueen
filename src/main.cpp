#include "../include/const.hpp"
#include "../include/killerqueen.hpp"

extern "C" void app_main(void)
{
    i2c_master_bus_handle_t master_bus;

    pca9685_device_t device1;
    device1.frequence = SERVO_FREQ;

    master_bus_init(&master_bus,GPIO_NUM_21, GPIO_NUM_22);
    pca9685_init(PCA9685_ADDR, master_bus, &device1.handler);
    pca9685_set_pwm(device1.handler, device1.frequence);

    while (1)
    {
        pca9685_set_pulse_us(device1, PIN15, USMIN);
        pca9685_set_pulse_us(device1, PIN12, USMIN);

        vTaskDelay(pdMS_TO_TICKS(1000));

        // pca9685_set_pulse_us(device1, PIN15, SERVO_FREQ, 1600);
        // pca9685_set_pulse_us(device1, PIN12, SERVO_FREQ, 1700);

        pca9685_set_pulse_us(device1, PIN15, USNEUTRAL);
        pca9685_set_pulse_us(device1, PIN12, USNEUTRAL);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
