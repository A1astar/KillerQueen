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
#define PCA9685_ADDR 0x40 // default PCA9685 i2c addr

// ===== Pins definition =====
#define RF_PAN_PIN 1
#define RF_TILT_PIN 2
#define RF_FOOT_PIN 3

#define RM_PAN_PIN 4
#define RM_TILT_PIN 5
#define RM_FOOT_PIN 5

#define RB_PAN_PIN 7
#define RB_TILT_PIN 8
#define RB_FOOT_PIN 9

#define LF_PAN_PIN 10
#define LF_TILT_PIN 11
#define LF_FOOT_PIN 12

#define LM_PAN_PIN 13
#define LM_TILT_PIN 14
#define LM_FOOT_PIN 15

#define LB_PAN_PIN 16
#define LB_TILT_PIN 17
#define LB_FOOT_PIN 18

// ===== Servo const =====
#define SERVOMIN 80 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 1000 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USNEUTRAL 1500
#define USMAX 2000 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates#endif

#endif
