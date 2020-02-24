// Include drivetrain header file
#include "../include/drivetrain.hpp"
#include "../include/defines.h"

DrivetrainClass::DrivetrainClass() :
    frontLeftMotor(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS),
    backLeftMotor(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS),
    frontRightMotor(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS),
    backRightMotor(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS),

    inertialSensor(6),

    leftEncoder(7, 8),
    rightEncoder(5, 6)
{

}

void DrivetrainClass::hardReset() {
    inertialSensor.reset();
    leftEncoder.reset();
    rightEncoder.reset();
}

float DrivetrainClass::getHeading() {
    return inertialSensor.get_heading() - .7;
}

void DrivetrainClass::update(int leftVal, int rightVal) {
    frontLeftMotor.move(leftVal);
    backLeftMotor.move(leftVal);
    frontRightMotor.move(rightVal);
    backRightMotor.move(rightVal);
}

void DrivetrainClass::driveTrainLeft(int speed) {
    frontLeftMotor.move(speed);
    backLeftMotor.move(speed);
}

void DrivetrainClass::driveTrainRight(int speed) {
    frontRightMotor.move(speed);
    backRightMotor.move(speed);
}

void DrivetrainClass::driveTrainTurn(int speed) {
    frontLeftMotor.move(speed);
    backLeftMotor.move(speed);
    frontRightMotor.move(-speed);
    backRightMotor.move(-speed);
}

// Function that converts inches to ticks
float DrivetrainClass::inchToTicks(float inch) {
    // Convert the inches to ticks
    float ticks = inch * wheelCircum - 50;

    // Return ticks
    return ticks;
}

int DrivetrainClass::timerValue(float seconds) {
    // Convert seconds to milliseconds
    int milliSeconds = seconds * 1000;

    if(milliSeconds < 250) {
        milliSeconds = 250;
    }

    return milliSeconds;
}


// Function for the PID control
void DrivetrainClass::PID(float target, float heading, float waitTime, int maxPower = 110) {
    cout << "PID Start" << endl;

    frontLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    backLeftMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    frontRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    backRightMotor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

    // Reset encoder values
    leftEncoder.reset();
    rightEncoder.reset();

    // PID variables decloration and initialization
    float kP = 0.3208;
    float kI = 0.0;
    float kD = 0.0;
    float angleKP = 1;

    // Variable for the raw intergral value
    float intergralRaw = 0;

    // Variable so the robot know when it should use intergral
    float intergralActiveZone = inchToTicks(10);

    // Variable to limit the value of intergral
    float intergralPowerLimit = 50 / kI;

    float lastError = 0;

    // Final output power/speed
    int finalPower;

    // Variable to let the PID know when to start the timer
    bool startTime = false;

    // Variable to log the time when the timer starts
    int currentTime = 0;

    // Convert our waitTimer to milliseconds
    timerValue(waitTime);

    while(currentTime < waitTime) {
        // Calculate how far the robot is from the target
        float error = inchToTicks(target) - ((leftEncoder.get_value() + rightEncoder.get_value()) / 2);

        std::cout << error << std::endl;

        // Calculate the proportion
        float proportion = kP * error;

        // Check if intergral should be used
        if(abs(error) < intergralActiveZone && error != 0) {
            intergralRaw += error;
        } else {
            intergralRaw = 0;
        }

        // Limit the raw intergral
        if(intergralRaw > intergralPowerLimit) {
            intergralRaw = intergralPowerLimit;
        } else if(intergralRaw < -intergralPowerLimit) {
            intergralRaw = -intergralPowerLimit;
        }

        // Scale intergral
        float intergral = kI * intergralRaw;

        // Calculate derivative
        float derivative = kD * (error - lastError);
        
        // Update last error
        float lastError = error;

        // Set derivative to 0 if at target
        if(error == 0) {
            derivative = 0;
        }

        // Calculate the final power to send to the motors
        finalPower = proportion + intergral + derivative;

        // Limit final power
        if(finalPower > maxPower) {
            finalPower = maxPower;
        } else if(finalPower < -maxPower) {
            finalPower = -maxPower;
        }

        float angleError = heading + getHeading();

        float angleProportion = angleKP * angleError;

        // std::cout << angleError << std::endl;
        // std::cout << getHeading() << std::endl;

        // Set the motors to the final power
        driveTrainLeft(finalPower - angleProportion);
        driveTrainRight(finalPower + angleProportion);

        // Start the timer
        if(abs(error) < 25) {
            startTime = true;
        }

        // Set timer values
        if(startTime) {
            currentTime = millis();
            if(currentTime == 0) waitTime += currentTime;
        }

        // Delay code to stop CPU hoggin
        delay(20);
    }
    cout << "PID End" << endl;
    driveTrainLeft(0);
    driveTrainRight(0);
}

// Function for the Turn PID control
void DrivetrainClass::turnPID(float target, float waitTime, int maxPower = 90) {
    cout << "PID start" << endl;

    // PID variables decloration and initialization
    float kP = 0.2;
    float kI = 0.05;
    float kD = 0.5;

    // Variable for the raw intergral value
    float intergralRaw = 0;

    // Variable so the robot know when it should use intergral
    float intergralActiveZone = inchToTicks(2);

    // Variable to limit the value of intergral
    float intergralPowerLimit = 50 / kI;

    // Variable to track last error
    float lastError = 0;

    // Final output power/speed
    int finalPower = 0;

    // Variable to let the PID know when to start the timer
    bool startTime = false;

    // Variable to log the time when the timer starts
    int currentTime = 0;

    // Convert our waitTimer to milliseconds
    timerValue(waitTime);

    while(currentTime < waitTime) {
        // Calculate how far the robot is from the target
        float error = target - inertialSensor.get_heading();

        // Calculate the proportion
        float proportion = kP * error;

        // Check if intergral should be used
        if(abs(error) < intergralActiveZone && error != 0) {
            intergralRaw += error;
        } else {
            intergralRaw = 0;
        }

        // Limit the raw intergral
        if(intergralRaw > intergralPowerLimit) {
            intergralRaw = intergralPowerLimit;
        } else if(intergralRaw < -intergralPowerLimit) {
            intergralRaw = -intergralPowerLimit;
        }

        // Scale intergral
        float intergral = kI * intergralRaw;

        // Calculate derivative
        float derivative = kD * (error - lastError);
        
        // Update last error
        lastError = error;

        // Set derivative to 0 if at target
        if(error == 0) {
            derivative = 0;
        }

        // Calculate the final power to send to the motors
        finalPower = proportion + intergral + derivative;

        // Limit final power
        if(finalPower > maxPower) {
            finalPower = maxPower;
        } else if(finalPower < -maxPower) {
            finalPower = -maxPower;
        }

        // Set motors to final power
        driveTrainTurn(finalPower);

        // Start the timer
        if(abs(error) < 25) {
            startTime = true;
        }

        // Set timer values
        if(startTime) {
            currentTime = millis();
            if(currentTime == 0) waitTime += currentTime;
        }

        // Delay code to stop CPU hoggin
        delay(20);
    }
    driveTrainTurn(0);
}