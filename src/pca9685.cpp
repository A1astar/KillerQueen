#include "../include/Pca9685.hpp"

Pca9685::Pca9685(i2c_master_bus_handle_t master_bus, uint16_t device_addr) :
_device_addr(device_addr),
_device_freq_hz(0),
_master_bus(master_bus),
_device(NULL)
{}

esp_err_t Pca9685::init()
{
    esp_err_t ret_val;

    i2c_device_config_t device_config {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = this->_device_addr,
        .scl_speed_hz = 1000000,
        .scl_wait_us = 0,
        .flags {
            .disable_ack_check = false,
        }
    };

    ret_val = i2c_master_bus_add_device(this->_master_bus, &device_config, &this->_device);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = this->write_register(MODE1_REG, AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = this->write_register(MODE2_REG, OUTDRV);
    if(ret_val != ESP_OK)
        return ret_val;

    return ESP_OK;
}

esp_err_t Pca9685::set_pwm(uint16_t freq_hz)
{
    if(freq_hz < 24 || freq_hz > 1526)
        return ESP_ERR_INVALID_ARG;

    uint16_t prescaler_value = (25000000 / (4096 * freq_hz)) - 1;
    esp_err_t ret_val;

    ret_val = this->write_register(MODE1_REG, SLEEP | AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = this->write_register(PRESCALE_REG, (uint8_t)prescaler_value);
    if(ret_val != ESP_OK)
        return ret_val;

    ret_val = this->write_register(MODE1_REG, AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    ets_delay_us(500);

    ret_val = this->write_register(MODE1_REG, RESTART | AI | ALLCALL);
    if(ret_val != ESP_OK)
        return ret_val;

    this->_device_freq_hz = freq_hz;

    return ESP_OK;
}

esp_err_t Pca9685::write_register(uint8_t reg, uint8_t data)
{
    i2c_master_transmit_multi_buffer_info_t buffer[2] = {
        {.write_buffer = &reg, .buffer_size = 1},
        {.write_buffer = &data, .buffer_size = 1},
    };
    return i2c_master_multi_buffer_transmit(this->_device, buffer, 2, -1);
}

esp_err_t Pca9685::write_pulse_us(uint8_t pin, uint16_t delay_us, uint16_t pulse_us)
{
    if(pin > 15)
        return ESP_ERR_INVALID_ARG;

    uint16_t total_us = 1000000 / this->_device_freq_hz;

    uint16_t asserted_tick_val = ((delay_us * 4096) / total_us);
    uint16_t negated_tick_val = ((pulse_us * 4096) / total_us) + asserted_tick_val - 1;

    uint8_t assereted_l = (uint8_t)(asserted_tick_val & 0xFF);
    uint8_t assereted_h = (uint8_t)(asserted_tick_val >> 8) & 0x0F;
    uint8_t negated_l = (uint8_t)(negated_tick_val & 0xFF) ;
    uint8_t negated_h = (uint8_t)(negated_tick_val >> 8) & 0x0F;

    uint8_t start_reg = 0x06 + (4 * pin);

    i2c_master_transmit_multi_buffer_info_t buffer[5] = {
        {.write_buffer = &start_reg, .buffer_size = 1},
        {.write_buffer = &assereted_l, .buffer_size = 1},
        {.write_buffer = &assereted_h, .buffer_size = 1},
        {.write_buffer = &negated_l, .buffer_size = 1},
        {.write_buffer = &negated_h, .buffer_size = 1},
    };

    return i2c_master_multi_buffer_transmit(this->_device, buffer, 5, -1);
}


