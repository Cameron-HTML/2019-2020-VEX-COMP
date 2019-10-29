// Include drivetrain header file
#include "../include/drivetrain.hpp"

Motor frontLeftMotor(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor backLeftMotor(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor frontRightMotor(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor backRightMotor(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);

void DrivetrainClass::update(int leftVal, int rightVal) {
    frontLeftMotor.move(leftVal);
    backLeftMotor.move(leftVal);
    frontRightMotor.move(rightVal);
    backRightMotor.move(leftVal);
}