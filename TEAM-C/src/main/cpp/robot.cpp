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
    Drivetrain->hardReset();
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
    Drivetrain->PID(10, 0, 10000, 127);
}

//////////////////////////////////////////////////////////////////////////////
//                             Operator Control                             //
//               Only runs when the robot is in opcontrol mode              //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::opcontrol() {

    // Send 'leftVal' and 'rightVal' to the drivetrain motors
    Drivetrain->update(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));

    // Send inputs to intake
    Intake->update(master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2));

    // Send inputs to tray
    if(master.get_digital(DIGITAL_L1) && Tray->trayMotor.get_position() < 15) {
        Tray->update(master.get_digital(DIGITAL_L2));
    } else {
        Tray->update(master.get_digital(DIGITAL_L2) - master.get_digital(DIGITAL_L1));

    }

    // Send inputs to arm
    if(master.get_digital(DIGITAL_DOWN) && Arm->armMotor.get_position() < 100) {
        Arm->update(master.get_digital(DIGITAL_B));
    } else {
        Arm->update(master.get_digital(DIGITAL_B) - master.get_digital(DIGITAL_DOWN));
    }
}