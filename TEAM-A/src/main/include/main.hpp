#ifndef MAIN_H
    #define MAIN_H
    // Include header files
    #include "api.h"

    #include "../include/robot.hpp"

    class MainClass {
        public:
            // Init pointer
            RobotClass* Robot;

            MainClass();
    } Main;
#endif

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif