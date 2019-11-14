#include "main.h"

//////////////////////////////////////////////////////////////////////////////
//                                Variables                                 //
//                           User-made variables                            //
//////////////////////////////////////////////////////////////////////////////

Motor leftIntake(13);
Motor rightIntake(-11);
Motor armMotor(-19);
Motor trayMotor(-3);

auto chassis = ChassisControllerFactory::create({8, 9}, {-1, -4}, AbstractMotor::gearset::green, {4_in, 13.75_in});
auto arm = AsyncControllerFactory::posPID(-19, 0.008, 0.0, 0.0002);
auto tray = AsyncControllerFactory::posPID(-3, 0.005, 0.0, 0.0);

int armHeights[3] = {68, 600, 800};
int trayHeights[3] = {10, 1400, 2550};
int selectedAuto = 0;

lv_obj_t * autoField;
lv_obj_t * redLeftButton;
lv_obj_t * redRightButton;
lv_obj_t * blueLeftButton;
lv_obj_t * blueRightButton;
lv_obj_t * confirmContainer;
lv_obj_t * confirmButton;

static lv_res_t buttonPressEvent(lv_obj_t * btn) {
    lv_btn_set_state(btn, LV_BTN_STATE_TGL_REL);

    if(btn == redLeftButton) {
        lv_btn_set_state(redRightButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(blueLeftButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(blueRightButton, LV_BTN_STATE_TGL_PR);
        lv_obj_align(confirmButton, NULL, LV_ALIGN_IN_LEFT_MID, 155, -80);
        selectedAuto = 1;
    } else if(btn == redRightButton) {
        lv_btn_set_state(redLeftButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(blueLeftButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(blueRightButton, LV_BTN_STATE_TGL_PR);
        lv_obj_align(confirmButton, NULL, LV_ALIGN_IN_LEFT_MID, 155, -27);
        selectedAuto = 2;
    } else if(btn == blueLeftButton) {
        lv_btn_set_state(redRightButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(redLeftButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(blueRightButton, LV_BTN_STATE_TGL_PR);
        lv_obj_align(confirmButton, NULL, LV_ALIGN_IN_LEFT_MID, 155, 26);
        selectedAuto = 3;
    } else if(btn == blueRightButton) {
        lv_btn_set_state(redLeftButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(redRightButton, LV_BTN_STATE_TGL_PR);
        lv_btn_set_state(blueLeftButton, LV_BTN_STATE_TGL_PR);
        lv_obj_align(confirmButton, NULL, LV_ALIGN_IN_LEFT_MID, 155, 80);
        selectedAuto = 4;
    }
}

static lv_res_t confirmSelected(lv_obj_t * btn) {
    cout << selectedAuto << endl;
}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void initialize() {
    leftIntake.setBrakeMode(AbstractMotor::brakeMode::hold);
	rightIntake.setBrakeMode(AbstractMotor::brakeMode::hold);

    // Object styles
    static lv_style_t autoFieldStyle;
    lv_style_copy(&autoFieldStyle, &lv_style_plain_color);
    autoFieldStyle.body.main_color = LV_COLOR_GRAY;
    autoFieldStyle.body.grad_color = LV_COLOR_GRAY;

    static lv_style_t redButtonStyle;
    lv_style_copy(&redButtonStyle, &lv_style_plain_color);
    redButtonStyle.body.main_color = LV_COLOR_RED;
    redButtonStyle.body.grad_color = LV_COLOR_RED;
    redButtonStyle.body.border.color = LV_COLOR_WHITE;
    redButtonStyle.body.border.width = 1;

    static lv_style_t redButtonStyleTGL;
    lv_style_copy(&redButtonStyleTGL, &lv_style_plain_color);
    redButtonStyleTGL.body.main_color = LV_COLOR_MAKE(245, 87, 76);
    redButtonStyleTGL.body.grad_color = LV_COLOR_MAKE(245, 87, 76);
    redButtonStyleTGL.body.border.color = LV_COLOR_WHITE;
    redButtonStyleTGL.body.border.width = 1;

    static lv_style_t blueButtonStyle;
    lv_style_copy(&blueButtonStyle, &lv_style_plain_color);
    blueButtonStyle.body.main_color = LV_COLOR_BLUE;
    blueButtonStyle.body.grad_color = LV_COLOR_BLUE;
    blueButtonStyle.body.border.color = LV_COLOR_WHITE;
    blueButtonStyle.body.border.width = 1;

    static lv_style_t blueButtonStyleTGL;
    lv_style_copy(&blueButtonStyleTGL, &lv_style_plain_color);
    blueButtonStyleTGL.body.main_color = LV_COLOR_MAKE(0, 0, 139);
    blueButtonStyleTGL.body.grad_color = LV_COLOR_MAKE(0, 0, 139);
    blueButtonStyleTGL.body.border.color = LV_COLOR_WHITE;
    blueButtonStyleTGL.body.border.width = 1;

    static lv_style_t buttonContainerStyle;
    lv_style_copy(&buttonContainerStyle, &lv_style_plain_color);
    buttonContainerStyle.body.main_color = LV_COLOR_GRAY;
    buttonContainerStyle.body.grad_color = LV_COLOR_GRAY;
    buttonContainerStyle.body.border.color = LV_COLOR_WHITE;
    buttonContainerStyle.body.border.width = 1;

    static lv_style_t confirmButtonStyle;
    lv_style_copy(&confirmButtonStyle, &lv_style_plain_color);
    confirmButtonStyle.body.main_color = LV_COLOR_MAKE(0, 255, 0);
    confirmButtonStyle.body.grad_color = LV_COLOR_MAKE(0, 255, 0);

    static lv_style_t confirmButtonStyleTGL;
    lv_style_copy(&confirmButtonStyleTGL, &lv_style_plain_color);
    confirmButtonStyleTGL.body.main_color = LV_COLOR_MAKE(50, 205, 50);
    confirmButtonStyleTGL.body.grad_color = LV_COLOR_MAKE(50, 205, 50);

    // Field object
    autoField = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(autoField, 250, 250);
    lv_obj_set_style(autoField, &autoFieldStyle);
    lv_obj_align(autoField, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    // Button objects
    redLeftButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_TGL_PR, &redButtonStyle);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_TGL_REL, &redButtonStyleTGL);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_REL, &redButtonStyle);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_PR, &redButtonStyle);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_INA, &redButtonStyle);
    lv_obj_set_size(redLeftButton, 140, 50);
    lv_obj_align(redLeftButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, -80);
    lv_btn_set_action(redLeftButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    redRightButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_PR, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_REL, &redButtonStyleTGL);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_REL, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_PR, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_INA, &redButtonStyle);
    lv_obj_set_size(redRightButton, 140, 50);
    lv_obj_align(redRightButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, -27);
    lv_btn_set_action(redRightButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    blueLeftButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_TGL_PR, &blueButtonStyle);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_TGL_REL, &blueButtonStyleTGL);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_REL, &blueButtonStyle);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_PR, &blueButtonStyle);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_INA, &blueButtonStyle);
    lv_obj_set_size(blueLeftButton, 140, 50);
    lv_obj_align(blueLeftButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 26);
    lv_btn_set_action(blueLeftButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    blueRightButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_TGL_PR, &blueButtonStyle);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_TGL_REL, &blueButtonStyleTGL);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_REL, &blueButtonStyle);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_PR, &blueButtonStyle);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_INA, &blueButtonStyle);
    lv_obj_set_size(blueRightButton, 140, 50);
    lv_obj_align(blueRightButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 79);
    lv_btn_set_action(blueRightButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    confirmContainer = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(confirmContainer, 50, 209);
    lv_obj_set_style(confirmContainer, &buttonContainerStyle);
    lv_obj_align(confirmContainer, NULL, LV_ALIGN_IN_LEFT_MID, 155, -1);

    confirmButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(confirmButton, LV_BTN_STYLE_TGL_PR, &confirmButtonStyle);
    lv_btn_set_style(confirmButton, LV_BTN_STYLE_TGL_REL, &confirmButtonStyleTGL);
    lv_btn_set_style(confirmButton, LV_BTN_STYLE_REL, &confirmButtonStyle);
    lv_btn_set_style(confirmButton, LV_BTN_STYLE_PR, &confirmButtonStyle);
    lv_btn_set_style(confirmButton, LV_BTN_STYLE_INA, &confirmButtonStyle);
    lv_obj_set_size(confirmButton, 50, 50);
    lv_obj_align(confirmButton, NULL, LV_ALIGN_IN_LEFT_MID, 155, -80);
    lv_btn_set_action(confirmButton, LV_BTN_ACTION_CLICK, confirmSelected);
}

//////////////////////////////////////////////////////////////////////////////
//                                 Disabled                                 //
//               Only runs when the robot is in disabled mode               //
//////////////////////////////////////////////////////////////////////////////
void disabled() {}

//////////////////////////////////////////////////////////////////////////////
//                         Competition-Initialize                           //
//           Only runs when plugged into a comp/field controller            //
//////////////////////////////////////////////////////////////////////////////
void competition_initialize() {}

//////////////////////////////////////////////////////////////////////////////
//                                Autonomous                                //
//              Only runs when the robot is in autonomous mode              //
//////////////////////////////////////////////////////////////////////////////
void autonomous() {
	cout << "Staring auton" << endl;
    
    cout << "Auto end" << endl;
}

// Controller setup
Controller masterController(ControllerId::master);
Controller partnerController(ControllerId::partner);

// Macro tray & arm buttons
ControllerButton btnX(ControllerId::partner, ControllerDigital::X);
ControllerButton btnY(ControllerId::partner, ControllerDigital::Y);
ControllerButton btnB(ControllerId::partner, ControllerDigital::B);
ControllerButton btnA(ControllerId::partner, ControllerDigital::A);
ControllerButton btnR1(ControllerId::master, ControllerDigital::R1);
ControllerButton btnR2(ControllerId::master, ControllerDigital::R2);

// Manual arm buttons
ControllerButton btnUp(ControllerId::partner, ControllerDigital::up);
ControllerButton btnDown(ControllerId::partner, ControllerDigital::down);

ControllerButton btnR1P(ControllerId::partner, ControllerDigital::R1);
ControllerButton btnR2P(ControllerId::partner, ControllerDigital::R2);

ControllerButton btnLeft(ControllerId::partner, ControllerDigital::left);
ControllerButton btnRight(ControllerId::partner, ControllerDigital::right);
ControllerButton btnRightM(ControllerId::master, ControllerDigital::right);

// Intake buttons
ControllerButton btnL1(ControllerId::master, ControllerDigital::L1);
ControllerButton btnL2(ControllerId::master, ControllerDigital::L2);

//////////////////////////////////////////////////////////////////////////////
//                             Operator Control                             //
//               Only runs when the robot is in opcontrol mode              //
//////////////////////////////////////////////////////////////////////////////
void opcontrol() {
    // Set arm height on opcontrol start
	arm.setTarget(armHeights[0]);

	while(true) {
		// Tank control
		chassis.tank(masterController.getAnalog(ControllerAnalog::leftY),
			masterController.getAnalog(ControllerAnalog::rightY));

		// Delay task to stop CPU hogging
		pros::delay(10);
	}	
}
