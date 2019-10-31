// Include drivetrain header file
#include "../include/tray.hpp"

TrayClass::TrayClass() :
    trayMotor(3, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS)
{

}

void TrayClass::update(int manual, bool macro) {

    // Manual control check || 1 = Forward & -1 Backward
    if(manual == 1) {
        PIDRunning = false;
        trayMotor.move(80);
        target = trayMotor.get_position();
	} else if(manual == -1) {
        PIDRunning = false;
        trayMotor.move(-90);
        target = trayMotor.get_position();
	} else {
		if(powerLimit == 80 && trayMotor.get_position() <= 20) {
            PIDRunning = false;
            trayMotor.move(0);
		} else {
            if(!PIDRunning) {
                PIDRunning = true;
            }
        }
	}

    // Macro control check
    if(macro) {
        PIDRunning = true;

        if(target <= 10) {
            target = 4000;
            powerLimit = 70;
        } else if(target >= 1600) {
            target = 10;
            powerLimit = 80;
        }
    }
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