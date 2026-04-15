#ifndef CONST_H
#define CONST_H

// ===== Naming rules =====
// RF_Leg -> right front leg
// RM_Leg -> right middle leg
// RB_leg -> right back leg
// LF_Leg -> left front leg
// LM_Leg -> left middle leg
// LB_leg -> left back leg

// ===== Cartesian coordinate system =====
//
//   Y(left)
//     \   Z(UP)
//      \  |
//       \ |
//          - - - X (forward)

// ===== Design dependent values =====
#define FIRST_PHALANX_LENGTH 150 //legth between pan servo and tilt servo (mm)
#define SECOND_PHALANX_LENGTH 100 //length between tilt servo and foot servo (mm)
#define FOOT_LENGTH 100 //length between foot servo and floor (mm)
#define ORIGIN_HEIGHT 100 //height of base leg servo (mm)

#define RF_LEG_X -70  //angle from x axis
#define RM_LEG_X -90  //angle from x axis
#define RB_LEG_X -110 //angle from x axis

#define LF_LEG_X 70  //angle from x axis
#define LM_LEG_X 90  //angle from x axis
#define LB_LEG_X 110 //angle from x axis

// ===== Hardware addresses =====
#define RIGHT_PCA9685_ADDR 0x40
#define LEFT_PCA9685_ADDR 0x80

// =====  Right side expender pins definition =====
#define RF_YAW_PIN 0
#define RF_ELBOW_PITCH_PIN 1
#define RF_FOOT_PITCH_PIN 2
#define RM_YAW_PIN 3
#define RM_ELBOW_PITCH_PIN 4
#define RM_FOOT_PITCH_PIN 5
#define RB_YAW_PIN 6
#define RB_ELBOW_PITCH_PIN 7
#define RB_FOOT_PITCH_PIN 8

// =====  Left side expender pins definition =====
#define LF_YAW_PIN 0
#define LF_ELBOW_PITCH_PIN 1
#define LF_FOOT_PITCH_PIN 2
#define LM_YAW_PIN 3
#define LM_ELBOW_PITCH_PIN 4
#define LM_FOOT_PITCH_PIN 5
#define LB_YAW_PIN 6
#define LB_ELBOW_PITCH_PIN 7
#define LB_FOOT_PITCH_PIN 8

// ===== Servo const =====
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz

// ===== Right front side servo calib values =====
#define RF_YAW_MIN 600
#define RF_YAW_NEUTRAL 1700
#define RF_YAW_MAX 2700

#define RF_ELBOW_PITCH_MIN 500
#define RF_ELBOW_PITCH_NEUTRAL 1500
#define RF_ELBOW_PITCH_MAX 2500

#define RF_FOOT_PITCH_MIN 700
#define RF_FOOT_PITCH_NEUTRAL 1800
#define RF_FOOT_PITCH_MAX 2800

// ===== Right middle side servo calib values =====
#define RM_YAW_MIN 600
#define RM_YAW_NEUTRAL 1700
#define RM_YAW_MAX 2700

#define RM_ELBOW_PITCH_MIN 500
#define RM_ELBOW_PITCH_NEUTRAL 1500
#define RM_ELBOW_PITCH_MAX 2500

#define RM_FOOT_PITCH_MIN 600
#define RM_FOOT_PITCH_NEUTRAL 1700
#define RM_FOOT_PITCH_MAX 2700

// ===== Right back side servo calib values =====
#define RB_YAW_MIN 600
#define RB_YAW_NEUTRAL 1700
#define RB_YAW_MAX 2700

#define RB_ELBOW_PITCH_MIN 500
#define RB_ELBOW_PITCH_NEUTRAL 1500
#define RB_ELBOW_PITCH_MAX 2500

#define RB_FOOT_PITCH_MIN 600
#define RB_FOOT_PITCH_NEUTRAL 1700
#define RB_FOOT_PITCH_MAX 2700

// ===== Left front side servo calib values =====
#define LF_YAW_MIN 600
#define LF_YAW_NEUTRAL 1700
#define LF_YAW_MAX 2700

#define LF_ELBOW_PITCH_MIN 500
#define LF_ELBOW_PITCH_NEUTRAL 1500
#define LF_ELBOW_PITCH_MAX 2500

#define LF_FOOT_PITCH_MIN 600
#define LF_FOOT_PITCH_NEUTRAL 1700
#define LF_FOOT_PITCH_MAX 2700

// ===== Left middle side servo calib values =====
#define LM_YAW_MIN 600
#define LM_YAW_NEUTRAL 1700
#define LM_YAW_MAX 2700

#define LM_ELBOW_PITCH_MIN 500
#define LM_ELBOW_PITCH_NEUTRAL 1500
#define LM_ELBOW_PITCH_MAX 2500

#define LM_FOOT_PITCH_MIN 600
#define LM_FOOT_PITCH_NEUTRAL 1700
#define LM_FOOT_PITCH_MAX 2700

// ===== Left back side servo calib values =====
#define LB_YAW_MIN 600
#define LB_YAW_NEUTRAL 1700
#define LB_YAW_MAX 2700

#define LB_ELBOW_PITCH_MIN 500
#define LB_ELBOW_PITCH_NEUTRAL 1500
#define LB_ELBOW_PITCH_MAX 2500

#define LB_FOOT_PITCH_MIN 600
#define LB_FOOT_PITCH_NEUTRAL 1700
#define LB_FOOT_PITCH_MAX 2700

// ===== datas =====
typedef uint8_t gamepad_data[11];


#endif
