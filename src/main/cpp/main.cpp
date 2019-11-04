//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//               This file is requried for the code to run.                 //
//         Refer to 'robot.cpp' to make changes to these functions          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
#include "../include/main.hpp"

MainClass::MainClass() {
    Robot = new RobotClass();
}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void initialize() {
    Main.Robot->initialize();
}

//////////////////////////////////////////////////////////////////////////////
//                                 Disabled                                 //
//               Only runs when the robot is in disabled mode               //
//////////////////////////////////////////////////////////////////////////////
void disabled() {
    Main.Robot->disabled();
}

//////////////////////////////////////////////////////////////////////////////
//                         Competition-Initialize                           //
//           Only runs when plugged into a comp/field controller            //
//////////////////////////////////////////////////////////////////////////////
void competition_initialize() {
    Main.Robot->competition_initialize();
}

//////////////////////////////////////////////////////////////////////////////
//                                Autonomous                                //
//              Only runs when the robot is in autonomous mode              //
//////////////////////////////////////////////////////////////////////////////
void autonomous() {
    cout << "Starting autonomous!" << endl;
     Main.Robot->autonomous();
}

//////////////////////////////////////////////////////////////////////////////
//                             Operator Control                             //
//               Only runs when the robot is in opcontrol mode              //
//////////////////////////////////////////////////////////////////////////////
void opcontrol() {
    cout << "Starting operator control!" << endl;
    while(true) {
        Main.Robot->opcontrol();

        delay(20);
    }
}