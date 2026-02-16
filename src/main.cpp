#include "../include/const.hpp"
#include "../include/externals.hpp"
#include "../include/Leg.hpp"


extern "C" void app_main(void)
{
    Leg leg_rf(RF_PAN_PIN, RF_TILT_PIN, RF_FOOT_PIN);
    Leg leg_rm(RM_PAN_PIN, RM_TILT_PIN, RM_FOOT_PIN);
    Leg leg_rb(RB_PAN_PIN, RB_TILT_PIN, RB_FOOT_PIN);
    Leg leg_lf(LF_PAN_PIN, LF_TILT_PIN, LF_FOOT_PIN);
    Leg leg_lm(LM_PAN_PIN, LM_TILT_PIN, LM_FOOT_PIN);
    Leg leg_lb(LB_PAN_PIN, LB_TILT_PIN, LB_FOOT_PIN);
}
