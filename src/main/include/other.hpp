// /**
//  * \file main.h
//  *
//  * Contains common definitions and header files used throughout your PROS
//  * project.
//  *
//  * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
//  * All rights reserved.
//  *
//  * This Source Code Form is subject to the terms of the Mozilla Public
//  * License, v. 2.0. If a copy of the MPL was not distributed with this
//  * file, You can obtain one at http://mozilla.org/MPL/2.0/.
//  */

// #ifndef _PROS_MAIN_H_
// 	#define _PROS_MAIN_H_
// 	#define PROS_USE_SIMPLE_NAMES
// 	#define PROS_USE_LITERALS

// 	// Includes
// 	#include "api.h"
// 	#include "../../../libraries/pros/apix.h"

// 	// Namespaces
// 	using namespace pros;
// 	using namespace pros::literals;

// 	// Define the motors
// 	extern Motor trayMotor, leftIntake, rightIntake, armMotor;
// 	extern int AutoSelection;

// 	typedef struct trayPIDArg {
// 		bool trayPIDRunning = true;
// 		int inTarget = 0;
// 		int powerLimit = 0;
// 	} _trayPIDArg;

// 	typedef struct armPIDArg {
// 		bool armPIDRunning = false;
// 		int inTarget = 0;
// 		int powerLimit = 127;
// 	} _armPIDArg;

// 	extern _trayPIDArg* trayPIDPtr;
// 	extern _armPIDArg* armPIDPtr;

// 	// Function for the PID control
// 	inline void armPID(void* argument) {
// 		_armPIDArg *armPIDPtr = (_armPIDArg *)argument;

// 		// Reset encoder value
// 		armMotor.tare_position();

// 		int target = 0;

// 		// PID variables decloration and initialization
// 		float kP = 0.3;
// 		float kI = 0.00001;
// 		float kD = 0.1;

// 		// Proportion variable decloration
// 		float proportion;
// 		float intergral;
// 		int intergralRaw;
// 		int derivative;

// 		// Error variable decloration
// 		int error;
// 		int lastError;

// 		// Variable so the robot know when it should use intergral
// 		const float intergralActiveZone = 10;

// 		// Variable to limit the value of intergßral
// 		int intergralPowerLimit = 50 / kI;

// 		int maxPower = 0;

// 		// Final output power/speed
// 		int finalPower;

// 		while(true) {
// 			if(armPIDPtr->armPIDRunning) {
// 				target = armPIDPtr->inTarget;
// 				maxPower = armPIDPtr->powerLimit;

// 				// Calculate how far the robot is from the target
// 				error = target - armMotor.get_position();

// 				// Calculate the proportion
// 				proportion = kP * error;

// 				// Check if intergral should be used
// 				if(abs(error) < intergralActiveZone && error != 0) {
// 					intergralRaw += error;
// 				} else {
// 					intergralRaw = 0;
// 				}

// 				// Limit the raw intergral
// 				if(intergralRaw > intergralPowerLimit) {
// 					intergralRaw = intergralPowerLimit;
// 				} else if(intergralRaw < -intergralPowerLimit) {
// 					intergralRaw = -intergralPowerLimit;
// 				}

// 				// Scale intergral
// 				intergral = kI * intergralRaw;

// 				// Calculate derivative
// 				derivative = kD * (error - lastError);
				
// 				// Update last error
// 				lastError = error;

// 				// Set derivative to 0 if at target
// 				if(error == 0) {
// 					derivative = 0;
// 				}

// 				// Calculate the final power to send to the motors
// 				finalPower = proportion + intergral + derivative;

// 				// Limit final power
// 				if(finalPower > maxPower) {
// 					finalPower = maxPower;
// 				} else if(finalPower < -maxPower) {
// 					finalPower = -maxPower;
// 				}

// 				// Set the motors to the final power
// 				armMotor.move(finalPower);
// 			}

// 			// Delay code to stop CPU hoggin
// 			delay(20);
// 		}
// 	}

// 	#ifdef __cplusplus
// 		extern "C" {
// 	#endif
// 		void autonomous(void);
// 		void initialize(void);
// 		void disabled(void);
// 		void competition_initialize(void);
// 		void opcontrol(void);
// 	#ifdef __cplusplus
// 		}
// 	#endif

// 		#ifdef __cplusplus
// 		// Import IOStream Library
// 		#include <iostream>

// 		// Call IOStream namespace
// 		using namespace std;

// 		#endif
// #endif  // _PROS_MAIN_H_