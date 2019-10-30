#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

// Include header files
#include "api.h"
#include "../../../libraries/pros/apix.h"

#include "../include/drivetrain.hpp"

// Namespaces
using namespace pros;
using namespace pros::literals;

class RobotClass {
     private:
        // Init controllers
        Controller master;
        Controller partner;

        // Init variables
        int threshold;
        int leftVal;
        int rightVal;
    public:
        // Init pointer
        DrivetrainClass* Drivetrain;

        RobotClass();
        static RobotClass* Get() {return TheRobot;}

        void autonomous();
		void initialize();
		void disabled();
		void competition_initialize();
		void opcontrol();
    protected:
        static RobotClass* TheRobot;
};