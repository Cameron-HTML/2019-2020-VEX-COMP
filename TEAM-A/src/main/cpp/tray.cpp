// Include drivetrain header file
#include "../include/tray.hpp"

TrayClass::TrayClass() :
    trayMotor(11, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS)
{

}

void TrayClass::update(int manual) {
    // Manual control check || 1 = Forward & -1 Backward & 2 PID off
    switch (manual) {
    case 1:
        PIDRunning = false;
        trayMotor.move(80);
        target = trayMotor.get_position();
        break;
    case -1:
        PIDRunning = false;
        trayMotor.move(-90);
        target = trayMotor.get_position();
        break;
    default:
        PIDRunning = true;
        break;
    }

    PID();
}

// Function for the Tray PID control
void TrayClass::PID() {
    if(PIDRunning) {
        powerLimit = powerLimit;

        // Calculate how far the robot is from the target
        error = target - trayMotor.get_position();

        // Calculate the proportion
        proportion = kP * error;

        // Check if intergral should be used
        if(abs(error) < intergralActiveZone && error != 0) {
            intergralRaw += error;
        } else {
            intergralRaw = 0;
        }

        // Limit the raw intergral
        if(intergralRaw > intergralPowerLimit) {
            intergralRaw = intergralPowerLimit;
        } else if(intergralRaw < -intergralPowerLimit) {
            intergralRaw = -intergralPowerLimit;
        }

        // Scale intergral
        intergral = kI * intergralRaw;

        // Calculate derivative
        derivative = kD * (error - lastError);
        
        // Update last error
        lastError = error;

        // Set derivative to 0 if at target
        if(error == 0) {
            derivative = 0;
        }

        // Calculate the final power to send to the motors
        finalPower = proportion + intergral + derivative;

        // Limit final power
        if(finalPower > powerLimit) {
            finalPower = powerLimit;
        } else if(finalPower < -powerLimit) {
            finalPower = -powerLimit;
        }

        // Set the motors to the final power
        trayMotor.move(finalPower);
    }
}