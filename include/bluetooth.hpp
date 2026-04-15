#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_hidh_api.h"
#include "esp_gap_bt_api.h"

void bt_hidh_callback(esp_hidh_cb_event_t event, esp_hidh_cb_param_t *param);
void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

#endif
