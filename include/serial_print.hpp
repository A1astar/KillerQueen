#ifndef SERIAL_PRINT_HPP
#define SERIAL_PRINT_HPP

#include "bluetooth.hpp"
#include "const.hpp"

void print_hex_data(uint8_t *data, uint16_t data_len);
void print_dpad_datas(uint8_t data);
void print_motion_data_queue(t_motion_data motion_data);

#endif
