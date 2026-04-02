#include "../include/killerqueen.hpp"
#include "../include/Servo.hpp"
#include "../include/Leg.hpp"
#include "../include/Pca9685.hpp"

esp_err_t master_bus_init(i2c_master_bus_handle_t *master_bus, gpio_num_t sda, gpio_num_t scl)
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
    return i2c_new_master_bus(&master_bus_config, master_bus);
}

extern "C" void app_main(void)
{
    i2c_master_bus_handle_t master_bus;
    master_bus_init(&master_bus, GPIO_NUM_21, GPIO_NUM_22);

    Pca9685 right_pca9685(master_bus, RIGHT_PCA9685_ADDR);
    right_pca9685.init();
    right_pca9685.set_pwm(SERVO_FREQ);

    Pca9685 left_pca9685(master_bus, LEFT_PCA9685_ADDR);
    left_pca9685.init();
    left_pca9685.set_pwm(SERVO_FREQ);

    Servo Servo_rf_yaw(right_pca9685, RF_YAW_PIN, RF_YAW_MIN, RF_YAW_MAX, RF_YAW_NEUTRAL);
    Servo Servo_rf_elbow_pitch(right_pca9685, RF_ELBOW_PITCH_PIN, RF_ELBOW_PITCH_MIN, RF_YAW_MAX, RF_ELBOW_PITCH_NEUTRAL);
    Servo Servo_rf_foot_pitch(right_pca9685, RF_FOOT_PITCH_PIN, RF_FOOT_PITCH_MIN, RF_FOOT_PITCH_MAX, RF_FOOT_PITCH_NEUTRAL);

    Servo Servo_rm_yaw(right_pca9685, RM_YAW_PIN, RM_YAW_MIN, RM_YAW_MAX, RM_YAW_NEUTRAL);
    Servo Servo_rm_elbow_pitch(right_pca9685, RM_ELBOW_PITCH_PIN, RM_ELBOW_PITCH_MIN, RM_YAW_MAX, RM_ELBOW_PITCH_NEUTRAL);
    Servo Servo_rm_foot_pitch(right_pca9685, RM_FOOT_PITCH_PIN, RM_FOOT_PITCH_MIN, RM_FOOT_PITCH_MAX, RM_FOOT_PITCH_NEUTRAL);

    Servo Servo_rb_yaw(right_pca9685, RB_YAW_PIN, RB_YAW_MIN, RB_YAW_MAX, RB_YAW_NEUTRAL);
    Servo Servo_rb_elbow_pitch(right_pca9685, RB_ELBOW_PITCH_PIN, RB_ELBOW_PITCH_MIN, RB_YAW_MAX, RB_ELBOW_PITCH_NEUTRAL);
    Servo Servo_rb_foot_pitch(right_pca9685, RB_FOOT_PITCH_PIN, RB_FOOT_PITCH_MIN, RB_FOOT_PITCH_MAX, RB_FOOT_PITCH_NEUTRAL);

    Servo Servo_lf_yaw(left_pca9685, LF_YAW_PIN, LF_YAW_MIN, LF_YAW_MAX, LF_YAW_NEUTRAL);
    Servo Servo_lf_elbow_pitch(left_pca9685, LF_ELBOW_PITCH_PIN, LF_ELBOW_PITCH_MIN, LF_YAW_MAX, LF_ELBOW_PITCH_NEUTRAL);
    Servo Servo_lf_foot_pitch(left_pca9685, LF_FOOT_PITCH_PIN, LF_FOOT_PITCH_MIN, LF_FOOT_PITCH_MAX, LF_FOOT_PITCH_NEUTRAL);

    Servo Servo_lm_yaw(left_pca9685, LM_YAW_PIN, LM_YAW_MIN, LM_YAW_MAX, LM_YAW_NEUTRAL);
    Servo Servo_lm_elbow_pitch(left_pca9685, LM_ELBOW_PITCH_PIN, LM_ELBOW_PITCH_MIN, LM_YAW_MAX, LM_ELBOW_PITCH_NEUTRAL);
    Servo Servo_lm_foot_pitch(left_pca9685, LM_FOOT_PITCH_PIN, LM_FOOT_PITCH_MIN, LM_FOOT_PITCH_MAX, LM_FOOT_PITCH_NEUTRAL);

    Servo Servo_lb_yaw(left_pca9685, LB_YAW_PIN, LB_YAW_MIN, LB_YAW_MAX, LB_YAW_NEUTRAL);
    Servo Servo_lb_elbow_pitch(left_pca9685, LB_ELBOW_PITCH_PIN, LB_ELBOW_PITCH_MIN, LB_YAW_MAX, LB_ELBOW_PITCH_NEUTRAL);
    Servo Servo_lb_foot_pitch(left_pca9685, LB_FOOT_PITCH_PIN, LB_FOOT_PITCH_MIN, LB_FOOT_PITCH_MAX, LB_FOOT_PITCH_NEUTRAL);

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
