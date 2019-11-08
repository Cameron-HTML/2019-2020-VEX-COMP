// Include drivetrain header file
#include "../include/intake.hpp"

IntakeClass::IntakeClass() :
    leftIntake(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS),
    rightIntake(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS)
{

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