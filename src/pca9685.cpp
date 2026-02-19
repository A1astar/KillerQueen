#include "../include/killerqueen.hpp"

static esp_err_t write_register(i2c_master_dev_handle_t device, uint8_t reg, uint8_t data)
{
    i2c_master_transmit_multi_buffer_info_t buffer[2] = {
        {.write_buffer = &reg, .buffer_size = 1},
        {.write_buffer = &data, .buffer_size = 1},
    };
    return i2c_master_multi_buffer_transmit(device, buffer, 2, -1);
}

esp_err_t master_bus_init(i2c_master_bus_handle_t *master_bus, gpio_num_t sda, gpio_num_t scl)
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
    return i2c_new_master_bus(&master_bus_config, master_bus);
}

esp_err_t pca9685_init(uint16_t addr, i2c_master_bus_handle_t master_bus, i2c_master_dev_handle_t *device)
{
    esp_err_t ret_val;

    i2c_device_config_t device_config {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = addr,
        .scl_speed_hz = 1000000,
        .scl_wait_us = 0,
        .flags {
            .disable_ack_check = false,
        }
    };
    ret_val = i2c_master_bus_add_device(master_bus, &device_config, device);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = write_register(*device, MODE1_REG, AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = write_register(*device, MODE2_REG, OUTDRV);
    if(ret_val != ESP_OK)
        return ret_val;

    return ESP_OK;
}

esp_err_t pca9685_set_pwm(i2c_master_dev_handle_t device, uint16_t freq_hz)
{
    if(freq_hz < 24 || freq_hz > 1526)
        return ESP_ERR_INVALID_ARG;

    uint16_t prescaler_value = (25000000 / (4096 * freq_hz)) - 1;
    esp_err_t ret_val;

    ret_val = write_register(device, MODE1_REG, SLEEP | AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = write_register(device, PRESCALE_REG, (uint8_t)prescaler_value);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = write_register(device, MODE1_REG, AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    ets_delay_us(500);

    ret_val = write_register(device, MODE1_REG, RESTART | AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    return ESP_OK;
}

esp_err_t pca9685_set_pulse_us(i2c_master_dev_handle_t device, uint8_t output_pin, uint16_t freq_hz, uint16_t pulse_us)
{
    if(output_pin > 15)
        return ESP_ERR_INVALID_ARG;

    uint16_t asserted_tick_val = 0x00;
    uint16_t total_us = 1000000 / freq_hz;
    uint16_t negated_tick_val = ((pulse_us * 4096) / total_us) - 1;

    uint8_t assereted_l = (uint8_t)(asserted_tick_val & 0xFF);
    uint8_t assereted_h = (uint8_t)(asserted_tick_val >> 8) & 0x0F;
    uint8_t negated_l = (uint8_t)(negated_tick_val & 0xFF) ;
    uint8_t negated_h = (uint8_t)(negated_tick_val >> 8) & 0x0F;

    uint8_t start_reg = 0x06 + (4 * output_pin);

    i2c_master_transmit_multi_buffer_info_t buffer[5] = {
        {.write_buffer = &start_reg, .buffer_size = 1},
        {.write_buffer = &assereted_l, .buffer_size = 1},
        {.write_buffer = &assereted_h, .buffer_size = 1},
        {.write_buffer = &negated_l, .buffer_size = 1},
        {.write_buffer = &negated_h, .buffer_size = 1},
    };

    return i2c_master_multi_buffer_transmit(device, buffer, 5, -1);
}
