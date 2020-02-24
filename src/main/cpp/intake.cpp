// Include drivetrain header file
#include "../include/intake.hpp"

IntakeClass::IntakeClass() :
    leftIntake(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS),
    rightIntake(10 /* 10 */, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS)
{
    leftIntake.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    rightIntake.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void IntakeClass::update(int manual, int speed) {
    // Manual control check || 1 = Forward & -1 Backward & 2 PID off
    switch (manual) {
    case 1:
        leftIntake.move(speed);
        rightIntake.move(speed);
        break;
    case -1:
        leftIntake.move(-speed);
        rightIntake.move(-speed);
        break;
    case 0:
        leftIntake.move(0);
        rightIntake.move(0);
        break;
    }
}