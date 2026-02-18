#include "../include/const.hpp"
#include "../include/killerqueen.hpp"
#include "../include/Leg.hpp"

extern "C" void app_main(void)
{
    pca9685_init(PCA9685_ADDR, GPIO_NUM_21, GPIO_NUM_22);
    pca9685_pwm(50);
    //i2c_master_transmit(device1, );

    // i2c_master_dev_handle_t device2;
    // i2c_init(PCA9685_ADDR, define.., define.., device2);

    // Leg leg_rf(RF_PAN_PIN, RF_TILT_PIN, RF_FOOT_PIN, device1);
    // Leg leg_rm(RM_PAN_PIN, RM_TILT_PIN, RM_FOOT_PIN, device1);
    // Leg leg_rb(RB_PAN_PIN, RB_TILT_PIN, RB_FOOT_PIN, device1);

    // Leg leg_lf(LF_PAN_PIN, LF_TILT_PIN, LF_FOOT_PIN, device2);
    // Leg leg_lm(LM_PAN_PIN, LM_TILT_PIN, LM_FOOT_PIN, device2);
    // Leg leg_lb(LB_PAN_PIN, LB_TILT_PIN, LB_FOOT_PIN, device2);
}
