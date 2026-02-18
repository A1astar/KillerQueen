#ifndef KILLERQUEEN_H
#define KILLERQUEEN_H

// ===== includes =====
#include <math.h> //for inverse kinematics
#include <driver/i2c_master.h> //for communication with servo driver expander

// ===== i2c.c =====
void i2c_init(uint16_t device_addr, gpio_num_t sda, gpio_num_t scl);

#endif
