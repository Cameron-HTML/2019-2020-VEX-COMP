// Include header files
#include "api.h"

// Namespaces
using namespace pros;
using namespace pros::literals;
using namespace std;

class TrayClass {
    public:
        Motor trayMotor;

        int target = 0;

        // PID variables
        float kP = 0.3;
        float kI = 0.00001;
        float kD = 0.1;

        // Proportion variables
        float proportion = 0.0;
        float intergral = 0.0;
        int intergralRaw = 0;
        int derivative = 0;

        // Error variables
        int error = 0;
        int lastError = 0;

        // Variable so the robot knows when it should use intergral
        const float intergralActiveZone = 10;

        // Variable to limit the value of intergral
        int intergralPowerLimit = 50 / kI;

        // Variable to limit power
        int powerLimit = 80;

        // Final output power/speed
        int finalPower = 0;

        int PIDRunning = false;

        TrayClass();

        void update(int manual);
        void PID();
};