
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

static const wchar_t * title = L"LVGL Training";
int btn21_pressed = 0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static const char * btnm_map[] = {
                                  "Clear", "Backspace", "\n",
                                  "1/x", "x^2", "x^1/2", "/", "\n",
                                  "7", "8", "9", "*", "\n",
                                  "4", "5", "6", "-", "\n",
                                  "1", "2", "3", "+", "\n",
                                  "+/-", "0", ".", "=", "\0"
                                 };

static double num2 = 0;
int operate = 0;
#define MAX_NUM 15
static char num1[MAX_NUM] = {0};
lv_obj_t * label1;
lv_obj_t * label2;

static void process_num(char * txt)
{
    int i = strlen(num1);
    printf("i=%d \n", i);

    if (i < MAX_NUM){
        num1[i] = txt[0];
        lv_label_set_text(label1, num1);

        printf("num1[] = %s \n", num1);
    }else{
        printf("i == MAX_NUM \n");
    }
}
void process_calculate_type1(int id)
{
    double tmp = atof(num1);

    switch(id)
    {
        case 2:
            if (tmp == 0)
                lv_label_set_text(label2, "Divisor cannot be ZERO!");
            else {
                tmp = 1 / tmp;
                printf("1/x = %f \n", tmp);
                lv_label_set_text_fmt(label2, "1/(%s)", num1);
            }
            break;

        case 3:
            tmp = tmp * tmp;
            printf("x^2 = %f \n", tmp);
            lv_label_set_text_fmt(label2, "sqr(%s)", num1);
            break;

        case 4:
            if (tmp < 0)
                lv_label_set_text(label2, "Neg num cannot square!");
            else {
                tmp = sqrt(tmp);
                printf("x 1/2 = %f \n", tmp);
                lv_label_set_text_fmt(label2, "(%s)^1/2", num1);
            }
            break;
    }

    sprintf(num1, "%g", tmp);
    lv_label_set_text(label1, num1);
    memset(num1, 0, MAX_NUM);
}

void process_calculate_type2(int id)
{
    num2 = atof(num1);

    switch(id)
    {
        //printf("process /, x, -, + \n");
        case 5:
            lv_label_set_text_fmt(label2, "%s / ", num1);
            operate = 1;
            break;

        case 9:
            lv_label_set_text_fmt(label2, "%s x ", num1);
            operate = 2;
            break;

        case 13:
            lv_label_set_text_fmt(label2, "%s - ", num1);
            operate = 3;
            break;

        case 17:
            lv_label_set_text_fmt(label2, "%s + ", num1);
            operate = 4;
            break;

        default:
            operate = 0;
            break;
    }
    memset(num1, 0, MAX_NUM);
}

void process_calculate_equal(void)
{
    double tmp = atof(num1);
    switch(operate)
    {
        case 1:
            num2 = num2 / tmp;
            break;

        case 2:
            num2 = num2 * tmp;
            break;

        case 3:
            num2 = num2 - tmp;
            break;

        case 4:
            num2 = num2 + tmp;
            break;

        default:
            break;
    }

    sprintf(num1, "%g", num2);
    lv_label_set_text(label1, num1);

    memset(num1, 0, MAX_NUM);
}

void process_clear(void)
{
    lv_label_set_text(label1, "0");
    lv_label_set_text(label2, "");
    memset(num1, 0, MAX_NUM);

    num2 = 0;
    operate = 0;
}

void process_backspace(void)
{
    int i = strlen(num1);

    if (i > 0)
        num1[i-1] = 0;

    i = strlen(num1);
    if (i == 0)
        lv_label_set_text(label1, "0");
    else
        lv_label_set_text(label1, num1);
}

void process_calculate_plus_minus()
{
    int len = strlen(num1);
    printf("len = %d\n", len);

    if (num1[0] == '-')
    {
        for (int i = 0; i < len - 1; i++)
            num1[i] = num1[i + 1];
        num1[len - 1] = 0;

        printf("num1[] = %s\n", num1);
    }
    else {
        if (len < MAX_NUM)
        {
            for (int i = 0; i < len; i++)
                num1[len - i] = num1[len - i - 1];
            num1[0] = '-';
            printf("num1[] = %s\n", num1);
        }
        else {
            printf("Over MAX_NUM bits!");
        }
    }

    lv_label_set_text(label1, num1);
}


static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED){
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        const char * txt = lv_btnmatrix_get_btn_text(obj, id);

        printf("%s was pressed, id=%d\n", txt, id);

        switch(id)
        {
            case 0:
                process_clear();
                break;

            case 1:
                process_backspace();
                break;

            case 2:
            case 3:
            case 4:
                process_calculate_type1(id);
                break;

            case 5:
            case 9:
            case 13:
            case 17:
                process_calculate_type2(id);
                break;

            case 18:
                process_calculate_plus_minus();
                break;

            case 21:
                process_calculate_equal();
                break;

            default:
                process_num(txt);
                break;
        }
    }
}

void lv_buttonmatrix_1(void)
{
    lv_obj_t * btnm1 = lv_buttonmatrix_create(lv_screen_active());
    lv_buttonmatrix_set_map(btnm1, btnm_map);

    lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 30);
    lv_obj_set_size(btnm1, 240, 260);

    // this line commented has the same result as not commenting it, because of the next line
    // lv_buttonmatrix_set_button_width(btnm1, 0, 1);
    lv_buttonmatrix_set_button_width(btnm1, 1, 2);

    lv_buttonmatrix_set_button_ctrl(btnm1, 21, LV_BTNMATRIX_CTRL_CHECKED);

    lv_obj_set_style_bg_color(btnm1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btnm1, lv_color_hex(0x3E3A3A), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btnm1, lv_color_hex(0x0000FF), LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(btnm1, lv_color_hex(0xFFFFFF), LV_PART_ITEMS|LV_STATE_DEFAULT);

    //lv_obj_set_style_outline_color(btnm1, lv_color_hex(0xff0000), LV_PART_MAIN);
    lv_obj_set_style_outline_width(btnm1, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(btnm1, 0, LV_PART_MAIN);
    //lv_obj_set_style_outline_pad(btnm1, 10, LV_PART_MAIN);

    lv_obj_set_style_pad_all(btnm1, 3, LV_PART_MAIN);
    lv_obj_set_style_pad_row(btnm1, 1, LV_PART_MAIN);
    lv_obj_set_style_pad_column(btnm1, 2, LV_PART_MAIN);

    lv_obj_set_style_shadow_ofs_x(btnm1, 0, LV_PART_ITEMS);
    lv_obj_set_style_shadow_ofs_y(btnm1, 0, LV_PART_ITEMS);

    lv_obj_set_style_radius(btnm1, 4, LV_PART_ITEMS);

    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);

    /*--------------------------label1-------------------------------*/

    label1 = lv_label_create(lv_screen_active());
    lv_obj_set_size(label1, 240, 30);
    lv_label_set_text(label1, "0");

    lv_obj_set_style_text_color(label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    //lv_obj_set_style_border_color(label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    //lv_obj_set_style_border_width(label1, 1, LV_PART_MAIN);

    lv_obj_align_to(label1, btnm1, LV_ALIGN_OUT_TOP_MID, -10, -25);
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_22, 0);

    /*--------------------------label2-------------------------------*/

    label2 = lv_label_create(lv_screen_active());
    lv_obj_set_size(label2, 240, 30);
    lv_label_set_text(label2, "");

    lv_obj_set_style_text_color(label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    //lv_obj_set_style_border_color(label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    //lv_obj_set_style_border_width(label2, 1, LV_PART_MAIN);

    lv_obj_align_to(label2, label1, LV_ALIGN_OUT_TOP_MID, 0, 0);
    lv_obj_set_style_text_align(label2, LV_TEXT_ALIGN_RIGHT, 0);

    lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);
 }

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL for LVGL*/
    lv_display_t * display = lv_windows_create_display(title, 300, 400, 100, FALSE, FALSE);
    lv_windows_acquire_pointer_indev(display);

    lv_buttonmatrix_1();

    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5000);       /*Just to let the system breath*/
    }
    return 0;
}
