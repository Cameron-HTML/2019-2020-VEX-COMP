// Include header files
#include "api.h"
#include "../../../libraries/pros/apix.h"

#include "../include/drivetrain.hpp"

// Namespaces
using namespace pros;

class Robot {
    public:

        Robot();
        void autonomous();
		void initialize();
		void disabled();
		void competition_initialize();
		void opcontrol();

    private:
        int threshold;
        int leftVal;
        int rightVal;
        int autoSelection;
};