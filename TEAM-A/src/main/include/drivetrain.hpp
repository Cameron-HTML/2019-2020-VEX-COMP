// Include header files
#include "api.h"

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

        Imu inertialSensor;

        ADIEncoder leftEncoder;
        ADIEncoder rightEncoder; 

        double gyroOffset = 0;
    public:
        DrivetrainClass();

        void update(int leftVal, int rightVal);
        void PID(float target, float heading, float waitTime, int maxPower);
        void turnPID(float target, float waitTime, int maxPower);
        void driveTrainLeft(int speed);
        void driveTrainRight(int speed);
        void driveTrainTurn(int speed);
        void hardReset();

        float getHeading();

        float inchToTicks(float inch);

        int timerValue(float seconds);
};