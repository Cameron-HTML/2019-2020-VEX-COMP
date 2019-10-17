/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"
#include "pros/apix.h"

/**
 * You should add more #includes here
 */
//#include "okapi/api.hpp"
//#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
using namespace pros;
using namespace pros::literals;
//using namespace okapi;

// Define the motors
extern Motor frontLeftMotor, backLeftMotor, frontRightMotor, backRightMotor, trayMotor, leftIntake, rightIntake, armMotor;
extern int AutoSelection;

typedef struct trayPIDArg {
	bool trayPIDRunning = true;
	int inTarget = 0;
	int powerLimit = 0;
} _trayPIDArg;

typedef struct armPIDArg {
	bool armPIDRunning = false;
	int inTarget = 0;
	int powerLimit = 127;
} _armPIDArg;

extern _trayPIDArg* trayPIDPtr;
extern _armPIDArg* armPIDPtr;

// Function for the PID control
inline void trayPID(void* argument) {
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
		}

        // Delay code to stop CPU hoggin
        delay(20);
    }
}

// Function for the PID control
inline void armPID(void* argument) {
    _armPIDArg *armPIDPtr = (_armPIDArg *)argument;

    // Reset encoder value
    armMotor.tare_position();

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
		if(armPIDPtr->armPIDRunning) {
			target = armPIDPtr->inTarget;
			maxPower = armPIDPtr->powerLimit;

			// Calculate how far the robot is from the target
			error = target - armMotor.get_position();

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
			armMotor.move(finalPower);
		}

        // Delay code to stop CPU hoggin
        delay(20);
    }
}

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// You can add C++-only headers here
// Import IOStream Library
#include <iostream>

// Let the code know we're going to be calling things from IOStream
using namespace std;

#endif

#endif  // _PROS_MAIN_H_