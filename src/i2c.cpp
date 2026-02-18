#include "../include/const.hpp"
#include "../include/killerqueen.hpp"

void i2c_init(uint16_t device_addr, gpio_num_t sda, gpio_num_t scl)
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

    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&master_bus_config, &bus_handle));

    i2c_device_config_t device_config {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = PCA9685_ADDR,
        .scl_speed_hz = 30000000,
        .scl_wait_us = 0,
        .flags {
            .disable_ack_check = false,
        }
    };

    i2c_master_dev_handle_t device;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &device_config, &device));
}
