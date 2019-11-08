#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

// Include header files
#include "api.h"
#include "../../../libraries/pros/apix.h"

#include "../include/drivetrain.hpp"
#include "../include/tray.hpp"
#include "../include/arm.hpp"
#include "../include/intake.hpp"

// Namespaces
using namespace pros;
using namespace pros::literals;

class RobotClass {
     private:
        // Init controllers
        Controller master;
        Controller partner;

        // Init variables
        int threshold = 15;
        // -1 for mirror || 1 for normal
        int isMirrored = 1;
        int leftVal = 0;
        int rightVal = 0;
    public:
        // Init pointers
        DrivetrainClass* Drivetrain;
        IntakeClass* Intake;
        TrayClass* Tray;
        ArmClass* Arm;

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