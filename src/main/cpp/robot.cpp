//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                These functions are called by main.cpp                    //
//                           Make changes here                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
#include "../include/robot.hpp"

RobotClass::RobotClass() :
    master(E_CONTROLLER_MASTER),
    partner(E_CONTROLLER_PARTNER)
{
    Drivetrain = new DrivetrainClass();
    Intake = new IntakeClass();
    Tray = new TrayClass();
    Arm = new ArmClass();
}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::initialize() {
    // Reset encoder values
    Tray->trayMotor.tare_position();
    Arm->armMotor.tare_position();
}

//////////////////////////////////////////////////////////////////////////////
//                                 Disabled                                 //
//               Only runs when the robot is in disabled mode               //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::disabled() {}

//////////////////////////////////////////////////////////////////////////////
//                         Competition-Initialize                           //
//           Only runs when plugged into a comp/field controller            //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::competition_initialize() {}

//////////////////////////////////////////////////////////////////////////////
//                                Autonomous                                //
//              Only runs when the robot is in autonomous mode              //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::autonomous() {
    cout << "Staring auton" << endl;

    // Start PIDs
    Arm->PIDRunning = true;
    Tray->PIDRunning = true;

    // Expand robot
    Tray->powerLimit = 127;
    Tray->target = -5000;
    delay(500);
    Arm->target = 800;
    delay(550);
    Arm->target = 190;
    Intake->update(-1, 127);
    delay(550);
    Tray->target = 0;
    delay(250);

    // Intake first stack of cubes
    Intake->update(1);
    Drivetrain->PID(48, 2750, 127);
    delay(250);

    // Straighten the robot
    Drivetrain->turnPID(-6, 2750, 127);

    // Line up with the second stack of cubes
    Drivetrain->PID(-33, 2750, 100);
    Drivetrain->turnPID(-75 * isMirrored, 2750, 127);
    Drivetrain->PID(-22, 2750, 127);
    Drivetrain->turnPID(50 * isMirrored, 2750, 127);
    Drivetrain->driveTrainRight(-100);
    delay(350);
    Drivetrain->driveTrainRight(0);
    Drivetrain->driveTrainLeft(-100);
    delay(350);
    Drivetrain->driveTrainLeft(0);

    // Get second stack of cubes
    Drivetrain->PID(43, 3000, 127);
    
    // Slow down intake so cubes do not twist
    Intake->update(1, 60);

    // Align with goal area
    Drivetrain->PID(-23, 3000, 127);
    Drivetrain->turnPID(120 * isMirrored, 2750, 127);

    // Score cubes in goal area
    Tray->target = -2750;
    Drivetrain->PID(13, 3000, 100);
    Intake->update(-1, 127);
    delay(250);
    Intake->update(0);
    Tray->powerLimit = 100;
    Tray->target = -6850;
    Intake->update(1, 80);
    delay(450);
    Intake->update(0);
    delay(1500);
    Intake->update(-1, 50);
    delay(100);
    Drivetrain->PID(-8, 3000, 127);
    Tray->target = 0;

    cout << "Auto end" << endl;
}

//////////////////////////////////////////////////////////////////////////////
//                             Operator Control                             //
//               Only runs when the robot is in opcontrol mode              //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::opcontrol() {
    // Send 'leftVal' and 'rightVal' to the drivetrain motors
    Drivetrain->update(leftVal = (threshold > abs(master.get_analog(ANALOG_LEFT_Y))) ? 0 : master.get_analog(ANALOG_LEFT_Y), 
    rightVal = (threshold > abs(master.get_analog(ANALOG_RIGHT_Y))) ? 0 : master.get_analog(ANALOG_RIGHT_Y));

    // Send inputs to intake
    Intake->update(master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2));

    // Send inputs to tray
    if(master.get_digital(DIGITAL_R1) && Tray->trayMotor.get_position() < 15) {
        Tray->update(master.get_digital(DIGITAL_R2));
    } else {
        Tray->update(master.get_digital(DIGITAL_R2) - master.get_digital(DIGITAL_R1));

    }

    // Send inputs to arm
    if(master.get_digital(DIGITAL_Y) && Arm->armMotor.get_position() < 230) {
        Arm->update(master.get_digital(DIGITAL_X));
    } else {
        Arm->update(master.get_digital(DIGITAL_X) - master.get_digital(DIGITAL_Y));
    }
}