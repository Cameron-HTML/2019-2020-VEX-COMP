#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void driveTrainLeft(int speed) {
    frontLeftMotor.move(speed);
}

void driveTrainRight(int speed) {
    frontRightMotor.move(speed);
}

void driveTrainTurn(int speed) {
    frontLeftMotor.move(speed);
    frontRightMotor.move(-speed);
}

// Function that converts inches to ticks
int inchToTicks(float inch) {
    // Decloration of output variable
    int ticks;

    // Convert the inches to ticks
    ticks = inch * 176.384125 - 500;

    // Return ticks
    return ticks;
}

// Function that converts degrees to ticks
int degreesToTicks(float degrees) {
    // Test 10 times and change value
    int ticksPerTurn = 3000;

    // Calculate ticks
    int ticks = degrees * ticksPerTurn / 360;

    return ticks;
}

int timerValue(float seconds) {
    // Convert seconds to milliseconds
    int milliSeconds = seconds * 1000;

    if(milliSeconds < 250) {
        milliSeconds = 250;
    }

    return milliSeconds;
}

// Function for the PID control
void driveTrainPID(float target, float waitTime, int maxPower = 110) {
    // Reset encoder values
    frontLeftMotor.tare_position();
    frontRightMotor.tare_position();

    // PID variables decloration and initialization
    float kP = 0.3;
    float kI = 0.00001;
    float kD = 0.1;

    // Proportion variable decloration
    float proportion;
    float intergral;
    int intergralRaw;
    int derivative;

    // Error variable decloration
    int error;
    int lastError;

    float kP_C = 1.25;
    int errorDrift;
    float proportionDrift;

    // Variable so the robot know when it should use intergral
    const float intergralActiveZone = inchToTicks(10);

    // Variable to limit the value of intergral
    int intergralPowerLimit = 50 / kI;

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
        error = inchToTicks(target) - (frontLeftMotor.get_position() + frontRightMotor.get_position());

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
        /*
        if(finalPower > maxPower) {
            finalPower = maxPower;
        } else if(finalPower < -maxPower) {
            finalPower = -maxPower;
        }
        */

        errorDrift = frontRightMotor.get_position() - frontLeftMotor.get_position();
        proportionDrift = kP_C * errorDrift;

        // Set the motors to the final power
        driveTrainLeft(finalPower + proportionDrift);
        driveTrainRight(finalPower - proportionDrift);

        // Start the timer
        if(error < 2) {
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
void driveTrainTurnPID(float target, float waitTime, int maxPower = 90) {
    // Reset encoder values
    frontLeftMotor.tare_position();
    frontRightMotor.tare_position();

    // PID variables decloration and initialization
    float kP = 0.2;
    float kI = 0.05;
    float kD = 0.5;

    // Proportion variable decloration
    float proportion;
    float intergral;
    int intergralRaw;
    int derivative;

    // Error variable decloration
    int error;
    int lastError;

    // Variable so the robot know when it should use intergral
    const float intergralActiveZone = inchToTicks(2);

    // Variable to limit the value of intergral
    int intergralPowerLimit = 50 / kI;

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
        error = degreesToTicks(target) - (frontLeftMotor.get_position() - frontRightMotor.get_position());

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

        // Set motors to final power
        driveTrainTurn(finalPower);

        /*
        // Start the timer
        if(error < 30) {
            startTime = true;
        }
        */

        // Set timer values
        if(startTime && currentTime == 0) {
            currentTime = millis();
            waitTime += currentTime;
        }

        // Delay code to stop CPU hoggin
        delay(20);
    }
    driveTrainTurn(0);
}

void autonomous() {
    cout << "Staring auton" << endl;
    frontLeftMotor.tare_position();
    frontRightMotor.tare_position();
    while(true) {
        if((frontLeftMotor.get_position() + frontRightMotor.get_position()) / 2 < 220) {
            driveTrainTurn(90);
        } else {
            driveTrainTurn(-5);
        }
    }
}
