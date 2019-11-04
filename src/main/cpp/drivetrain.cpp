// Include drivetrain header file
#include "../include/drivetrain.hpp"

DrivetrainClass::DrivetrainClass() :
    frontLeftMotor(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS),
    backLeftMotor(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS),
    frontRightMotor(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS),
    backRightMotor(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS)
{

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
int DrivetrainClass::inchToTicks(float inch) {
    // Convert the inches to ticks
    ticks = inch * 176.384125 - 200;

    // Return ticks
    return ticks;
}

int DrivetrainClass::timerValue(float seconds) {
    // Convert seconds to milliseconds
    milliSeconds = seconds * 1000;

    if(milliSeconds < 250) {
        milliSeconds = 250;
    }

    return milliSeconds;
}

// Function that converts degrees to ticks
int DrivetrainClass::degreesToTicks(float degrees) {
    // Calculate ticks
    ticks = degrees * ticksPerTurn / 360;

    return ticks;
}

// Function for the PID control
void DrivetrainClass::PID(float target, float waitTime, int maxPower = 110) {
    cout << "PID Start" << endl;
    // Reset encoder values
    frontLeftMotor.tare_position();
    backLeftMotor.tare_position();
    frontRightMotor.tare_position();
    backRightMotor.tare_position();

    // Convert our waitTimer to milliseconds
    timerValue(waitTime);

    while(currentTime < waitTime) {
        // Calculate how far the robot is from the target
        error = inchToTicks(target) - ((frontLeftMotor.get_position() - backLeftMotor.tare_position()) + (frontRightMotor.get_position() - backRightMotor.tare_position()));

        // Calculate the proportion
        proportion = kP * error;

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
        intergral = kI * intergralRaw;

        // Calculate derivative
        derivative = kD * (error - lastError);
        
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
        
        errorDrift = (frontRightMotor.get_position() + backRightMotor.get_position()) - (frontLeftMotor.get_position() + backLeftMotor.get_position());
        proportionDrift = kP_C * errorDrift;

        // Set the motors to the final power
        driveTrainLeft(finalPower + proportionDrift);
        driveTrainRight(finalPower - proportionDrift);

        // Start the timer
        if(abs(error) < 2) {
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