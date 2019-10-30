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
        DrivetrainClass();

        void update(int leftVal, int rightVal);
        void PID(float target, float waitTime, int maxPower);
        void turn(float target, float waitTime, int maxPower);
        void driveTrainLeft(int speed);
        void driveTrainRight(int speed);
        void driveTrainTurn(int speed);
        int inchToTicks(float inch);
        int timerValue(float seconds);
        int degreesToTicks(float degrees);
};