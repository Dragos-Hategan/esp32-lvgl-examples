
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

 void my_label01_function(void)
 {
    lv_obj_t * label1 = lv_label_create(lv_screen_active());

    int user_num = 2;
    lv_label_set_text_fmt(label1, "%d user", user_num);

    lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 0, 0);
 }

void my_label02_function(void)
 {
    lv_obj_t * label1 = lv_label_create(lv_screen_active());
    lv_obj_set_style_text_color(label1, lv_color_hex(0x0000FF), 0);
    lv_label_set_text(label1, "Hello, World!");
 }

 void my_label03_function(void)
 {
    lv_obj_t * label1 = lv_label_create(lv_screen_active());
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_42, 0);
    lv_label_set_text(label1, "Hi There!");
 }

 void my_label04_function(void)
 {
    lv_obj_t * label1 = lv_label_create(lv_screen_active());
    lv_obj_set_style_text_font(label1, &StoryScript_28, 0);
    lv_label_set_text(label1, "Nice Font TXT");
 }

  void my_label05_function(void)
 {
    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_style_set_text_color(&label_style, lv_color_hex(0x0000FF));
    lv_style_set_text_font(&label_style, &StoryScript_28);

    lv_obj_t * label1 = lv_label_create(lv_screen_active());
    lv_label_set_text(label1, "Nice Font TXT");

    lv_obj_t * label2 = lv_label_create(lv_screen_active());
    lv_label_set_text(label2, "Hello Buddy");
    lv_obj_align_to(label2, label1, LV_ALIGN_CENTER, 25, 25);

    static lv_style_t label_style2;
    lv_style_init(&label_style2);
    lv_style_set_text_color(&label_style2, lv_color_hex(0xFF0000));
    lv_obj_t * label3 = lv_label_create(lv_screen_active());
    lv_label_set_text(label3, "My name is Salam");
    lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_style(label1, &label_style, LV_PART_MAIN);
    lv_obj_add_style(label2, &label_style, LV_PART_MAIN);
    lv_obj_add_style(label3, &label_style2, LV_PART_MAIN);
 }

 void my_label06_function(void)
 {
    lv_obj_t * label1 = lv_label_create(lv_screen_active());

    /*
    lv_obj_set_width(label1, 250);
    lv_obj_set_height(label1, 100);
    */
    lv_obj_set_size(label1, 250, 100); // same as the previous 2 lines

    lv_label_set_text(label1,
                                "This is a long string.\r"
                                "It contains multiple newlines."
                                "It is cool!");
    lv_label_set_long_mode(label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // LV_LABEL_LONG_WRAP
    // LV_LABEL_LONG_DOT
    // LV_LABEL_LONG_SCROLL
    // LV_LABEL_LONG_SCROLL_CIRCULAR
    // LV_LABEL_LONG_CLIP
 }

 void my_label07_function(void)
 {
    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj, 200, 100);
    lv_obj_center(obj);

    lv_obj_t * label = lv_label_create(obj);
    lv_label_set_text(label,
                      "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
                      "Etiam dictum, tortor vestibulum lacinia laoreet, mi neque consectetur neque, vel mattis odio dolor egestas ligula. \n"
                      "Sed vestibulum sapien nulla, id convallis ex porttitor nec. \n"
                      "Duis et massa eu libero accumsan faucibus a in arcu. \n"
                      "Ut pulvinar odio lorem, vel tempus turpis condimentum quis. Nam consectetur condimentum sem in auctor. \n"
                      "Sed nisl augue, venenatis in blandit et, gravida ac tortor. \n"
                      "Etiam dapibus elementum suscipit. \n"
                      "Proin mollis sollicitudin convallis. \n"
                      "Integer dapibus tempus arcu nec viverra. \n"
                      "Donec molestie nulla enim, eu interdum velit placerat quis. \n"
                      "Donec id efficitur risus, at molestie turpis. \n"
                      "Suspendisse vestibulum consectetur nunc ut commodo. \n"
                      "Fusce molestie rhoncus nisi sit amet tincidunt. \n"
                      "Suspendisse a nunc ut magna ornare volutpat.");
 }

 static void my_event_cb(lv_event_t *event)
 {
     printf("Clicked!\n");
 }

 void my_label08_function(void)
 {
    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj, 200, 100);
    lv_obj_center(obj);

    lv_obj_t * label = lv_label_create(obj);
    lv_label_set_text(label, "Hello World!!\n");

    lv_obj_add_event_cb(obj, my_event_cb, LV_EVENT_CLICKED, NULL);
    //lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE);
 }


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL for LVGL*/
    lv_display_t * display = lv_windows_create_display(title, 1280, 720, 100, FALSE, FALSE);
    lv_windows_acquire_pointer_indev(display);

    //my_label01_function();
    //my_label02_function();
    //my_label03_function();
    //my_label04_function();
    //my_label05_function();
    //my_label06_function();
    //my_label07_function();
    my_label08_function();

    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5000);       /*Just to let the system breath*/
    }
    return 0;
}
