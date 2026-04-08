#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_hidh_api.h"
#include "esp_gap_bt_api.h"


void setup_bt_hidh();
void setup_bt_gap();
void setup_bt_bluedroid();
void setup_bt_controller();
void bt_pairing();

#endif
