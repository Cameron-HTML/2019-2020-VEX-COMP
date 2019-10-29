#include "../include/robot.hpp"

Robot::Robot() :
    DrivetrainClass* Drivetrain
{

}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void initialize() {
    // _trayPIDArg* tray = new _trayPIDArg();
    // _armPIDArg* arm = new _armPIDArg();
}

//////////////////////////////////////////////////////////////////////////////
//                                 Disabled                                 //
//               Only runs when the robot is in disabled mode               //
//////////////////////////////////////////////////////////////////////////////
void disabled() {}

//////////////////////////////////////////////////////////////////////////////
//                         Competition-Initialize                           //
//           Only runs when plugged into a comp/field controller            //
//////////////////////////////////////////////////////////////////////////////
void competition_initialize() {}

//////////////////////////////////////////////////////////////////////////////
//                                Autonomous                                //
//              Only runs when the robot is in autonomous mode              //
//////////////////////////////////////////////////////////////////////////////
void autonomous() {}

//////////////////////////////////////////////////////////////////////////////
//                             Operator Control                             //
//               Only runs when the robot is in opcontrol mode              //
//////////////////////////////////////////////////////////////////////////////
void opcontrol() {
    Controller master(E_CONTROLLER_MASTER);
    Controller partner(E_CONTROLLER_PARTNER);

    int threshold = 15;

	while (true) {
        int leftVal = (threshold > master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) ? 0 : master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        int rightVal = (threshold > master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) ? 0 : master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
        Drivetrain->update(leftVal, rightVal);

		// Delay task to stop CPU hogging
		delay(20);
	}
}