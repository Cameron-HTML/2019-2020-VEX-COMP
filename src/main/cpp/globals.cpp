#include "../include/robot.hpp"

Motor trayMotor(3, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);
Motor leftIntake(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor rightIntake(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor armMotor(20, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS);