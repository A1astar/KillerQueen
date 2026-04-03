#include "../include/killerqueen.hpp"
#include "../include/Servo.hpp"
#include "../include/Leg.hpp"
#include "../include/Pca9685.hpp"
#include "../include/MotionController.hpp"

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
    /*i2c master bus init*/
    static i2c_master_bus_handle_t master_bus;
    master_bus_init(&master_bus, GPIO_NUM_21, GPIO_NUM_22);

    /*pca9685 init*/
    static Pca9685 right_pca9685(master_bus, RIGHT_PCA9685_ADDR);
    right_pca9685.init();
    right_pca9685.set_pwm(SERVO_FREQ);

    static Pca9685 left_pca9685(master_bus, LEFT_PCA9685_ADDR);
    left_pca9685.init();
    left_pca9685.set_pwm(SERVO_FREQ);

    /*right servos init*/
    static Servo Servo_rf_yaw(RF_YAW_PIN, RF_YAW_MIN, RF_YAW_MAX, RF_YAW_NEUTRAL, 0);
    static Servo Servo_rf_elbow_pitch(RF_ELBOW_PITCH_PIN, RF_ELBOW_PITCH_MIN, RF_YAW_MAX, RF_ELBOW_PITCH_NEUTRAL, 0);
    static Servo Servo_rf_foot_pitch(RF_FOOT_PITCH_PIN, RF_FOOT_PITCH_MIN, RF_FOOT_PITCH_MAX, RF_FOOT_PITCH_NEUTRAL, 0);
    static Servo Servo_rm_yaw(RM_YAW_PIN, RM_YAW_MIN, RM_YAW_MAX, RM_YAW_NEUTRAL, 0);
    static Servo Servo_rm_elbow_pitch(RM_ELBOW_PITCH_PIN, RM_ELBOW_PITCH_MIN, RM_YAW_MAX, RM_ELBOW_PITCH_NEUTRAL, 0);
    static Servo Servo_rm_foot_pitch(RM_FOOT_PITCH_PIN, RM_FOOT_PITCH_MIN, RM_FOOT_PITCH_MAX, RM_FOOT_PITCH_NEUTRAL, 0);
    static Servo Servo_rb_yaw(RB_YAW_PIN, RB_YAW_MIN, RB_YAW_MAX, RB_YAW_NEUTRAL, 0);
    static Servo Servo_rb_elbow_pitch(RB_ELBOW_PITCH_PIN, RB_ELBOW_PITCH_MIN, RB_YAW_MAX, RB_ELBOW_PITCH_NEUTRAL, 0);
    static Servo Servo_rb_foot_pitch(RB_FOOT_PITCH_PIN, RB_FOOT_PITCH_MIN, RB_FOOT_PITCH_MAX, RB_FOOT_PITCH_NEUTRAL, 0);

    /*left servos init*/
    static Servo Servo_lf_yaw(LF_YAW_PIN, LF_YAW_MIN, LF_YAW_MAX, LF_YAW_NEUTRAL, 0);
    static Servo Servo_lf_elbow_pitch(LF_ELBOW_PITCH_PIN, LF_ELBOW_PITCH_MIN, LF_YAW_MAX, LF_ELBOW_PITCH_NEUTRAL, 0);
    static Servo Servo_lf_foot_pitch(LF_FOOT_PITCH_PIN, LF_FOOT_PITCH_MIN, LF_FOOT_PITCH_MAX, LF_FOOT_PITCH_NEUTRAL, 0);
    static Servo Servo_lm_yaw(LM_YAW_PIN, LM_YAW_MIN, LM_YAW_MAX, LM_YAW_NEUTRAL, 0);
    static Servo Servo_lm_elbow_pitch(LM_ELBOW_PITCH_PIN, LM_ELBOW_PITCH_MIN, LM_YAW_MAX, LM_ELBOW_PITCH_NEUTRAL, 0);
    static Servo Servo_lm_foot_pitch(LM_FOOT_PITCH_PIN, LM_FOOT_PITCH_MIN, LM_FOOT_PITCH_MAX, LM_FOOT_PITCH_NEUTRAL, 0);
    static Servo Servo_lb_yaw(LB_YAW_PIN, LB_YAW_MIN, LB_YAW_MAX, LB_YAW_NEUTRAL, 0);
    static Servo Servo_lb_elbow_pitch(LB_ELBOW_PITCH_PIN, LB_ELBOW_PITCH_MIN, LB_YAW_MAX, LB_ELBOW_PITCH_NEUTRAL, 0);
    static Servo Servo_lb_foot_pitch(LB_FOOT_PITCH_PIN, LB_FOOT_PITCH_MIN, LB_FOOT_PITCH_MAX, LB_FOOT_PITCH_NEUTRAL, 0);

    /*right legs init*/
    static Leg Leg_rf(Servo_rf_yaw, Servo_rf_elbow_pitch, Servo_rf_foot_pitch);
    static Leg Leg_rm(Servo_rm_yaw, Servo_rm_elbow_pitch, Servo_rm_foot_pitch);
    static Leg Leg_rb(Servo_rb_yaw, Servo_rb_elbow_pitch, Servo_rb_foot_pitch);

    /*left legs init*/
    static Leg Leg_lf(Servo_lf_yaw, Servo_lf_elbow_pitch, Servo_lf_foot_pitch);
    static Leg Leg_lm(Servo_lm_yaw, Servo_lm_elbow_pitch, Servo_lm_foot_pitch);
    static Leg Leg_lb(Servo_lb_yaw, Servo_lb_elbow_pitch, Servo_lb_foot_pitch);

    /*motion controller init */
    static MotionController MotionController(left_pca9685, right_pca9685, Leg_rf, Leg_rm, Leg_rb, Leg_lf, Leg_lm, Leg_lb);
}
