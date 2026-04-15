#include "../include/killerqueen.hpp"

void action_task(void *pv_arg)
{
    //TODO: task for robot action ->future hardware (leds, sounds, etc.)
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void motion_task(void *pv_arg)
{
    MotionController *Controller = static_cast<MotionController*>(pv_arg);

    uint64_t now_us = (uint64_t)esp_timer_get_time();

    Controller->start_demo(now_us);

    TickType_t last_wake = xTaskGetTickCount();

    while (true)
    {
        now_us = (uint64_t)esp_timer_get_time();
        Controller->update(now_us);
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));
    }
}

void bt_data_parsing_task(void *pv_arg)
{
    ESP_ERROR_CHECK(esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 0x30, 0));

    while (true)
    {
        // if(queue_recieve(bt_data_queue))
        // {
        //     parse
        //     queue_send(motion_data_queue)
        // }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
