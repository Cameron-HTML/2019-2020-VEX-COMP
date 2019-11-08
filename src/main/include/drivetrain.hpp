// Include header files
#include "api.h"
#include "../../../libraries/pros/apix.h"
#include <IOStream>

// Namespaces
using namespace pros;
using namespace pros::literals;
using namespace std;

class DrivetrainClass {
    private:
        Motor frontLeftMotor;
        Motor backLeftMotor;
        Motor frontRightMotor;
        Motor backRightMotor;
    public:
        // Decloration of output ticks
        int ticks = 0;

        // Decloration of ticks per turn(360)
        int ticksPerTurn = 3000;

        // Decloration of 'milliSeconds' variable
        int milliSeconds = 0;

        // PID variables decloration and initialization
        float kP = 0.3;
        float kI = 0.00001;
        float kD = 0.1;

        // Proportion variable decloration
        float proportion = 0.0;
        float intergral = 0.0;
        int intergralRaw = 0;
        int derivative = 0;

        // Error variable decloration
        int error = 0;
        int lastError = 0;

        float kP_C = 0; //.09
        int errorDrift = 0;
        float proportionDrift = 0.0;

        // Variable so the robot know when it should use intergral
        float intergralActiveZone = 0.0;

        // Variable to limit the value of intergral
        int intergralPowerLimit = 50 / kI;

        // Final output power/speed
        int finalPower = 0;

        // Variable to let the PID know when to start the timer
        bool startTime = false;

        // Variable to log the time when the timer starts
        int currentTime = 0;

        DrivetrainClass();

        void update(int leftVal, int rightVal);
        void PID(float target, float waitTime, int maxPower);
        void turnPID(float target, float waitTime, int maxPower);
        void driveTrainLeft(int speed);
        void driveTrainRight(int speed);
        void driveTrainTurn(int speed);
        int inchToTicks(float inch);
        int timerValue(float seconds);
        int degreesToTicks(float degrees);
};