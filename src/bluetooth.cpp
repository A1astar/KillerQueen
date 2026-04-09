#include "../include/killerqueen.hpp"

esp_bd_addr_t gamepad_addr = {0x98, 0xB6, 0xE8, 0x69, 0x3C, 0xC9};

gamepad_data netral_state = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00};
gamepad_data dpad_up = {0x07, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
gamepad_data dpad_down = {0x07, 0x80, 0x80, 0x80, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};
gamepad_data dpad_left = {0x07, 0x80, 0x80, 0x80, 0x80, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
gamepad_data dpad_right = {0x07, 0x80, 0x80, 0x80, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
gamepad_data button_pressed_a = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00};
gamepad_data button_pressed_b = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x02, 0x00, 0x00, 0x00, 0x00};
gamepad_data button_pressed_x = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x08, 0x00, 0x00, 0x00, 0x00};
gamepad_data button_pressed_y = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00};
gamepad_data button_pressed_lb = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x40, 0x00, 0x00, 0x00, 0x00};
gamepad_data button_pressed_lt = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x00, 0x01, 0x00, 0xFF, 0x00};
gamepad_data button_pressed_rb = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00};
gamepad_data button_pressed_rt = {0x07, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x00, 0x0A, 0xFF, 0x00, 0x00};

/*
[0]      ID? (0x07)
[1]      Stick gauche X  (0x80 = centre)
[2]      Stick gauche Y  (0x80 = centre)
[3]      Stick droit X   (0x80 = centre)
[4]      Stick droit Y   (0x80 = centre)
[5]      D-pad (0x0F = neutre, 0x06 = gauche, 0x02 = droite, 0x04 = bas)
[6]      Boutons : A(0x01) B(0x02) X(0x08) Y(0x10) LB(0x40) RB(0x80)
[7]      Flags : LT(0x01) RT(0x02) Stick gauche pressed(0x20) Stick droit pressed(0x40)
[8]      RT analog (0x00 –> 0xFF)
[9]      LT analog (0x00 –> 0xFF)
[10]     Inconnu (0x00)
*/

static bool is_gamepad_addr(esp_bd_addr_t const gamepad_addr, esp_bd_addr_t const device_addr)
{
    return (memcmp(gamepad_addr, device_addr, ESP_BD_ADDR_LEN) == 0);
}

void print_hex_data(uint8_t *data, uint16_t data_len)
{
    for (uint16_t len = 0; len < data_len; len++)
        printf("%02X ", data[len]);
    printf("\n");
}

void print_dpad_datas(uint8_t data)
{
    switch (data)
    {
        case DPAD_NEUTRAL:
            printf("dpad_neutral\n");
        break;

        case DPAD_UP:
            printf("dpad_up\n");
        break;

        case DPAD_DOWN:
            printf("dpad_down\n");
        break;

        case DPAD_LEFT:
            printf("dpad_left\n");
        break;

        case DPAD_RIGHT:
            printf("dpad_right\n");
        break;

        case DPAD_UP_LEFT:
            printf("dpad_up_left\n");
        break;

        case DPAD_UP_RIGHT:
            printf("dpad_up_right\n");
        break;

        case DPAD_DOWN_LEFT:
            printf("dpad_down_left\n");
        break;

        case DPAD_DOWN_RIGHT:
            printf("dpad_down_right\n");
        break;
    }
}

static void bt_hidh_callback(esp_hidh_cb_event_t event, esp_hidh_cb_param_t *param)
{
    if(event == ESP_HIDH_INIT_EVT)
        printf("bt_hidh_callback() -> HIDH host is initialized\n");
    if(event == ESP_HIDH_DEINIT_EVT)
        printf("bt_hidh_callback() -> HIDH host is deinitialized\n");
    if(event == ESP_HIDH_OPEN_EVT)
        printf("bt_hidh_callback() -> HIDH host connection opened\n");
    if(event == ESP_HIDH_CLOSE_EVT)
        printf("bt_hidh_callback() -> HIDH host connection closed\n");
    if(event == ESP_HIDH_GET_RPT_EVT)
        printf("bt_hidh_callback() -> Get_Report command is called\n");
    if(event == ESP_HIDH_SET_RPT_EVT)
        printf("bt_hidh_callback() -> Set_Report command is called\n");
    if(event == ESP_HIDH_GET_PROTO_EVT)
        printf("bt_hidh_callback() -> Get_Protocol command is called\n");
    if(event == ESP_HIDH_SET_PROTO_EVT)
        printf("bt_hidh_callback() -> Set_Protocol command is called\n");
    if(event == ESP_HIDH_GET_IDLE_EVT)
        printf("bt_hidh_callback() -> Get_Idle command is called\n");
    if(event == ESP_HIDH_SET_IDLE_EVT)
        printf("bt_hidh_callback() -> Set_Idle command is called\n");
    if(event == ESP_HIDH_GET_DSCP_EVT)
        printf("bt_hidh_callback() -> HIDH is initialized\n");
    if(event == ESP_HIDH_ADD_DEV_EVT)
        printf("bt_hidh_callback() -> device is added\n");
    if(event == ESP_HIDH_RMV_DEV_EVT)
        printf("bt_hidh_callback() -> device is removed\n");
    if(event == ESP_HIDH_VC_UNPLUG_EVT)
        printf("bt_hidh_callback() -> virtually unplugged\n");
    if(event == ESP_HIDH_DATA_EVT)
        printf("bt_hidh_callback() -> HIDH send data on interrupt channel\n");
    if(event == ESP_HIDH_DATA_IND_EVT)
    {
        // param->data_ind.data;
        // param->data_ind.handle;
        // param->data_ind.len;
        // param->data_ind.proto_mode;
        // param->data_ind.status;

        printf("bt_hidh_callback() -> HIDH receive data on interrupt channel\n");
        //print_hex_data(param->data_ind.data,param->data_ind.len);
        print_dpad_datas(param->data_ind.data[DPAD_BYTE]);
    }
    if(event == ESP_HIDH_SET_INFO_EVT)
        printf("bt_hidh_callback() -> HID device descriptor set\n");
}

static void bt_gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    if(event == ESP_BT_GAP_DISC_RES_EVT)
    {
        printf("bt_gap_callback() -> Device discovery result event\n");
        if(is_gamepad_addr(gamepad_addr, param->disc_res.bda))
        {
            printf("GAMEPAD FOUND !!!\n");
            esp_bt_hid_host_connect(param->disc_res.bda);
            printf("GAMEPAD CONNECTED !!!\n");
            esp_bt_gap_cancel_discovery();
        }
    }
    if(event == ESP_BT_GAP_DISC_STATE_CHANGED_EVT)
        printf("bt_gap_callback() -> Discovery state changed event\n");
    if(event == ESP_BT_GAP_RMT_SRVCS_EVT)
        printf("bt_gap_callback() -> Get remote services event\n");
    if(event == ESP_BT_GAP_RMT_SRVC_REC_EVT)
        printf("bt_gap_callback() -> Get remote service record event\n");
    if(event == ESP_BT_GAP_AUTH_CMPL_EVT)
        printf("bt_gap_callback() -> Authentication complete event\n");
    if(event == ESP_BT_GAP_PIN_REQ_EVT)
        printf("bt_gap_callback() -> Legacy Pairing Pin code request\n");
    if(event == ESP_BT_GAP_CFM_REQ_EVT)
        printf("bt_gap_callback() -> Security Simple Pairing User Confirmation request\n");
    if(event == ESP_BT_GAP_KEY_NOTIF_EVT)
        printf("bt_gap_callback() -> Security Simple Pairing Passkey Notification\n");
    if(event == ESP_BT_GAP_KEY_REQ_EVT)
        printf("bt_gap_callback() -> Security Simple Pairing Passkey request \n");
    if(event == ESP_BT_GAP_READ_RSSI_DELTA_EVT)
        printf("bt_gap_callback() -> Read rssi event\n");
    if(event == ESP_BT_GAP_CONFIG_EIR_DATA_EVT)
        printf("bt_gap_callback() -> Config EIR data event\n");
    if(event == ESP_BT_GAP_SET_AFH_CHANNELS_EVT)
        printf("bt_gap_callback() -> Set AFH channels even\n");
    if(event == ESP_BT_GAP_READ_REMOTE_NAME_EVT)
        printf("bt_gap_callback() -> Read Remote Name event\n");
    if(event == ESP_BT_GAP_MODE_CHG_EVT)
        printf("bt_gap_callback() -> ESP_BT_GAP_MODE_CHG_EVT\n");
    if(event == ESP_BT_GAP_REMOVE_BOND_DEV_COMPLETE_EVT)
        printf("bt_gap_callback() -> remove bond device complete event\n");
    if(event == ESP_BT_GAP_QOS_CMPL_EVT)
        printf("bt_gap_callback() -> QOS complete event\n");
    if(event == ESP_BT_GAP_ACL_CONN_CMPL_STAT_EVT)
        printf("bt_gap_callback() -> ACL connection complete status event\n");
    if(event == ESP_BT_GAP_ACL_DISCONN_CMPL_STAT_EVT)
        printf("bt_gap_callback() -> ACL disconnection complete status event\n");
    if(event == ESP_BT_GAP_SET_PAGE_TO_EVT)
        printf("bt_gap_callback() -> Set page timeout event\n");
    if(event == ESP_BT_GAP_GET_PAGE_TO_EVT)
        printf("bt_gap_callback() -> Get page timeout event\n");
    if(event == ESP_BT_GAP_ACL_PKT_TYPE_CHANGED_EVT)
        printf("bt_gap_callback() -> Set ACL packet types event\n");
    if(event == ESP_BT_GAP_ENC_CHG_EVT)
        printf("bt_gap_callback() -> Encryption change event\n");
    if(event == ESP_BT_GAP_SET_MIN_ENC_KEY_SIZE_EVT)
        printf("bt_gap_callback() -> Set minimum encryption key size\n");
    if(event == ESP_BT_GAP_GET_DEV_NAME_CMPL_EVT)
        printf("bt_gap_callback() -> Get device name complete event\n");
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

void bt_pairing()
{
    ESP_ERROR_CHECK(esp_bt_hid_host_register_callback(bt_hidh_callback));
    ESP_ERROR_CHECK(esp_bt_hid_host_init());
    ESP_ERROR_CHECK(esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 0x30, 0));
}
