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

    static lv_style_t redRightButtonStyle;
    lv_style_copy(&redRightButtonStyle, &lv_style_plain_color);
    redRightButtonStyle.body.main_color = LV_COLOR_RED;
    redRightButtonStyle.body.grad_color = LV_COLOR_RED;
    redRightButtonStyle.body.border.color = LV_COLOR_WHITE;
    redRightButtonStyle.body.border.width = 1;

    lv_obj_t * redRightButton;
    redRightButton = lv_btn_create(lv_scr_act(), NULL);
    //lv_obj_set_event_cb(redRightButton, autoSelectEventHandler)
    lv_obj_set_size(redRightButton, 140, 50);
    lv_obj_set_style(redRightButton, &redRightButtonStyle);
    lv_obj_align(redRightButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, -80);
    lv_btn_set_toggle(redRightButton, true);
    lv_btn_toggle(redRightButton);


    static lv_style_t redLeftBoxStyle;
    lv_style_copy(&redLeftBoxStyle, &lv_style_plain_color);
    redLeftBoxStyle.body.main_color = LV_COLOR_RED;
    redLeftBoxStyle.body.grad_color = LV_COLOR_RED;
    redLeftBoxStyle.body.border.color = LV_COLOR_WHITE;
    redLeftBoxStyle.body.border.width = 1;

    lv_obj_t * redLeftBox;
    redLeftBox = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(redLeftBox, 140, 50);
    lv_obj_set_style(redLeftBox, &redLeftBoxStyle);
    lv_obj_align(redLeftBox, NULL, LV_ALIGN_IN_LEFT_MID, 10, -27);

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
