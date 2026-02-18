#include "../include/killerqueen.hpp"

i2c_master_dev_handle_t device_handle;
i2c_master_bus_handle_t bus_handle;

int pca9685_init(uint16_t addr, gpio_num_t sda, gpio_num_t scl)
{
    i2c_master_bus_config_t master_bus_config {
        .i2c_port = -1,
        .sda_io_num = sda,
        .scl_io_num = scl,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags {
            .enable_internal_pullup = true,
            .allow_pd = false,
        }
    };

    if(i2c_new_master_bus(&master_bus_config, &bus_handle) != ESP_OK)
        return -1;

    i2c_device_config_t device_config {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = addr,
        .scl_speed_hz = 1000000,
        .scl_wait_us = 0,
        .flags {
            .disable_ack_check = false,
        }
    };

    if(i2c_master_bus_add_device(bus_handle, &device_config, &device_handle) != ESP_OK)
        return -1;

    uint8_t reg = MODE1_REG;
    uint8_t data = ALLCALL | SLEEP;
    i2c_master_transmit_multi_buffer_info_t buffer[2] = {
        {.write_buffer = &reg, .buffer_size = 1},
        {.write_buffer = &data, .buffer_size = 1},
    };
    if(i2c_master_multi_buffer_transmit(device_handle, buffer, 2, -1) != ESP_OK)
        return -1;
    return 0;
}

int pca9685_pwm(uint16_t freq_hz)
{
    if(freq_hz < 24 || freq_hz > 1526)
        return -1;
    uint16_t prescaler_value = round(25000000 / (4096 * freq_hz)) - 1;

    uint8_t reg = PRESCALE_REG;
    uint8_t data = (uint8_t)prescaler_value;
    i2c_master_transmit_multi_buffer_info_t buffer1[2] = {
        {.write_buffer = &reg, .buffer_size = 1},
        {.write_buffer = &data, .buffer_size = 1},
    };
    if(i2c_master_multi_buffer_transmit(device_handle, buffer1, 2, -1) != ESP_OK)
        return -1;

    reg = MODE1_REG;
    data = ALLCALL;
    i2c_master_transmit_multi_buffer_info_t buffer2[2] = {
        {.write_buffer = &reg, .buffer_size = 1},
        {.write_buffer = &data, .buffer_size = 1},
    };
    if(i2c_master_multi_buffer_transmit(device_handle, buffer2, 2, -1) != ESP_OK)
        return -1;
    return 0;
}
