#include "../include/killerqueen.hpp"

void nvs_init()
{
    if(nvs_flash_init() == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }
}

void i2c_master_bus_init(i2c_master_bus_handle_t *master_bus, gpio_num_t sda, gpio_num_t scl)
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
    ESP_ERROR_CHECK(i2c_new_master_bus(&master_bus_config, master_bus));
}

void queues_init()
{
    bt_data_queue = xQueueCreate(1, sizeof(gamepad_data));
    if(bt_data_queue == NULL)
        printf("failed to create bt_data_queue\n");
    else
        printf("bt_data_queue created\n");

    motion_data_queue = xQueueCreate(1, sizeof(t_motion_data));
    if(motion_data_queue == NULL)
        printf("failed to create motion_data_queue\n");
    else
        printf("motion_data_queue created\n");
}

void bt_init()
{
    esp_bt_controller_config_t bt_controller_conf = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_controller_conf));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT));
    ESP_ERROR_CHECK(esp_bt_sleep_disable());

    esp_bluedroid_config_t bt_bluedroid_conf = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bluedroid_init_with_cfg(&bt_bluedroid_conf));
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    ESP_ERROR_CHECK(esp_bt_gap_register_callback(bt_gap_callback));
    ESP_ERROR_CHECK(esp_bt_gap_set_device_name("KillerQueen"));
    ESP_ERROR_CHECK(esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE));

    ESP_ERROR_CHECK(esp_bt_hid_host_register_callback(bt_hidh_callback));
    ESP_ERROR_CHECK(esp_bt_hid_host_init());
}
