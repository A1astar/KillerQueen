#include "../include/killerqueen.hpp"

esp_bd_addr_t gamepad_addr = {0x98, 0xB6, 0xE9, 0x69, 0x3C, 0xC9};

static void bt_hidh_callback(esp_hidh_cb_event_t event, esp_hidh_cb_param_t *param)
{
    if(event == ESP_HIDH_INIT_EVT)
        printf("HIDH host is initialized\n");
    if(event == ESP_HIDH_DEINIT_EVT)
        printf("HIDH host is deinitialized\n");
    if(event == ESP_HIDH_OPEN_EVT)
        printf("HIDH host connection opened\n");
    if(event == ESP_HIDH_CLOSE_EVT)
        printf("HIDH host connection closed\n");
    if(event == ESP_HIDH_GET_DSCP_EVT)
        printf("HIDH initialized\n");
    if(event == ESP_HIDH_ADD_DEV_EVT)
        printf("HIDH device is added\n");
    if(event == ESP_HIDH_RMV_DEV_EVT)
        printf("HIDH device is removed\n");
    if(event == ESP_HIDH_DATA_EVT)
        printf("HIDH send data on interrupt channel\n");
    if(event == ESP_HIDH_DATA_IND_EVT)
        printf("HIDH receive data on interrupt channel\n");
}

static void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    if(event == ESP_BT_GAP_DISC_RES_EVT)
        printf("Device discovery result event\n");
    if(event == ESP_BT_GAP_DISC_STATE_CHANGED_EVT)
        printf("Discovery state changed event\n");
    if(event == ESP_BT_GAP_RMT_SRVCS_EVT)
        printf("Get remote services event\n");
    if(event == ESP_BT_GAP_RMT_SRVC_REC_EVT)
        printf("Get remote service record event\n");
    if(event == ESP_BT_GAP_AUTH_CMPL_EVT)
        printf("Authentication complete event\n");
    if(event == ESP_BT_GAP_PIN_REQ_EVT)
        printf("Legacy Pairing Pin code request\n");
    if(event == ESP_BT_GAP_CFM_REQ_EVT)
        printf("Security Simple Pairing User Confirmation request\n");
    if(event == ESP_BT_GAP_KEY_NOTIF_EVT)
        printf("Security Simple Pairing Passkey Notification\n");
    if(event == ESP_BT_GAP_KEY_REQ_EVT)
        printf("Security Simple Pairing Passkey request \n");
    if(event == ESP_BT_GAP_READ_RSSI_DELTA_EVT)
        printf("Read rssi event\n");
    if(event == ESP_BT_GAP_CONFIG_EIR_DATA_EVT)
        printf(" Config EIR data event\n");
    if(event == ESP_BT_GAP_SET_AFH_CHANNELS_EVT)
        printf("Set AFH channels even\n");
    if(event == ESP_BT_GAP_READ_REMOTE_NAME_EVT)
        printf("Read Remote Name event\n");
    if(event == ESP_BT_GAP_MODE_CHG_EVT)
        printf("ESP_BT_GAP_MODE_CHG_EVT\n");
    if(event == ESP_BT_GAP_REMOVE_BOND_DEV_COMPLETE_EVT)
        printf("remove bond device complete event\n");
    if(event == ESP_BT_GAP_QOS_CMPL_EVT)
        printf("QOS complete event\n");
    if(event == ESP_BT_GAP_ACL_CONN_CMPL_STAT_EVT)
        printf("ACL connection complete status event\n");
    if(event == ESP_BT_GAP_ACL_DISCONN_CMPL_STAT_EVT)
        printf("ACL disconnection complete status event\n");
    if(event == ESP_BT_GAP_SET_PAGE_TO_EVT)
        printf("Set page timeout event\n");
    if(event == ESP_BT_GAP_GET_PAGE_TO_EVT)
        printf("Get page timeout event\n");
    if(event == ESP_BT_GAP_ACL_PKT_TYPE_CHANGED_EVT)
        printf("Set ACL packet types event\n");
    if(event == ESP_BT_GAP_ENC_CHG_EVT)
        printf("Encryption change event\n");
    if(event == ESP_BT_GAP_SET_MIN_ENC_KEY_SIZE_EVT)
        printf("Set minimum encryption key size\n");
    if(event == ESP_BT_GAP_GET_DEV_NAME_CMPL_EVT)
        printf("Get device name complete event\n");
}

void setup_bt_controller()
{
    esp_bt_controller_config_t bt_controller_conf = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_controller_conf));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT));
    ESP_ERROR_CHECK(esp_bt_sleep_disable());
}

void setup_bt_bluedroid()
{
    esp_bluedroid_config_t bt_bluedroid_conf = BT_BLUEDROID_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_bluedroid_init_with_cfg(&bt_bluedroid_conf));
    ESP_ERROR_CHECK(esp_bluedroid_enable());
}

void setup_bt_gap()
{
    ESP_ERROR_CHECK(esp_bt_gap_register_callback(bt_gap_callback));
    ESP_ERROR_CHECK(esp_bt_gap_set_device_name("KillerQueen"));
    ESP_ERROR_CHECK(esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE));
}

void setup_bt_hidh()
{
    ESP_ERROR_CHECK(esp_bt_hid_host_register_callback(bt_hidh_callback));
    ESP_ERROR_CHECK(esp_bt_hid_host_init());
}

void bt_pairing()
{
    ESP_ERROR_CHECK(esp_bt_hid_host_register_callback(bt_hidh_callback));
    ESP_ERROR_CHECK(esp_bt_hid_host_init());
    //ESP_ERROR_CHECK(esp_bt_gap_start_discovery()); //TODO
    //esp_bt_hid_host_connect(); //TODO
}
