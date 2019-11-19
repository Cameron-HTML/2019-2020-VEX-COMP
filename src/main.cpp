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
static lv_point_t redLinePoints[] = {{38, 82}, {80, 40}};
static lv_point_t blueLinePoints[] = {{210, 82}, {168, 40}};

lv_obj_t * autoField;
lv_obj_t * redLeftButton;
lv_obj_t * redLeftButtonText;
lv_obj_t * redRightButton;
lv_obj_t * redRightButtonText;
lv_obj_t * blueLeftButton;
lv_obj_t * blueLeftButtonText;
lv_obj_t * blueRightButton;
lv_obj_t * blueRightButtonText;
lv_obj_t * confirmContainer;
lv_obj_t * confirmButton;
lv_obj_t * background;

lv_obj_t * highLogo;

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

lv_obj_t * redGoal1;
lv_obj_t * redGoal2;
lv_obj_t * blueGoal1;
lv_obj_t * blueGoal2;

lv_obj_t * tape1;
lv_obj_t * tape2;
lv_obj_t * tape3;
lv_obj_t * tape4;
lv_obj_t * tape5;
lv_obj_t * tape6;
lv_obj_t * tape7;
lv_obj_t * tape8;
lv_obj_t * tape9;
lv_obj_t * tape10;
lv_obj_t * tape11;
lv_obj_t * tape12;

lv_obj_t * cube1;
lv_obj_t * cube2;
lv_obj_t * cube3;
lv_obj_t * cube4;
lv_obj_t * cube5;
lv_obj_t * cube6;
lv_obj_t * cube7;
lv_obj_t * cube8;
lv_obj_t * cube9;
lv_obj_t * cube10;
lv_obj_t * cube11;
lv_obj_t * cube12;
lv_obj_t * cube13;
lv_obj_t * cube14;
lv_obj_t * cube15;
lv_obj_t * cube16;
lv_obj_t * cube17;
lv_obj_t * cube18;
lv_obj_t * cube19;
lv_obj_t * cube20;
lv_obj_t * cube21;
lv_obj_t * cube22;
lv_obj_t * cube23;
lv_obj_t * cube24;
lv_obj_t * cube25;
lv_obj_t * cube26;
lv_obj_t * cube27;
lv_obj_t * cube28;
lv_obj_t * cube29;
lv_obj_t * cube30;
lv_obj_t * cube31;
lv_obj_t * cube32;
lv_obj_t * cube33;
lv_obj_t * cube34;
lv_obj_t * cube35;
lv_obj_t * cube36;
lv_obj_t * cube37;
lv_obj_t * cube38;
lv_obj_t * cube39;
lv_obj_t * cube40;
lv_obj_t * cube41;
lv_obj_t * cube42;
lv_obj_t * cube43;
lv_obj_t * cube44;
lv_obj_t * cube45;
lv_obj_t * cube46;
lv_obj_t * cube47;
lv_obj_t * cube48;

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

static lv_style_t redGoalStyle;
static lv_style_t blueGoalStyle;

static lv_style_t tapeStyle;
static lv_style_t tapeDagStyle;

static lv_style_t purpleCubeStyle;
static lv_style_t greenCubeStyle;
static lv_style_t orangeCubeStyle;

static lv_style_t logoStyle;
static lv_style_t backgroundStyle;

typedef  FILE * pc_file_t;

static lv_fs_res_t pcfs_open( void * file_p, const char * fn, lv_fs_mode_t mode)
{
    errno = 0;
    const char * flags = "";
    if(mode == LV_FS_MODE_WR) flags = "wb";
    else if(mode == LV_FS_MODE_RD) flags = "rb";
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) flags = "a+";

    char buf[256];
    sprintf(buf, "/%s", fn);
    pc_file_t f = fopen(buf, flags);

    if(f == NULL)
      return LV_FS_RES_UNKNOWN;
    else {
      fseek(f, 0, SEEK_SET);
      pc_file_t * fp = (pc_file_t *)file_p;
      *fp = f;
    }

    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_close( void * file_p)
{
    pc_file_t * fp = (pc_file_t *)file_p;
    fclose(*fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_read( void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    pc_file_t * fp =  (pc_file_t *)file_p;
    *br = fread(buf, 1, btr, *fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_seek( void * file_p, uint32_t pos)
{
    pc_file_t * fp = (pc_file_t *)file_p;
    fseek(*fp, pos, SEEK_SET);
    return LV_FS_RES_OK;
}

static lv_fs_res_t pcfs_tell( void * file_p, uint32_t * pos_p)
{
    pc_file_t * fp =  (pc_file_t *)file_p;
    *pos_p = ftell(*fp);
    return LV_FS_RES_OK;
}


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

        lv_obj_align(redLeftButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 185);
        break;
     case 2:
        lv_obj_del(redLeftButton);
        lv_obj_del(blueLeftButton);
        lv_obj_del(blueRightButton);
        lv_obj_del(confirmContainer);
        lv_obj_del(confirmButton);
        lv_obj_del(autoField);

        lv_obj_align(redRightButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 185);
        break;
     case 3:
        lv_obj_del(redLeftButton);
        lv_obj_del(redRightButton);
        lv_obj_del(blueRightButton);
        lv_obj_del(confirmContainer);
        lv_obj_del(confirmButton);
        lv_obj_del(autoField);

        lv_obj_align(blueLeftButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 185);
        break;
     case 4:
        lv_obj_del(redLeftButton);
        lv_obj_del(redRightButton);
        lv_obj_del(blueLeftButton);
        lv_obj_del(confirmContainer);
        lv_obj_del(confirmButton);
        lv_obj_del(autoField);

        lv_obj_align(blueRightButton, NULL, LV_ALIGN_IN_TOP_MID, 0, 185);
        break;
    default:
        break;
    }

    logoStyle.image.opa = 255;
    lv_obj_align(highLogo, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
}

//////////////////////////////////////////////////////////////////////////////
//                               Initialize                                 //
//                   Runs when the program first starts                     //
//////////////////////////////////////////////////////////////////////////////
void initialize() {
    pros::delay(100);

    /* Add a simple drive to open images from PC*/
    lv_fs_drv_t pcfs_drv;                         /*A driver descriptor*/
    memset(&pcfs_drv, 0, sizeof(lv_fs_drv_t));    /*Initialization*/

    pcfs_drv.file_size = sizeof(pc_file_t);       /*Set up fields...*/
    pcfs_drv.letter = 'S';
    pcfs_drv.open = pcfs_open;
    pcfs_drv.close = pcfs_close;
    pcfs_drv.read = pcfs_read;
    pcfs_drv.seek = pcfs_seek;
    pcfs_drv.tell = pcfs_tell;
    lv_fs_add_drv(&pcfs_drv);

    // Object styles
    lv_style_copy(&logoStyle, &lv_style_plain);
    logoStyle.image.opa = 0;

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

    lv_style_copy(&redGoalStyle, &lv_style_plain_color);
    redGoalStyle.body.main_color = LV_COLOR_RED;
    redGoalStyle.body.grad_color = LV_COLOR_RED;
    redGoalStyle.body.opa = 0;
    redGoalStyle.body.border.color = LV_COLOR_RED;
    redGoalStyle.body.border.width = 5;
    redGoalStyle.body.border.opa = 255;
    redGoalStyle.body.border.part = 11;
    redGoalStyle.body.radius = 2;

    lv_style_copy(&blueGoalStyle, &lv_style_plain_color);
    blueGoalStyle.body.main_color = LV_COLOR_BLUE;
    blueGoalStyle.body.grad_color = LV_COLOR_BLUE;
    blueGoalStyle.body.opa = 0;
    blueGoalStyle.body.border.color = LV_COLOR_BLUE;
    blueGoalStyle.body.border.width = 5;
    blueGoalStyle.body.border.opa = 255;
    blueGoalStyle.body.border.part = 15;
    blueGoalStyle.body.radius = 2;

    lv_style_copy(&tapeStyle, &lv_style_plain_color);
    tapeStyle.body.main_color = LV_COLOR_WHITE;
    tapeStyle.body.grad_color = LV_COLOR_WHITE;

    lv_style_copy(&tapeDagStyle, &lv_style_plain);
    tapeDagStyle.line.color = LV_COLOR_WHITE;
    tapeDagStyle.line.width = 5;

    lv_style_copy(&purpleCubeStyle, &lv_style_plain_color);
    purpleCubeStyle.body.main_color = LV_COLOR_PURPLE;
    purpleCubeStyle.body.grad_color = LV_COLOR_PURPLE;
    purpleCubeStyle.body.radius = 2;

    lv_style_copy(&greenCubeStyle, &lv_style_plain_color);
    greenCubeStyle.body.main_color = LV_COLOR_GREEN;
    greenCubeStyle.body.grad_color = LV_COLOR_GREEN;
    greenCubeStyle.body.radius = 2;

    lv_style_copy(&orangeCubeStyle, &lv_style_plain_color);
    orangeCubeStyle.body.main_color = LV_COLOR_ORANGE;
    orangeCubeStyle.body.grad_color = LV_COLOR_ORANGE;
    orangeCubeStyle.body.radius = 2;

    lv_style_copy(&backgroundStyle, &lv_style_plain_color);
    backgroundStyle.body.main_color = LV_COLOR_BLACK;
    backgroundStyle.body.grad_color = LV_COLOR_BLACK;

    background = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(background, 700, 700);
    lv_obj_set_style(background, &backgroundStyle);

    highLogo = lv_img_create(lv_scr_act(), NULL); /*Crate an image object*/
    lv_img_set_src(highLogo, "S:/usd/highrollersLogo.bin");  /*Set the created file as image (a red rose)*/
    lv_obj_align(highLogo, NULL, LV_ALIGN_IN_TOP_MID, 0, -500);
    lv_img_set_style(highLogo, &logoStyle);

    // Field object
    autoField = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(autoField, 250, 250);
    lv_obj_set_style(autoField, &autoFieldStyle);
    lv_obj_align(autoField, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    // Button w/ text objects
    redLeftButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_TGL_PR, &redButtonStyle);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_TGL_REL, &redButtonStyleTGL);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_REL, &redButtonStyle);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_PR, &redButtonStyle);
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_INA, &redButtonStyle);
    lv_obj_set_size(redLeftButton, 140, 50);
    lv_obj_align(redLeftButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, -80);
    lv_btn_set_action(redLeftButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    redLeftButtonText = lv_label_create(redLeftButton, NULL);
    lv_label_set_text(redLeftButtonText, "Left");

    redRightButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_PR, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_TGL_REL, &redButtonStyleTGL);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_REL, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_PR, &redButtonStyle);
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_INA, &redButtonStyle);
    lv_obj_set_size(redRightButton, 140, 50);
    lv_obj_align(redRightButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, -27);
    lv_btn_set_action(redRightButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    redRightButtonText = lv_label_create(redRightButton, NULL);
    lv_label_set_text(redRightButtonText, "Right");

    blueLeftButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_TGL_PR, &blueButtonStyle);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_TGL_REL, &blueButtonStyleTGL);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_REL, &blueButtonStyle);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_PR, &blueButtonStyle);
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_INA, &blueButtonStyle);
    lv_obj_set_size(blueLeftButton, 140, 50);
    lv_obj_align(blueLeftButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 26);
    lv_btn_set_action(blueLeftButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    blueLeftButtonText = lv_label_create(blueLeftButton, NULL);
    lv_label_set_text(blueLeftButtonText, "Left");

    blueRightButton = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_TGL_PR, &blueButtonStyle);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_TGL_REL, &blueButtonStyleTGL);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_REL, &blueButtonStyle);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_PR, &blueButtonStyle);
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_INA, &blueButtonStyle);
    lv_obj_set_size(blueRightButton, 140, 50);
    lv_obj_align(blueRightButton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 79);
    lv_btn_set_action(blueRightButton, LV_BTN_ACTION_CLICK, buttonPressEvent);

    blueRightButtonText = lv_label_create(blueRightButton, NULL);
    lv_label_set_text(blueRightButtonText, "Right");

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

    redTile1 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(redTile1, 40, 40);
    lv_obj_set_style(redTile1, &redTileStyle);
    lv_obj_align(redTile1, NULL, LV_ALIGN_IN_TOP_LEFT, 40, 0);

    redTile2 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(redTile2, 40, 40);
    lv_obj_set_style(redTile2, &redTileStyle);
    lv_obj_align(redTile2, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 40);

    blueTile1 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(blueTile1, 40, 40);
    lv_obj_set_style(blueTile1, &blueTileStyle);
    lv_obj_align(blueTile1, NULL, LV_ALIGN_IN_TOP_RIGHT, -40, 0);

    blueTile2 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(blueTile2, 40, 40);
    lv_obj_set_style(blueTile2, &blueTileStyle);
    lv_obj_align(blueTile2, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 40);

    tape1 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape1, 4, 250);
    lv_obj_set_style(tape1, &tapeStyle);
    lv_obj_align(tape1, NULL, LV_ALIGN_IN_TOP_MID, -4, 0);

    tape2 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape2, 4, 250);
    lv_obj_set_style(tape2, &tapeStyle);
    lv_obj_align(tape2, NULL, LV_ALIGN_IN_TOP_MID, 4, 0);

    tape3 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape3, 4, 41);
    lv_obj_set_style(tape3, &tapeStyle);
    lv_obj_align(tape3, NULL, LV_ALIGN_IN_TOP_LEFT, 38, 0);
    
    tape4 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape4, 41, 4);
    lv_obj_set_style(tape4, &tapeStyle);
    lv_obj_align(tape4, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 38);

    tape5 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape5, 4, 41);
    lv_obj_set_style(tape5, &tapeStyle);
    lv_obj_align(tape5, NULL, LV_ALIGN_IN_TOP_LEFT, 80, 0);
    
    tape6 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape6, 41, 4);
    lv_obj_set_style(tape6, &tapeStyle);
    lv_obj_align(tape6, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 80);

    tape7 = lv_line_create(autoField, NULL);
    lv_line_set_style(tape7, &tapeDagStyle);
    lv_line_set_points(tape7, redLinePoints, 2);

    tape8 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape8, 4, 41);
    lv_obj_set_style(tape8, &tapeStyle);
    lv_obj_align(tape8, NULL, LV_ALIGN_IN_TOP_RIGHT, -38, 0);
    
    tape9 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape9, 41, 4);
    lv_obj_set_style(tape9, &tapeStyle);
    lv_obj_align(tape9, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 38);

    tape10 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape10, 4, 41);
    lv_obj_set_style(tape10, &tapeStyle);
    lv_obj_align(tape10, NULL, LV_ALIGN_IN_TOP_RIGHT, -80, 0);
    
    tape11 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tape11, 41, 4);
    lv_obj_set_style(tape11, &tapeStyle);
    lv_obj_align(tape11, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 80);

    tape12 = lv_line_create(autoField, NULL);
    lv_line_set_style(tape12, &tapeDagStyle);
    lv_line_set_points(tape12, blueLinePoints, 2);

    tower1 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tower1, 20, 20);
    lv_obj_set_style(tower1, &towerStyle);
    lv_obj_align(tower1, NULL, LV_ALIGN_IN_TOP_MID, 0, 114);

    tower2 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tower2, 20, 20);
    lv_obj_set_style(tower2, &towerStyle);
    lv_obj_align(tower2, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -44);

    tower3 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tower3, 20, 20);
    lv_obj_set_style(tower3, &towerStyle);
    lv_obj_align(tower3, NULL, LV_ALIGN_IN_TOP_MID, 0, 44);

    tower4 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tower4, 20, 20);
    lv_obj_set_style(tower4, &towerStyle);
    lv_obj_align(tower4, NULL, LV_ALIGN_IN_RIGHT_MID, -204, 0);

    tower5 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tower5, 20, 20);
    lv_obj_set_style(tower5, &towerStyle);
    lv_obj_align(tower5, NULL, LV_ALIGN_IN_RIGHT_MID, -28, 0);

    tower6 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tower6, 20, 20);
    lv_obj_set_style(tower6, &redTowerStyle);
    lv_obj_align(tower6, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -182, 0);

    tower7 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(tower7, 20, 20);
    lv_obj_set_style(tower7, &blueTowerStyle);
    lv_obj_align(tower7, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -50, 0);

    redGoal1 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(redGoal1, 25, 25);
    lv_obj_set_style(redGoal1, &redGoalStyle);
    lv_obj_align(redGoal1, NULL, LV_ALIGN_IN_BOTTOM_LEFT, -3, 0);

    redGoal2 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(redGoal2, 35, 25);
    lv_obj_set_style(redGoal2, &redGoalStyle);
    lv_obj_align(redGoal2, NULL, LV_ALIGN_IN_TOP_LEFT, -3, 0);

    blueGoal1 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(blueGoal1, 26, 25);
    lv_obj_set_style(blueGoal1, &blueGoalStyle);
    lv_obj_align(blueGoal1, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 5, 0);

    blueGoal2 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(blueGoal2, 35, 25);
    lv_obj_set_style(blueGoal2, &blueGoalStyle);
    lv_obj_align(blueGoal2, NULL, LV_ALIGN_IN_TOP_RIGHT, 5, 0);

    cube1 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube1, 13, 13);
    lv_obj_set_style(cube1, &purpleCubeStyle);
    lv_obj_align(cube1, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 50, -30);

    cube2 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube2, 13, 13);
    lv_obj_set_style(cube2, &greenCubeStyle);
    lv_obj_align(cube2, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 63, -30);

    cube3 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube3, 13, 13);
    lv_obj_set_style(cube3, &greenCubeStyle);
    lv_obj_align(cube3, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 76, -30);

    cube4 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube4, 13, 13);
    lv_obj_set_style(cube4, &orangeCubeStyle);
    lv_obj_align(cube4, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 89, -30);

    cube5 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube5, 13, 13);
    lv_obj_set_style(cube5, &purpleCubeStyle);
    lv_obj_align(cube5, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 63, -70);

    cube6 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube6, 13, 13);
    lv_obj_set_style(cube6, &greenCubeStyle);
    lv_obj_align(cube6, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 76, -70);

    cube7 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube7, 13, 13);
    lv_obj_set_style(cube7, &orangeCubeStyle);
    lv_obj_align(cube7, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 89, -70);

    cube8 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube8, 13, 13);
    lv_obj_set_style(cube8, &purpleCubeStyle);
    lv_obj_align(cube8, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 76, -124);

    cube9 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube9, 13, 13);
    lv_obj_set_style(cube9, &orangeCubeStyle);
    lv_obj_align(cube9, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 89, -124);

    cube10 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube10, 13, 13);
    lv_obj_set_style(cube10, &orangeCubeStyle);
    lv_obj_align(cube10, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 89, -167);

    cube11 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube11, 13, 13);
    lv_obj_set_style(cube11, &orangeCubeStyle);
    lv_obj_align(cube11, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 40, -167);

    cube12 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube12, 13, 13);
    lv_obj_set_style(cube12, &orangeCubeStyle);
    lv_obj_align(cube12, NULL, LV_ALIGN_IN_LEFT_MID, 13, 0);

    cube13 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube13, 13, 13);
    lv_obj_set_style(cube13, &purpleCubeStyle);
    lv_obj_align(cube13, NULL, LV_ALIGN_IN_LEFT_MID, 30, 16);

    cube14 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube14, 13, 13);
    lv_obj_set_style(cube14, &purpleCubeStyle);
    lv_obj_align(cube14, NULL, LV_ALIGN_IN_LEFT_MID, 30, -17);

    cube15 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube15, 13, 13);
    lv_obj_set_style(cube15, &orangeCubeStyle);
    lv_obj_align(cube15, NULL, LV_ALIGN_IN_LEFT_MID, 40, -90);

    cube16 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube16, 13, 13);
    lv_obj_set_style(cube16, &purpleCubeStyle);
    lv_obj_align(cube16, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -50, -30);

    cube17 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube17, 13, 13);
    lv_obj_set_style(cube17, &orangeCubeStyle);
    lv_obj_align(cube17, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -63, -30);

    cube18 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube18, 13, 13);
    lv_obj_set_style(cube18, &orangeCubeStyle);
    lv_obj_align(cube18, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -76, -30);

    cube19 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube19, 13, 13);
    lv_obj_set_style(cube19, &greenCubeStyle);
    lv_obj_align(cube19, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -89, -30);

    cube20 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube20, 13, 13);
    lv_obj_set_style(cube20, &purpleCubeStyle);
    lv_obj_align(cube20, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -63, -70);

    cube21 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube21, 13, 13);
    lv_obj_set_style(cube21, &orangeCubeStyle);
    lv_obj_align(cube21, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -76, -70);

    cube22 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube22, 13, 13);
    lv_obj_set_style(cube22, &greenCubeStyle);
    lv_obj_align(cube22, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -89, -70);

    cube23 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube23, 13, 13);
    lv_obj_set_style(cube23, &purpleCubeStyle);
    lv_obj_align(cube23, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -76, -124);

    cube24 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube24, 13, 13);
    lv_obj_set_style(cube24, &greenCubeStyle);
    lv_obj_align(cube24, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -89, -124);

    cube25 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube25, 13, 13);
    lv_obj_set_style(cube25, &greenCubeStyle);
    lv_obj_align(cube25, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -89, -167);

    cube26 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube26, 13, 13);
    lv_obj_set_style(cube26, &greenCubeStyle);
    lv_obj_align(cube26, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -40, -167);

    cube27 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube27, 13, 13);
    lv_obj_set_style(cube27, &greenCubeStyle);
    lv_obj_align(cube27, NULL, LV_ALIGN_IN_RIGHT_MID, -13, 0);

    cube28 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube28, 13, 13);
    lv_obj_set_style(cube28, &purpleCubeStyle);
    lv_obj_align(cube28, NULL, LV_ALIGN_IN_RIGHT_MID, -30, 16);

    cube29 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube29, 13, 13);
    lv_obj_set_style(cube29, &purpleCubeStyle);
    lv_obj_align(cube29, NULL, LV_ALIGN_IN_RIGHT_MID, -30, -17);

    cube30 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube30, 13, 13);
    lv_obj_set_style(cube30, &greenCubeStyle);
    lv_obj_align(cube30, NULL, LV_ALIGN_IN_RIGHT_MID, -40, -90);

    cube31 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube31, 13, 13);
    lv_obj_set_style(cube31, &greenCubeStyle);
    lv_obj_align(cube31, NULL, LV_ALIGN_IN_BOTTOM_MID, -6, 0);

    cube32 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube32, 13, 13);
    lv_obj_set_style(cube32, &greenCubeStyle);
    lv_obj_align(cube32, NULL, LV_ALIGN_IN_BOTTOM_MID, -6, -13);

    cube33 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube33, 13, 13);
    lv_obj_set_style(cube33, &orangeCubeStyle);
    lv_obj_align(cube33, NULL, LV_ALIGN_IN_BOTTOM_MID, 6, 0);

    cube34 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube34, 13, 13);
    lv_obj_set_style(cube34, &orangeCubeStyle);
    lv_obj_align(cube34, NULL, LV_ALIGN_IN_BOTTOM_MID, 6, -13);

    cube35 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube35, 13, 13);
    lv_obj_set_style(cube35, &purpleCubeStyle);
    lv_obj_align(cube35, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -8);

    cube36 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube36, 13, 13);
    lv_obj_set_style(cube36, &purpleCubeStyle);
    lv_obj_align(cube36, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -32);

    cube37 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube37, 13, 13);
    lv_obj_set_style(cube37, &purpleCubeStyle);
    lv_obj_align(cube37, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -64);

    cube38 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube38, 13, 13);
    lv_obj_set_style(cube38, &purpleCubeStyle);
    lv_obj_align(cube38, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -104);

    cube39 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube39, 13, 13);
    lv_obj_set_style(cube39, &purpleCubeStyle);
    lv_obj_align(cube39, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -136);

    cube40 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube40, 13, 13);
    lv_obj_set_style(cube40, &purpleCubeStyle);
    lv_obj_align(cube40, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -174);

    cube41 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube41, 13, 13);
    lv_obj_set_style(cube41, &purpleCubeStyle);
    lv_obj_align(cube41, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -206);

    cube42 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube42, 13, 13);
    lv_obj_set_style(cube42, &purpleCubeStyle);
    lv_obj_align(cube42, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -206);

    cube43 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube43, 13, 13);
    lv_obj_set_style(cube43, &greenCubeStyle);
    lv_obj_align(cube43, NULL, LV_ALIGN_IN_BOTTOM_MID, 15, -47);

    cube44 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube44, 13, 13);
    lv_obj_set_style(cube44, &greenCubeStyle);
    lv_obj_align(cube44, NULL, LV_ALIGN_IN_BOTTOM_MID, 15, -119);

    cube45 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube45, 13, 13);
    lv_obj_set_style(cube45, &greenCubeStyle);
    lv_obj_align(cube45, NULL, LV_ALIGN_IN_BOTTOM_MID, 15, -189);

    cube46 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube46, 13, 13);
    lv_obj_set_style(cube46, &orangeCubeStyle);
    lv_obj_align(cube46, NULL, LV_ALIGN_IN_BOTTOM_MID, -15, -47);

    cube47 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube47, 13, 13);
    lv_obj_set_style(cube47, &orangeCubeStyle);
    lv_obj_align(cube47, NULL, LV_ALIGN_IN_BOTTOM_MID, -15, -119);

    cube48 = lv_obj_create(autoField, NULL);
    lv_obj_set_size(cube48, 13, 13);
    lv_obj_set_style(cube48, &orangeCubeStyle);
    lv_obj_align(cube48, NULL, LV_ALIGN_IN_BOTTOM_MID, -15, -189);

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
