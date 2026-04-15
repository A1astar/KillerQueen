#ifndef SERIAL_PRINT_HPP
#define SERIAL_PRINT_HPP

#include "bluetooth.hpp"

#define ID_BYTE 0
#define LEFT_STICK_X_BYTE 1
#define LEFT_STICK_Y_BYTE 2
#define RIGHT_STICK_X_BYTE 3
#define RIGHT_STICK_Y_BYTE 4
#define DPAD_BYTE 5
#define MAIN_BUTTONS_BYTE 6
#define SECOND_BUTTONS_BYTE 7
#define LEFT_TRIGGER_ANALOG_BYTE 8
#define RIGHT_TRIGGER_ANALOG_BYTE 9
#define FUTURE_USE_BYTE 10

#define DPAD_NEUTRAL 0x0F
#define DPAD_UP 0x00
#define DPAD_DOWN 0x04
#define DPAD_LEFT 0x06
#define DPAD_RIGHT 0x02
#define DPAD_UP_LEFT 0x07
#define DPAD_UP_RIGHT 0x01
#define DPAD_DOWN_LEFT 0x05
#define DPAD_DOWN_RIGHT 0x03

void print_hex_data(uint8_t *data, uint16_t data_len);
void print_dpad_datas(uint8_t data);

#endif
