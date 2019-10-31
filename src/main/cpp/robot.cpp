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
    Tray = new TrayClass();
}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::initialize() {
    // Reset encoder value
    Tray->trayMotor.tare_position();
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
void RobotClass::autonomous() {}

//////////////////////////////////////////////////////////////////////////////
//                             Operator Control                             //
//               Only runs when the robot is in opcontrol mode              //
//////////////////////////////////////////////////////////////////////////////
void RobotClass::opcontrol() {
    // Send 'leftVal' and 'rightVal' to the drivetrain motors
    Drivetrain->update(leftVal = (threshold > master.get_analog(ANALOG_LEFT_Y)) ? 0 : master.get_analog(ANALOG_LEFT_Y), 
    rightVal = (threshold > master.get_analog(ANALOG_RIGHT_Y)) ? 0 : master.get_analog(ANALOG_RIGHT_Y));

    // Send inputs to tray
    Tray->update((master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2)), master.get_digital(DIGITAL_B));
    // Wait for the user to let go of button
    while(master.get_digital(DIGITAL_R1) || master.get_digital(DIGITAL_R2) || master.get_digital(DIGITAL_B)) delay(10);
}