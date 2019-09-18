#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

typedef struct trayPIDArg {
	bool trayPIDRunning = false;
	int inTarget = 0;
	int powerLimit = 0;
} _trayPIDArg;

	// Function for the PID control
void trayPID(void* argument) {
	_trayPIDArg *trayPIDPtr = (_trayPIDArg *)argument;

    // Reset encoder value
    trayMotor.tare_position();

	int target = 0;

    // PID variables decloration and initialization
    float kP = 0.3;
    float kI = 0.00001;
    float kD = 0.1;

    // Proportion variable decloration
    float proportion;
    float intergral;
    int intergralRaw;
    int derivative;

    // Error variable decloration
    int error;
    int lastError;

    // Variable so the robot know when it should use intergral
    const float intergralActiveZone = 10;

    // Variable to limit the value of intergßral
    int intergralPowerLimit = 50 / kI;

	int maxPower = 0;

    // Final output power/speed
    int finalPower;

    while(true) {
		if(trayPIDPtr->trayPIDRunning) {
			target = trayPIDPtr->inTarget;
			maxPower = trayPIDPtr->powerLimit;

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
			if(finalPower > maxPower) {
				finalPower = maxPower;
			} else if(finalPower < -maxPower) {
				finalPower = -maxPower;
			}

			// Set the motors to the final power
			trayMotor.move(finalPower);

			cout << "Running" << endl;
		}

        // Delay code to stop CPU hoggin
        delay(20);
    }
}

void opcontrol() {
	Controller master(E_CONTROLLER_MASTER);

	_trayPIDArg* trayPIDPtr = new _trayPIDArg();
	Task TrayTask(trayPID, trayPIDPtr);
	
	trayMotor.tare_position();

	// Variable decloration and initialization
	int threshold = 15;

	while (true) {
		// Control for the left side of the drive trainß
		if(abs(master.get_analog(ANALOG_LEFT_Y)) >= threshold) {
			frontLeftMotor.move(master.get_analog(ANALOG_LEFT_Y));
			backLeftMotor.move(master.get_analog(ANALOG_LEFT_Y));
		} else {
			frontLeftMotor.move(0);	
			backLeftMotor.move(0);
		}

		// Control for the right side of the drive train
		if(abs(master.get_analog(ANALOG_RIGHT_Y)) >= threshold) {
			frontRightMotor.move(master.get_analog(ANALOG_RIGHT_Y));
			backRightMotor.move(master.get_analog(ANALOG_RIGHT_Y));
		} else {
			frontRightMotor.move(0);
			backRightMotor.move(0);
		}

		// Tray auto place macro
		if(master.get_digital(DIGITAL_A)) {
			while(master.get_digital(DIGITAL_A)) delay(20);

			if(trayPIDPtr->trayPIDRunning) {
				trayPIDPtr->trayPIDRunning = false;
			} else {
				trayPIDPtr->trayPIDRunning = true;
			}
		}

		if(master.get_digital(DIGITAL_B)) {
			while(master.get_digital(DIGITAL_B)) delay(20);

			if(trayPIDPtr->trayPIDRunning && trayPIDPtr->inTarget == 10 || trayPIDPtr->trayPIDRunning && trayPIDPtr->inTarget == 0) {
				trayPIDPtr->inTarget = 1600;
				trayPIDPtr->powerLimit = 60;
			} else if(trayPIDPtr->trayPIDRunning && trayPIDPtr->inTarget >= 1600) {
				trayPIDPtr->inTarget = 10;
				trayPIDPtr->powerLimit = 80;
			}
		}

		// Tray manual control
		if(master.get_digital(DIGITAL_R1) == 1) {
			trayMotor.move(80);
		} else if(master.get_digital(DIGITAL_R2) == 1) {
			trayMotor.move(-90);
		} else {
			trayMotor.move(0);
		}

		// Arm control
		if(master.get_digital(DIGITAL_X) == 1) {
			armMotor.move(127);
		} else if(master.get_digital(DIGITAL_Y) == 1) {
			armMotor.move(-127);
		} else {
			armMotor.move(0);
		}

		// Intake control
		if(master.get_digital(DIGITAL_L1) == 1) {
			leftIntake.move(127);
			rightIntake.move(127);
		} else if(master.get_digital(DIGITAL_L2) == 1) {
			leftIntake.move(-127);
			rightIntake.move(-127);
		} else {
			leftIntake.move(0);
			rightIntake.move(0);
		}

		// Delay task to stop CPU hogging
		delay(20);
		cout << trayMotor.get_position() << endl;
	}
}
