#ifndef INIT_HPP
#define INIT_HPP

#include <driver/i2c_master.h>

void nvs_init();
void i2c_master_bus_init(i2c_master_bus_handle_t *master_bus, gpio_num_t sda, gpio_num_t scl);
void queues_init();
void bt_init();

#endif
