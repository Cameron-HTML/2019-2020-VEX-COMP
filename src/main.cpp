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

lv_obj_t * redTile1;
lv_obj_t * redTile2;
lv_obj_t * blueTile1;
lv_obj_t * blueTile2;

lv_obj_t * tower1;
lv_obj_t * tower2;
lv_obj_t * tower3;
lv_obj_t * tower4;
lv_obj_t * tower5;
lv_obj_t * tower6;
lv_obj_t * tower7;

static lv_style_t autoFieldStyle;
static lv_style_t redButtonStyle;
static lv_style_t redButtonStyleTGL;
static lv_style_t blueButtonStyle;
static lv_style_t blueButtonStyleTGL;
static lv_style_t buttonContainerStyle;
static lv_style_t confirmButtonStyle;
static lv_style_t confirmButtonStyleTGL;

static lv_style_t redTileStyle;
static lv_style_t blueTileStyle;

static lv_style_t towerStyle;
static lv_style_t redTowerStyle;
static lv_style_t blueTowerStyle;

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

    if(confirmButtonStyle.body.opa == 0) {
        confirmButtonStyle.body.opa = 255;
        lv_btn_set_state(confirmButton, LV_BTN_STATE_TGL_PR);
    }

}

static lv_res_t confirmSelected(lv_obj_t * btn) {
    switch (selectedAuto) {
    case 1:
        lv_obj_del(redRightButton);
        lv_obj_del(blueLeftButton);
        lv_obj_del(blueRightButton);
        lv_obj_del(confirmContainer);
        lv_obj_del(confirmButton);
        lv_obj_del(autoField);
        break;
     case 2:
        lv_obj_del(redLeftButton);
        lv_obj_del(blueLeftButton);
        lv_obj_del(blueRightButton);
        lv_obj_del(confirmContainer);
        lv_obj_del(confirmButton);
        lv_obj_del(autoField);
        break;
     case 3:
        lv_obj_del(redLeftButton);
        lv_obj_del(redRightButton);
        lv_obj_del(blueRightButton);
        lv_obj_del(confirmContainer);
        lv_obj_del(confirmButton);
        lv_obj_del(autoField);
        break;
     case 4:
        lv_obj_del(redLeftButton);
        lv_obj_del(redRightButton);
        lv_obj_del(blueLeftButton);
        lv_obj_del(confirmContainer);
        lv_obj_del(confirmButton);
        lv_obj_del(autoField);
        break;
    default:
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void initialize() {
    pros::delay(100);

    // Object styles
    lv_style_copy(&autoFieldStyle, &lv_style_plain_color);
    autoFieldStyle.body.main_color = LV_COLOR_GRAY;
    autoFieldStyle.body.grad_color = LV_COLOR_GRAY;

    lv_style_copy(&redButtonStyle, &lv_style_plain_color);
    redButtonStyle.body.main_color = LV_COLOR_RED;
    redButtonStyle.body.grad_color = LV_COLOR_RED;
    redButtonStyle.body.border.color = LV_COLOR_WHITE;
    redButtonStyle.body.border.width = 1;

    lv_style_copy(&redButtonStyleTGL, &lv_style_plain_color);
    redButtonStyleTGL.body.main_color = LV_COLOR_MAKE(245, 87, 76);
    redButtonStyleTGL.body.grad_color = LV_COLOR_MAKE(245, 87, 76);
    redButtonStyleTGL.body.border.color = LV_COLOR_WHITE;
    redButtonStyleTGL.body.border.width = 1;

    lv_style_copy(&blueButtonStyle, &lv_style_plain_color);
    blueButtonStyle.body.main_color = LV_COLOR_BLUE;
    blueButtonStyle.body.grad_color = LV_COLOR_BLUE;
    blueButtonStyle.body.border.color = LV_COLOR_WHITE;
    blueButtonStyle.body.border.width = 1;

    lv_style_copy(&blueButtonStyleTGL, &lv_style_plain_color);
    blueButtonStyleTGL.body.main_color = LV_COLOR_MAKE(0, 0, 139);
    blueButtonStyleTGL.body.grad_color = LV_COLOR_MAKE(0, 0, 139);
    blueButtonStyleTGL.body.border.color = LV_COLOR_WHITE;
    blueButtonStyleTGL.body.border.width = 1;

    lv_style_copy(&buttonContainerStyle, &lv_style_plain_color);
    buttonContainerStyle.body.main_color = LV_COLOR_GRAY;
    buttonContainerStyle.body.grad_color = LV_COLOR_GRAY;
    buttonContainerStyle.body.border.color = LV_COLOR_WHITE;
    buttonContainerStyle.body.border.width = 1;

    lv_style_copy(&confirmButtonStyle, &lv_style_plain_color);
    confirmButtonStyle.body.main_color = LV_COLOR_MAKE(0, 255, 0);
    confirmButtonStyle.body.grad_color = LV_COLOR_MAKE(0, 255, 0);
    confirmButtonStyle.body.opa = 0;

    lv_style_copy(&confirmButtonStyleTGL, &lv_style_plain_color);
    confirmButtonStyleTGL.body.main_color = LV_COLOR_MAKE(50, 205, 50);
    confirmButtonStyleTGL.body.grad_color = LV_COLOR_MAKE(50, 205, 50);

    lv_style_copy(&towerStyle, &lv_style_plain_color);
    towerStyle.body.main_color = LV_COLOR_MAKE(0, 0, 0);
    towerStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 0);
    towerStyle.body.radius = LV_RADIUS_CIRCLE;
    towerStyle.body.border.color = LV_COLOR_WHITE;
    towerStyle.body.border.width = 3;

    lv_style_copy(&redTowerStyle, &lv_style_plain_color);
    redTowerStyle.body.main_color = LV_COLOR_RED;
    redTowerStyle.body.grad_color = LV_COLOR_RED;
    redTowerStyle.body.radius = LV_RADIUS_CIRCLE;
    redTowerStyle.body.border.color = LV_COLOR_WHITE;
    redTowerStyle.body.border.width = 3;

    lv_style_copy(&blueTowerStyle, &lv_style_plain_color);
    blueTowerStyle.body.main_color = LV_COLOR_BLUE;
    blueTowerStyle.body.grad_color = LV_COLOR_BLUE;
    blueTowerStyle.body.radius = LV_RADIUS_CIRCLE;
    blueTowerStyle.body.border.color = LV_COLOR_WHITE;
    blueTowerStyle.body.border.width = 3;

    lv_style_copy(&redTileStyle, &lv_style_plain_color);
    redTileStyle.body.main_color = LV_COLOR_RED;
    redTileStyle.body.grad_color = LV_COLOR_RED;

    lv_style_copy(&blueTileStyle, &lv_style_plain_color);
    blueTileStyle.body.main_color = LV_COLOR_BLUE;
    blueTileStyle.body.grad_color = LV_COLOR_BLUE;

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
    lv_obj_align(confirmButton, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
    lv_btn_set_action(confirmButton, LV_BTN_ACTION_CLICK, confirmSelected);
    lv_btn_set_state(confirmButton, LV_BTN_STYLE_INA);

    redTile1 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(redTile1, 40, 40);
    lv_obj_set_style(redTile1, &redTileStyle);
    lv_obj_align(redTile1, NULL, LV_ALIGN_IN_TOP_MID, 50, 0);

    redTile2 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(redTile2, 40, 40);
    lv_obj_set_style(redTile2, &redTileStyle);
    lv_obj_align(redTile2, NULL, LV_ALIGN_IN_TOP_MID, 10, 40);

    blueTile1 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(blueTile1, 40, 40);
    lv_obj_set_style(blueTile1, &blueTileStyle);
    lv_obj_align(blueTile1, NULL, LV_ALIGN_IN_TOP_RIGHT, -40, 0);

    blueTile2 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(blueTile2, 40, 40);
    lv_obj_set_style(blueTile2, &blueTileStyle);
    lv_obj_align(blueTile2, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 40);

    tower1 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(tower1, 20, 20);
    lv_obj_set_style(tower1, &towerStyle);
    lv_obj_align(tower1, NULL, LV_ALIGN_IN_RIGHT_MID, -109, 0);

    tower2 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(tower2, 20, 20);
    lv_obj_set_style(tower2, &towerStyle);
    lv_obj_align(tower2, NULL, LV_ALIGN_IN_RIGHT_MID, -109, 74);

    tower3 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(tower3, 20, 20);
    lv_obj_set_style(tower3, &towerStyle);
    lv_obj_align(tower3, NULL, LV_ALIGN_IN_RIGHT_MID, -109, -74);

    tower4 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(tower4, 20, 20);
    lv_obj_set_style(tower4, &towerStyle);
    lv_obj_align(tower4, NULL, LV_ALIGN_IN_RIGHT_MID, -189, 0);

    tower5 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(tower5, 20, 20);
    lv_obj_set_style(tower5, &towerStyle);
    lv_obj_align(tower5, NULL, LV_ALIGN_IN_RIGHT_MID, -28, 0);

    tower6 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(tower6, 20, 20);
    lv_obj_set_style(tower6, &redTowerStyle);
    lv_obj_align(tower6, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -167, 0);

    tower7 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(tower7, 20, 20);
    lv_obj_set_style(tower7, &blueTowerStyle);
    lv_obj_align(tower7, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -50, 0);

    leftIntake.setBrakeMode(AbstractMotor::brakeMode::hold);
	rightIntake.setBrakeMode(AbstractMotor::brakeMode::hold);
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
