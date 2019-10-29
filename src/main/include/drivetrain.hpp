// Include header files
#include "api.h"
#include "../../../libraries/pros/apix.h"

// Namespaces
using namespace pros;
using namespace pros::literals;

class DrivetrainClass {
    Motor frontLeftMotor;
    Motor backLeftMotor;
    Motor frontRightMotor;
    Motor backRightMotor;

    public:
        void update(int leftVal, int rightVal);
};