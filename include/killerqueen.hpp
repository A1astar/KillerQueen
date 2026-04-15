#ifndef KILLERQUEEN_H
#define KILLERQUEEN_H

// ===== libs =====
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/ringbuf.h"
#include "freertos/queue.h"
#include "esp_timer.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>

#include "bluetooth.hpp"
#include "const.hpp"
#include "serial_print.hpp"
#include "bluetooth.hpp"
#include "tasks.hpp"

// ===== Class =====
#include "MotionController.hpp"
#include "Pca9685.hpp"
#include "Leg.hpp"
#include "Servo.hpp"
#include "init.hpp"

// ===== Global Var =====
extern QueueHandle_t raw_data_queue;
extern QueueHandle_t motion_data_queue;
extern QueueHandle_t action_data_queue;


#endif
