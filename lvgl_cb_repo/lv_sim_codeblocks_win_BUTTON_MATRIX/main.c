
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

static void keyboard_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

    lv_obj_t * textarea = lv_event_get_user_data(e);
    if (strcmp(txt, "abc") == 0){
        lv_textarea_add_text(textarea, "Change to abc lower mode!");
    }

    if (strcmp(txt, "ABC") == 0){
        lv_textarea_set_text(textarea, "Change to ABC upper mode!");
    }
}

static void text_area_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

void my_keyboard(void)
{
    /*Create a keyboard to use it with an of the text areas*/
    lv_obj_t * kb = lv_keyboard_create(lv_screen_active());

    /*Create a text area. The keyboard will write here*/
    lv_obj_t * ta = lv_textarea_create(lv_screen_active());
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 0);
    lv_textarea_set_placeholder_text(ta, "Please input user name!");

    lv_keyboard_set_textarea(kb, ta);

    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_password_mode(ta, true);
    lv_textarea_set_max_length(ta, 20);

    lv_obj_add_event_cb(kb, keyboard_event_cb, LV_EVENT_PRESSED, ta);
    lv_obj_add_event_cb(ta, text_area_event_cb, LV_EVENT_ALL, kb);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL for LVGL*/
    lv_display_t * display = lv_windows_create_display(title, 640, 360, 100, FALSE, FALSE);
    lv_windows_acquire_pointer_indev(display);

    my_keyboard();

    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5000);       /*Just to let the system breath*/
    }
    return 0;
}
