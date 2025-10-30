
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

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int iClick = 0;
int iData[] = {55, 44, 66, 33, 53, 12};

struct Btn_Info_t{
    lv_obj_t * label;
    int btn_id;
}Btn_Info_1, Btn_Info_2;

 static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    struct Btn_Info_t * pData = lv_event_get_user_data(e);

    if(code == LV_EVENT_CLICKED) {
        lv_label_set_text_fmt(pData->label, "Clicked by Btn %d\n", pData->btn_id);
    }
}

 void my_button1(void)
{
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    /*----------------------------------------------------------------------*/

    Btn_Info_1.label = label;
    Btn_Info_1.btn_id = 1;

    lv_obj_t * btn1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, &Btn_Info_1);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, 50);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    lv_obj_t * label1;
    label1 = lv_label_create(btn1);
    lv_label_set_text(label1, "Button1");
    lv_obj_center(label1);

    /*----------------------------------------------------------------------*/

    Btn_Info_2.label = label;
    Btn_Info_2.btn_id = 2;

    lv_obj_t * btn2 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, &Btn_Info_2);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, -50);
    lv_obj_remove_flag(btn2, LV_OBJ_FLAG_PRESS_LOCK);

    lv_obj_t * label2;
    label2 = lv_label_create(btn2);
    lv_label_set_text(label2, "Button2");
    lv_obj_center(label2);
}

 static void event_handler2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);

    static int cx = 0, cy = 0;
    const int step = 20;

    if(code == LV_EVENT_CLICKED) {
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        char * txt = lv_label_get_text(label);

        printf("%s %d %d\n", txt, cx, cy);

        if (cx == 0 && cy == 0) {
            cy -= step;
        } else if (cx == 0 && cy == -step) {
            cx -= step; cy += step;
        } else if (cx == -step && cy == 0) {
            cx += step; cy += step;
        } else if (cx == 0 && cy == step) {
            cx += step; cy -= step;
        } else if (cx == step && cy == 0) {
            cx -= step; cy -= step;
        }

        lv_obj_align(btn, LV_ALIGN_CENTER, cx, cy);
    }
}

 void my_button2(void)
{
    lv_obj_t * btn1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn1, event_handler2, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    lv_obj_t * label1;
    label1 = lv_label_create(btn1);
    lv_label_set_text(label1, "Button1");
    lv_obj_center(label1);
}

int i = 0;

static void event_cb(lv_event_t * e)
{
    /*The original target of the event. Can be the buttons or the container*/
    lv_obj_t * target = lv_event_get_target(e);

    /*The current target is always the container as the event is added to it*/
    lv_obj_t * cont = lv_event_get_current_target(e);

    printf("target = %d, cont = %d \n", target, cont);

    if(target == cont){
        for (int j = 0; j < 3; j++){
            lv_obj_t * btn = lv_obj_get_child(target, j);
            lv_obj_center(btn);
        }
    }else{
        lv_obj_move_to(target, i * 80, 0);
        i++;
        if (i == 3){
            i = 0;
        }
    }
}

/**
 * Demonstrate event bubbling
 */
void my_button3_event_get_current_target(void)
{
    uint32_t i;
    for(i = 0; i < 3; i++) {
        lv_obj_t * btn = lv_button_create(lv_screen_active());
        lv_obj_set_size(btn, 50, 50);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_center(btn);

        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "%"LV_PRIu32, i+1);
    }

    lv_obj_add_event_cb(lv_screen_active(), event_cb, LV_EVENT_CLICKED, NULL);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL for LVGL*/
    lv_display_t * display = lv_windows_create_display(title, 1280, 720, 100, FALSE, FALSE);
    lv_windows_acquire_pointer_indev(display);

    //my_button1();
    //my_button2();
    my_button3_event_get_current_target();

    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5000);       /*Just to let the system breath*/
    }
    return 0;
}
