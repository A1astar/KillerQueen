#include "../include/killerqueen.hpp"
#include "../include/Servo.hpp"
#include "../include/Leg.hpp"

void msg_exit(const char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

esp_err_t init_device_via_i2c(i2c_master_bus_handle_t master_bus, uint16_t device_addr, uint16_t device_freq_hz, pca9685_device_t *device)
{
    esp_err_t ret;

    device->frequence = device_freq_hz;

    ret = pca9685_init(RIGHT_PCA9685_ADDR, master_bus, &(*device).handler);
    if (ret != ESP_OK)
        return ret;

    ret = pca9685_set_pwm(device->handler, device->frequence);
    if (ret != ESP_OK)
        return ret;

    return ESP_OK;
}

extern "C" void app_main(void)
{
    i2c_master_bus_handle_t master_bus;
    pca9685_device_t right_side_device;
    pca9685_device_t left_side_device;

    if(master_bus_init(&master_bus, GPIO_NUM_21, GPIO_NUM_22) != ESP_OK)
        msg_exit("I2C master bus init FAILED!\n");
    printf("2C master bus init OK !\n");

    if(init_device_via_i2c(master_bus, RIGHT_PCA9685_ADDR, SERVO_FREQ, &right_side_device) != ESP_OK)
        msg_exit("R-PCA9685 init FAILED!\n");
    printf("R-PCA9685 init OK !\n");

    // if(init_device_via_i2c(master_bus, LEFT_PCA9685_ADDR, SERVO_FREQ, &left_side_device) != ESP_OK)
    //     msg_exit("L-PCA9685 init FAILED!\n");
    // printf("L-PCA9685 init OK !\n");

    Servo Servo_rf_yaw(right_side_device, RF_YAW_PIN, RF_YAW_MIN, RF_YAW_MAX, RF_YAW_NEUTRAL);
    Servo Servo_rf_elbow_pitch(right_side_device, RF_ELBOW_PITCH_PIN, RF_ELBOW_PITCH_MIN, RF_YAW_MAX, RF_ELBOW_PITCH_NEUTRAL);
    Servo Servo_rf_foot_pitch(right_side_device, RF_FOOT_PITCH_PIN, RF_FOOT_PITCH_MIN, RF_FOOT_PITCH_MAX, RF_FOOT_PITCH_NEUTRAL);

    Servo Servo_rm_yaw(right_side_device, RM_YAW_PIN, RM_YAW_MIN, RM_YAW_MAX, RM_YAW_NEUTRAL);
    Servo Servo_rm_elbow_pitch(right_side_device, RM_ELBOW_PITCH_PIN, RM_ELBOW_PITCH_MIN, RM_YAW_MAX, RM_ELBOW_PITCH_NEUTRAL);
    Servo Servo_rm_foot_pitch(right_side_device, RM_FOOT_PITCH_PIN, RM_FOOT_PITCH_MIN, RM_FOOT_PITCH_MAX, RM_FOOT_PITCH_NEUTRAL);

    Servo Servo_rb_yaw(right_side_device, RB_YAW_PIN, RB_YAW_MIN, RB_YAW_MAX, RB_YAW_NEUTRAL);
    Servo Servo_rb_elbow_pitch(right_side_device, RB_ELBOW_PITCH_PIN, RB_ELBOW_PITCH_MIN, RB_YAW_MAX, RB_ELBOW_PITCH_NEUTRAL);
    Servo Servo_rb_foot_pitch(right_side_device, RB_FOOT_PITCH_PIN, RB_FOOT_PITCH_MIN, RB_FOOT_PITCH_MAX, RB_FOOT_PITCH_NEUTRAL);

    Servo Servo_lf_yaw(left_side_device, LF_YAW_PIN, LF_YAW_MIN, LF_YAW_MAX, LF_YAW_NEUTRAL);
    Servo Servo_lf_elbow_pitch(left_side_device, LF_ELBOW_PITCH_PIN, LF_ELBOW_PITCH_MIN, LF_YAW_MAX, LF_ELBOW_PITCH_NEUTRAL);
    Servo Servo_lf_foot_pitch(left_side_device, LF_FOOT_PITCH_PIN, LF_FOOT_PITCH_MIN, LF_FOOT_PITCH_MAX, LF_FOOT_PITCH_NEUTRAL);

    Servo Servo_lm_yaw(left_side_device, LM_YAW_PIN, LM_YAW_MIN, LM_YAW_MAX, LM_YAW_NEUTRAL);
    Servo Servo_lm_elbow_pitch(left_side_device, LM_ELBOW_PITCH_PIN, LM_ELBOW_PITCH_MIN, LM_YAW_MAX, LM_ELBOW_PITCH_NEUTRAL);
    Servo Servo_lm_foot_pitch(left_side_device, LM_FOOT_PITCH_PIN, LM_FOOT_PITCH_MIN, LM_FOOT_PITCH_MAX, LM_FOOT_PITCH_NEUTRAL);

    Servo Servo_lb_yaw(left_side_device, LB_YAW_PIN, LB_YAW_MIN, LB_YAW_MAX, LB_YAW_NEUTRAL);
    Servo Servo_lb_elbow_pitch(left_side_device, LB_ELBOW_PITCH_PIN, LB_ELBOW_PITCH_MIN, LB_YAW_MAX, LB_ELBOW_PITCH_NEUTRAL);
    Servo Servo_lb_foot_pitch(left_side_device, LB_FOOT_PITCH_PIN, LB_FOOT_PITCH_MIN, LB_FOOT_PITCH_MAX, LB_FOOT_PITCH_NEUTRAL);

    Leg Leg_rf(Servo_rf_yaw, Servo_rf_elbow_pitch, Servo_rf_foot_pitch);
    Leg Leg_rm(Servo_rm_yaw, Servo_rm_elbow_pitch, Servo_rm_foot_pitch);
    Leg Leg_rb(Servo_rb_yaw, Servo_rb_elbow_pitch, Servo_rb_foot_pitch);

    Leg Leg_lf(Servo_lf_yaw, Servo_lf_elbow_pitch, Servo_lf_foot_pitch);
    Leg Leg_lm(Servo_lm_yaw, Servo_lm_elbow_pitch, Servo_lm_foot_pitch);
    Leg Leg_lb(Servo_lb_yaw, Servo_lb_elbow_pitch, Servo_lb_foot_pitch);

    while (1)
    {
        Leg_rf.move_servos_degree(0, 0, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(30, 30, 30);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(60, 60, 60);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(30, 30, 30);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(0, 0, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(-30, -30, -30);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(-60, -60, -60);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(-80, -80, -80);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(-60, -60, -60);
        vTaskDelay(pdMS_TO_TICKS(500));

        Leg_rf.move_servos_degree(-30, -30, -30);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


