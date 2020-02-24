// Include header files
#include "api.h"

// Namespaces
using namespace pros;
using namespace pros::literals;
using namespace std;

class IntakeClass {
    public:
        Motor leftIntake;
        Motor rightIntake;
        
        IntakeClass();

        void update(int manual, int speed = 127);
};