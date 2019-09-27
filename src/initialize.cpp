#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

// static void autoSelectEventHandler(lv_obj_t * obj, lv_event_t event) {
//     // if(event == LV_EVENT_VALUE_CHANGED) {
//     //     cout << "Toggled" << endl;
//     // }
// }

static lv_res_t buttonPressEvent(struct _lv_obj_t * obj) {
    cout << "Button PRESSED" << endl;
    return LV_RES_INV;
}

void initialize() {
    static lv_style_t autoFieldStyle;
    lv_style_copy(&autoFieldStyle, &lv_style_plain_color);
    autoFieldStyle.body.main_color = LV_COLOR_GRAY;
    autoFieldStyle.body.grad_color = LV_COLOR_GRAY;

    lv_obj_t * autoField;
    autoField = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(autoField, 250, 250);
    lv_obj_set_style(autoField, &autoFieldStyle);
    lv_obj_align(autoField, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

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

    lv_obj_t * redRightButton;
    redRightButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_PR, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_REL, &redButtonStyleTGL);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_REL, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_PR, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_INA, &redButtonStyle);
    lv_obj_set_size(redRightButton, 140, 50);
    lv_obj_align(redRightButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, -80);
    lv_btn_set_action(redRightButton, LV_BTN_ACTION_PR, buttonPressEvent);

    static lv_style_t blueRightBoxStyle;
    lv_style_copy(&blueRightBoxStyle, &lv_style_plain_color);
    blueRightBoxStyle.body.main_color = LV_COLOR_BLUE;
    blueRightBoxStyle.body.grad_color = LV_COLOR_BLUE;
    blueRightBoxStyle.body.border.color = LV_COLOR_WHITE;
    blueRightBoxStyle.body.border.width = 1;

    lv_obj_t * blueRightBox;
    blueRightBox = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(blueRightBox, 140, 50);
    lv_obj_set_style(blueRightBox, &blueRightBoxStyle);
    lv_obj_align(blueRightBox, NULL, LV_ALIGN_IN_LEFT_MID, 10, 26);

    static lv_style_t blueLeftBoxStyle;
    lv_style_copy(&blueLeftBoxStyle, &lv_style_plain_color);
    blueLeftBoxStyle.body.main_color = LV_COLOR_BLUE;
    blueLeftBoxStyle.body.grad_color = LV_COLOR_BLUE;
    blueLeftBoxStyle.body.border.color = LV_COLOR_WHITE;
    blueLeftBoxStyle.body.border.width = 1;

    lv_obj_t * blueLeftBox;
    blueLeftBox = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(blueLeftBox, 140, 50);
    lv_obj_set_style(blueLeftBox, &blueLeftBoxStyle);
    lv_obj_align(blueLeftBox, NULL, LV_ALIGN_IN_LEFT_MID, 10, 79);

    // lv_obj_t * redRight = lv_label_create(lv_scr_act(), NULL);
    // lv_label_set_recolor(redRight, true);
    // lv_obj_align(redRight, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
    // lv_label_set_align(redRight, LV_LABEL_ALIGN_LEFT);
    // lv_label_set_text(redRight, "#000000 Red Right");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {}
