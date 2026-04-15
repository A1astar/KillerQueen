#include "../include/killerqueen.hpp"

void action_task(void *pv_arg)
{
    //TODO: task for robot action ->future hardware (leds, sounds, etc.)
    TickType_t last_wake = xTaskGetTickCount();
    while (true)
    {
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));
    }
}

void motion_task(void *pv_arg)
{
    MotionController *Controller = static_cast<MotionController*>(pv_arg);
    t_motion_data motion_data;
    uint64_t now_us = (uint64_t)esp_timer_get_time();

    Controller->start_demo(now_us);
    Controller->move(0, 0, 0);

    TickType_t last_wake = xTaskGetTickCount();
    while (true)
    {
        if(xQueueReceive(motion_data_queue, &motion_data, pdMS_TO_TICKS(10)) == pdPASS)
        {
            print_motion_data_queue(motion_data);
            Controller->move(motion_data.forward, motion_data.lateral, motion_data.lateral);
        }
        now_us = (uint64_t)esp_timer_get_time();
        Controller->update(now_us);
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));
    }
}

void bt_data_parsing_task(void *pv_arg)
{
    ESP_ERROR_CHECK(esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 0x30, 0));

    gamepad_data raw_data;
    t_motion_data motion_data;

    TickType_t last_wake = xTaskGetTickCount();
    while (true)
    {
        if(xQueueReceive(raw_data_queue, &raw_data, portMAX_DELAY) == pdPASS)
        {
            motion_data.forward = raw_data[LEFT_STICK_Y_BYTE];
            motion_data.lateral = raw_data[LEFT_STICK_X_BYTE];
            motion_data.rotation = raw_data[RIGHT_STICK_X_BYTE];
            xQueueSend(motion_data_queue, (void *)&motion_data, portMAX_DELAY);
        }
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(10));
    }
}
