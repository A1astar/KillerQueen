#include "../include/killerqueen.hpp"

extern "C" void app_main(void)
{
    i2c_master_bus_handle_t master_bus;
    pca9685_device_t device1;

    device1.frequence = SERVO_FREQ;

    if (master_bus_init(&master_bus,GPIO_NUM_21, GPIO_NUM_22) != ESP_OK)
    {
        printf("Master Bus init error\n");
        exit(1);
    }
    if (pca9685_init(PCA9685_ADDR, master_bus, &device1.handler) != ESP_OK)
    {
        printf("pca9685 init error\n");
        exit(1);
    }
    if (pca9685_set_pwm(device1.handler, device1.frequence) != ESP_OK)
    {
        printf("pca9685 set pwm error\n");
        exit(1);
    }

    printf("Init ok\n");

    pca9685_set_pulse_us(device1, PIN15, 0, USNEUTRAL);

    while (1)
    {
    }
}
