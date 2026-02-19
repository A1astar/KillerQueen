#include "../include/killerqueen.hpp"

i2c_master_dev_handle_t device_handle;
i2c_master_bus_handle_t bus_handle;
static uint16_t current_freq_hz = 0;

static esp_err_t write_register(uint8_t reg, uint8_t data)
{
    i2c_master_transmit_multi_buffer_info_t buffer[2] = {
        {.write_buffer = &reg, .buffer_size = 1},
        {.write_buffer = &data, .buffer_size = 1},
    };
    return i2c_master_multi_buffer_transmit(device_handle, buffer, 2, -1);
}

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

    if(write_register(MODE1_REG, AI | ALLCALL) != ESP_OK)
        return -1;
    if(write_register(MODE2_REG, OUTDRV) != ESP_OK)
        return -1;
    return 0;
}

int pca9685_set_pwm(uint16_t freq_hz)
{
    if(freq_hz < 24 || freq_hz > 1526)
        return -1;

    uint16_t prescaler_value = (25000000 / (4096 * freq_hz)) - 1;

    // Turn off the internal oscillator
    if(write_register(MODE1_REG, SLEEP | AI | ALLCALL) != ESP_OK)
        return -1;

    // Set the prescale value
    if(write_register(PRESCALE_REG, (uint8_t)prescaler_value) != ESP_OK)
        return -1;

    //turn on oscillator
    if(write_register(MODE1_REG, AI | ALLCALL) != ESP_OK)
        return -1;

    //wait at least 500us for oscillator stability
    ets_delay_us(500);

    //restart device
    if(write_register(MODE1_REG, RESTART | AI | ALLCALL) != ESP_OK)
        return -1;

    current_freq_hz = freq_hz;
    return 0;
}

int pca9685_set_pulse_us(uint8_t output_pin, uint16_t pulse_us)
{
    if(output_pin > 15 || current_freq_hz == 0)
        return -1;

    uint16_t asserted_tick_val = 0x00; // 0% delay for phase shift
    uint16_t total_us = 1000000 / current_freq_hz;
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

    if(i2c_master_multi_buffer_transmit(device_handle, buffer, 5, -1) != ESP_OK)
        return -1;
    return 0;
}
