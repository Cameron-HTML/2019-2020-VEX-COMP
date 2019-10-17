#include "main.h"

Motor frontLeftMotor(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor backLeftMotor(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor frontRightMotor(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor backRightMotor(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor trayMotor(3, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);
Motor leftIntake(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor rightIntake(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor armMotor(20, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS);

int autoSelection = 0;

_trayPIDArg* trayPIDPtr = new _trayPIDArg();
_armPIDArg* armPIDPtr = new _armPIDArg();