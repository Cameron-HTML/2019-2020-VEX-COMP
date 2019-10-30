// // Include main hea
// #include "../include/main.hpp"

// _trayPIDArg* trayPIDPtr = new _trayPIDArg();
// _armPIDArg* armPIDPtr = new _armPIDArg();

// // Function for the Turn PID control
// void driveTrainTurnPID(float target, float waitTime, int maxPower = 90) {
//     // Reset encoder values
//     frontLeftMotor.tare_position();
//     backLeftMotor.tare_position();
//     frontRightMotor.tare_position();
//     backRightMotor.tare_position();

//     // PID variables decloration and initialization
//     float kP = 0.2;
//     float kI = 0.05;
//     float kD = 0.5;

//     // Proportion variable decloration
//     float proportion;
//     float intergral;
//     int intergralRaw;
//     int derivative;

//     // Error variable decloration
//     int error;
//     int lastError;

//     // Variable so the robot know when it should use intergral
//     const float intergralActiveZone = inchToTicks(2);

//     // Variable to limit the value of intergral
//     int intergralPowerLimit = 50 / kI;

//     // Final output power/speed
//     int finalPower;

//     // Variable to let the PID know when to start the timer
//     bool startTime = false;

//     // Variable to log the time when the timer starts
//     int currentTime = 0;

//     // Convert our waitTimer to milliseconds
//     timerValue(waitTime);

//     while(currentTime < waitTime) {
//         // Calculate how far the robot is from the target
//         error = degreesToTicks(target) - ((frontLeftMotor.get_position() + backLeftMotor.tare_position()) - (frontRightMotor.get_position() + backRightMotor.tare_position()));

//         // Calculate the proportion
//         proportion = kP * error;

//         // Check if intergral should be used
//         if(abs(error) < intergralActiveZone && error != 0) {
//             intergralRaw += error;
//         } else {
//             intergralRaw = 0;
//         }

//         // Limit the raw intergral
//         if(intergralRaw > intergralPowerLimit) {
//             intergralRaw = intergralPowerLimit;
//         } else if(intergralRaw < -intergralPowerLimit) {
//             intergralRaw = -intergralPowerLimit;
//         }

//         // Scale intergral
//         intergral = kI * intergralRaw;

//         // Calculate derivative
//         derivative = kD * (error - lastError);
        
//         // Update last error
//         lastError = error;

//         // Set derivative to 0 if at target
//         if(error == 0) {
//             derivative = 0;
//         }

//         // Calculate the final power to send to the motors
//         finalPower = proportion + intergral + derivative;

//         // Limit final power
//         if(finalPower > maxPower) {
//             finalPower = maxPower;
//         } else if(finalPower < -maxPower) {
//             finalPower = -maxPower;
//         }

//         // Set motors to final power
//         driveTrainTurn(finalPower);

        
//         // Start the timer
//         if(error < 2) {
//             startTime = true;
//         }

//         // Set timer values
//         if(startTime && currentTime == 0) {
//             currentTime = millis();
//             waitTime += currentTime;
//         }

//         // Delay code to stop CPU hoggin
//         delay(20);
//     }
//     driveTrainTurn(0);
// }

// void intake(int lSpeed, int rSpeed) {
//     leftIntake.move(lSpeed);
//     rightIntake.move(rSpeed);
// }

// // Callback event for auto selection
// static lv_res_t buttonPressEvent(struct _lv_obj_t * obj) {
//     lv_btn_toggle(obj);
// }

// /**
//  * Runs initialization code. This occurs as soon as the program is started.
//  *
//  * All other competition modes are blocked by initialize; it is recommended
//  * to keep execution time for this mode under a few seconds.
//  */
// void initialize() {
//     Task armTask(armPID, armPIDPtr, "ArmPIDTask");
//     Task trayTask(trayPID, trayPIDPtr, "TrayPIDTask");

//     static lv_style_t autoFieldStyle;
//     lv_style_copy(&autoFieldStyle, &lv_style_plain_color);
//     autoFieldStyle.body.main_color = LV_COLOR_GRAY;
//     autoFieldStyle.body.grad_color = LV_COLOR_GRAY;

//     lv_obj_t * autoField;
//     autoField = lv_obj_create(lv_scr_act(), NULL);
//     lv_obj_set_size(autoField, 250, 250);
//     lv_obj_set_style(autoField, &autoFieldStyle);
//     lv_obj_align(autoField, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

//     static lv_style_t redButtonStyle;
//     lv_style_copy(&redButtonStyle, &lv_style_plain_color);
//     redButtonStyle.body.main_color = LV_COLOR_RED;
//     redButtonStyle.body.grad_color = LV_COLOR_RED;
//     redButtonStyle.body.border.color = LV_COLOR_WHITE;
//     redButtonStyle.body.border.width = 1;

//     static lv_style_t redButtonStyleTGL;
//     lv_style_copy(&redButtonStyleTGL, &lv_style_plain_color);
//     redButtonStyleTGL.body.main_color = LV_COLOR_MAKE(245, 87, 76);
//     redButtonStyleTGL.body.grad_color = LV_COLOR_MAKE(245, 87, 76);
//     redButtonStyleTGL.body.border.color = LV_COLOR_WHITE;
//     redButtonStyleTGL.body.border.width = 1;

//     lv_obj_t * redRightButton;
//     redRightButton = lv_btn_create(lv_scr_act(), NULL);
//     lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_PR, &redButtonStyle);
//     lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_REL, &redButtonStyleTGL);
//     lv_btn_set_style(redRightButton, LV_BTN_STYLE_REL, &redButtonStyle);
//     lv_btn_set_style(redRightButton, LV_BTN_STYLE_PR, &redButtonStyle);
//     lv_btn_set_style(redRightButton, LV_BTN_STYLE_INA, &redButtonStyle);
//     lv_obj_set_size(redRightButton, 140, 50);
//     lv_obj_align(redRightButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, -80);
//     lv_btn_set_action(redRightButton, LV_BTN_ACTION_PR, buttonPressEvent);

//     static lv_style_t blueRightBoxStyle;
//     lv_style_copy(&blueRightBoxStyle, &lv_style_plain_color);
//     blueRightBoxStyle.body.main_color = LV_COLOR_BLUE;
//     blueRightBoxStyle.body.grad_color = LV_COLOR_BLUE;
//     blueRightBoxStyle.body.border.color = LV_COLOR_WHITE;
//     blueRightBoxStyle.body.border.width = 1;

//     lv_obj_t * blueRightBox;
//     blueRightBox = lv_obj_create(lv_scr_act(), NULL);
//     lv_obj_set_size(blueRightBox, 140, 50);
//     lv_obj_set_style(blueRightBox, &blueRightBoxStyle);
//     lv_obj_align(blueRightBox, NULL, LV_ALIGN_IN_LEFT_MID, 10, 26);

//     static lv_style_t blueLeftBoxStyle;
//     lv_style_copy(&blueLeftBoxStyle, &lv_style_plain_color);
//     blueLeftBoxStyle.body.main_color = LV_COLOR_BLUE;
//     blueLeftBoxStyle.body.grad_color = LV_COLOR_BLUE;
//     blueLeftBoxStyle.body.border.color = LV_COLOR_WHITE;
//     blueLeftBoxStyle.body.border.width = 1;

//     lv_obj_t * blueLeftBox;
//     blueLeftBox = lv_obj_create(lv_scr_act(), NULL);
//     lv_obj_set_size(blueLeftBox, 140, 50);
//     lv_obj_set_style(blueLeftBox, &blueLeftBoxStyle);
//     lv_obj_align(blueLeftBox, NULL, LV_ALIGN_IN_LEFT_MID, 10, 79);
// }

// /**
//  * Runs while the robot is in the disabled state of Field Management System or
//  * the VEX Competition Switch, following either autonomous or opcontrol. When
//  * the robot is enabled, this task will exit.
//  */
// void disabled() {}

// /**
//  * Runs after initialize(), and before autonomous when connected to the Field
//  * Management System or the VEX Competition Switch. This is intended for
//  * competition-specific initialization routines, such as an autonomous selector
//  * on the LCD.
//  *
//  * This task will exit when the robot is enabled and autonomous or opcontrol
//  * starts.
//  */
// void competition_initialize() {}

// /**
//  * Runs the user autonomous code. This function will be started in its own task
//  * with the default priority and stack size whenever the robot is enabled via
//  * the Field Management System or the VEX Competition Switch in the autonomous
//  * mode. Alternatively, this function may be called in initialize or opcontrol
//  * for non-competition testing purposes.
//  *
//  * If the robot is disabled or communications is lost, the autonomous task
//  * will be stopped. Re-enabling the robot will restart the task, not re-start it
//  * from where it left off.
//  */
// void autonomous() {
//     cout << "Staring auton" << endl;
//     frontLeftMotor.tare_position();
//     frontRightMotor.tare_position();
//     armMotor.tare_position();
//     trayMotor.tare_position();

//     armPIDPtr->armPIDRunning = true;
//     armPIDPtr->inTarget = 800;
//     delay(1000);
//     armPIDPtr->inTarget = 300;
//     intake(127, 127);
//     driveTrainPID(46, 3000, 90);
//     delay(500);
//     driveTrainPID(-23, 3000, 127);

//     // while(true) {
//     //     if((frontLeftMotor.get_position() + frontRightMotor.get_position()) / 2 < 220) {
//     //         driveTrainTurn(90);
//     //     } else {
//     //         driveTrainTurn(-5);
//     //     }
//     // }
// }

// /**
//  * Runs the operator control code. This function will be started in its own task
//  * with the default priority and stack size whenever the robot is enabled via
//  * the Field Management System or the VEX Competition Switch in the operator
//  * control mode.
//  *
//  * If no competition control is connected, this function will run immediately
//  * following initialize().
//  *
//  * If the robot is disabled or communications is lost, the
//  * operator control task will be stopped. Re-enabling the robot will restart the
//  * task, not resume it from where it left off.
//  */
// void opcontrol() {
//     Controller master(E_CONTROLLER_MASTER);
	
// 	trayMotor.tare_position();
// 	armMotor.tare_position();


// 	// Variable decloration and initialization
// 	int threshold = 15;

// 	while (true) {
// 		// Control for the left side of the drive trainß
// 		if(abs(master.get_analog(ANALOG_LEFT_Y)) >= threshold) {
// 			frontLeftMotor.move(master.get_analog(ANALOG_LEFT_Y));
// 			backLeftMotor.move(master.get_analog(ANALOG_LEFT_Y));
// 		} else {
// 			frontLeftMotor.move(0);	
// 			backLeftMotor.move(0);
// 		}

// 		// Control for the right side of the drive train
// 		if(abs(master.get_analog(ANALOG_RIGHT_Y)) >= threshold) {
// 			frontRightMotor.move(master.get_analog(ANALOG_RIGHT_Y));
// 			backRightMotor.move(master.get_analog(ANALOG_RIGHT_Y));
// 		} else {
// 			frontRightMotor.move(0);
// 			backRightMotor.move(0);
// 		}

// 		// Tray auto place macro
// 		if(master.get_digital(DIGITAL_A)) {
// 			while(master.get_digital(DIGITAL_A)) delay(20);

// 			if(trayPIDPtr->trayPIDRunning) {
// 				trayPIDPtr->trayPIDRunning = false;
// 			} else {
// 				trayPIDPtr->trayPIDRunning = true;
// 			}
// 		}

// 		if(master.get_digital(DIGITAL_B)) {
// 			while(master.get_digital(DIGITAL_B)) delay(20);

// 			trayPIDPtr->trayPIDRunning = true;

// 			if(trayPIDPtr->inTarget <= 10) {
// 				trayPIDPtr->inTarget = 4000;
// 				trayPIDPtr->powerLimit = 70;
// 			} else if(trayPIDPtr->inTarget >= 1600) {
// 				trayPIDPtr->inTarget = 10;
// 				trayPIDPtr->powerLimit = 80;
// 			}
// 		}

// 		// Tray manual control
// 		if(master.get_digital(DIGITAL_R1) == 1) {
// 			trayPIDPtr->trayPIDRunning = false;
// 			trayMotor.move(80);
// 			trayPIDPtr->inTarget = trayMotor.get_position();
// 		} else if(master.get_digital(DIGITAL_R2) == 1) {
// 			trayPIDPtr->trayPIDRunning = false;
// 			trayMotor.move(-90);
// 			trayPIDPtr->inTarget = trayMotor.get_position();
// 		} else {
// 			if(trayPIDPtr->powerLimit == 80 && trayMotor.get_position() <= 20) {
// 				trayPIDPtr->trayPIDRunning = false;
// 				trayMotor.move(0);
// 			} else {
// 				if(!trayPIDPtr->trayPIDRunning) {
// 					trayPIDPtr->trayPIDRunning = true;
// 				}
// 			}
// 		}

// 		// Arm control
// 		if(master.get_digital(DIGITAL_X) == 1) {
// 			armPIDPtr->armPIDRunning = false;
// 			armMotor.move(100);
// 			armPIDPtr->inTarget = armMotor.get_position();
// 		} else if(master.get_digital(DIGITAL_Y) == 1 && armMotor.get_position() != 50) {
// 			armPIDPtr->armPIDRunning = false;
// 			armMotor.move(-100);
// 			armPIDPtr->inTarget = armMotor.get_position();
// 		} else {
// 			if(armMotor.get_position() >= 60) {
// 				armPIDPtr->armPIDRunning = true;
// 			} else {
// 				armPIDPtr->armPIDRunning = false;
// 				armMotor.move(0);
// 			}
// 		}

// 		// Intake control
// 		if(master.get_digital(DIGITAL_L1) == 1) {
// 			if(trayPIDPtr->inTarget != 4000) {
// 				leftIntake.move(127);
// 				rightIntake.move(127);
// 			} else {
// 				leftIntake.move(50);
// 				rightIntake.move(50);
// 			}
// 		} else if(master.get_digital(DIGITAL_L2) == 1) {
// 			if(trayPIDPtr->inTarget != 4000) {
// 				leftIntake.move(-127);
// 				rightIntake.move(-127);
// 			} else {
// 				leftIntake.move(50);
// 				rightIntake.move(50);
// 			}
// 		} else {
// 			leftIntake.move(0);
// 			rightIntake.move(0);
// 		}

// 		// Delay task to stop CPU hogging
// 		delay(20);
// 	}
// }