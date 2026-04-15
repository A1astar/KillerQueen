#include "../include/killerqueen.hpp"

esp_bd_addr_t gamepad_addr = {0x98, 0xB6, 0xE8, 0x69, 0x3C, 0xC9};

static inline bool is_gamepad_addr(esp_bd_addr_t const gamepad_addr, esp_bd_addr_t const device_addr)
{
    return (memcmp(gamepad_addr, device_addr, ESP_BD_ADDR_LEN) == 0);
}

void bt_hidh_callback(esp_hidh_cb_event_t event, esp_hidh_cb_param_t *param)
{
    switch (event)
    {
        case ESP_HIDH_INIT_EVT:
            printf("bt_hidh_callback() -> HIDH host is initialized\n");
        break;

        case ESP_HIDH_DEINIT_EVT:
            printf("bt_hidh_callback() -> HIDH host is deinitialized\n");
        break;

        case ESP_HIDH_OPEN_EVT:
            printf("bt_hidh_callback() -> HIDH host connection opened\n");
        break;

        case ESP_HIDH_CLOSE_EVT:
            printf("bt_hidh_callback() -> HIDH host connection closed\n");
            ESP_ERROR_CHECK(esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 0x30, 0));
        break;

        case ESP_HIDH_DATA_IND_EVT:
            printf("bt_hidh_callback() -> HIDH receive data on interrupt channel\n");
            xQueueSend(raw_data_queue, param->data_ind.data, portMAX_DELAY);
        break;

        default:
        break;
    }
}

void connect_controller(esp_bt_gap_cb_param_t *param)
{
    if(is_gamepad_addr(gamepad_addr, param->disc_res.bda))
    {
        esp_bt_hid_host_connect(param->disc_res.bda);
        esp_bt_gap_cancel_discovery();
        printf("Controller connected\n");
    }
}

void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event)
    {
        case ESP_BT_GAP_DISC_RES_EVT:
            connect_controller(param);
        break;

        default:
        break;
    }
}
