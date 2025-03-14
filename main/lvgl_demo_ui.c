/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/widgets/extra/meter.html#simple-meter

#include "lvgl.h"
#include "esp_log.h"
#include "stdio.h"
#include <string.h>

static lv_obj_t *meter;
static lv_obj_t * ubtn;
static lv_obj_t * dbtn;
static lv_disp_rot_t rotation = LV_DISP_ROT_NONE;
static int startNumber = 0;
static int mainNumber = 0;
char* str;
lv_obj_t * label;
lv_obj_t * myscr;

lv_style_t style_btn_transp;                          // Declare a new style

lv_disp_t * thisdisp;

void example_lvgl_page2();

// static void set_value(void *indic, int32_t v)
// {
//     lv_meter_set_indicator_end_value(meter, indic, v);
// }

// static void btn_cb(lv_event_t * e)
// {
//     lv_disp_t *disp = lv_event_get_user_data(e);
//     rotation++;
//     if (rotation > LV_DISP_ROT_270) {
//         rotation = LV_DISP_ROT_NONE;
//     }
//     lv_disp_set_rotation(disp, rotation);
// }

static void update_display()
{
    int length = snprintf( NULL, 0, "%d", mainNumber );
    str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", mainNumber );
    lv_label_set_text(label, str);
    free(str);
}

static void btn_up_cb(lv_event_t * e)
{
    mainNumber++;
    update_display();
}

static void btn_down_cb(lv_event_t * e)
{
    mainNumber--;
    update_display();
    
}

void create_static_label(lv_obj_t *scr, int mynum, int offset){

    int mylength = snprintf( NULL, 0, "%d", mynum );
    char* mystr = malloc( mylength + 1 );
    snprintf( mystr, mylength + 1, "%d", mynum );
    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label2 = lv_label_create(scr);
    lv_obj_set_style_text_font(label2,&lv_font_montserrat_48,0);
    lv_label_set_text(label2, mystr);
    lv_obj_set_style_text_color(scr, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, offset);
    free(mystr);
}

void create_clickable_label(lv_obj_t *scr, int mynum, int offset, lv_event_cb_t cb, lv_disp_t * disp){

    int mylength = snprintf( NULL, 0, "%d", mynum );
    char* mystr = malloc( mylength + 1 );
    snprintf( mystr, mylength + 1, "%d", mynum );
    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label2 = lv_label_create(scr);
    lv_obj_set_style_text_font(label2,&lv_font_montserrat_48,0);
    lv_label_set_text(label2, mystr);
    lv_obj_set_style_text_color(scr, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, offset);
    lv_obj_add_flag(label2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(label2, cb, LV_EVENT_CLICKED, disp);
    free(mystr);
}

void create_clickable_text_label(lv_obj_t *scr, char* text, int offset, lv_event_cb_t cb, lv_disp_t * disp){

    /*Create a white label, set its text and align it to the center*/

    lv_obj_t * label2 = lv_label_create(scr);
    lv_obj_set_style_text_font(label2,&lv_font_montserrat_48,0);
    lv_label_set_text(label2, text);
    lv_obj_set_style_text_color(scr, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, offset);
    lv_obj_add_flag(label2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(label2, cb, LV_EVENT_CLICKED, disp);
}

void example_lvgl_demo_ui(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x003a57), LV_PART_MAIN);



    int length = snprintf( NULL, 0, "%d", mainNumber );
    str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", mainNumber );
    /*Create a white label, set its text and align it to the center*/
    label = lv_label_create(scr);
    lv_obj_set_style_text_font(label,&lv_font_montserrat_48,0);
    lv_label_set_text(label, str);
    lv_obj_set_style_text_color(scr, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    free(str);
    
    ubtn = lv_btn_create(scr);
    lv_obj_t * lbl = lv_label_create(ubtn);
    lv_label_set_text_static(lbl, LV_SYMBOL_UP);
    lv_obj_align(ubtn, LV_ALIGN_TOP_MID, 0, 0);
    /*Button event*/
    lv_obj_add_event_cb(ubtn, btn_up_cb, LV_EVENT_CLICKED, disp);

    dbtn = lv_btn_create(scr);
    lv_obj_t * dlbl = lv_label_create(dbtn);
    lv_label_set_text_static(dlbl, LV_SYMBOL_DOWN);
    lv_obj_align(dbtn, LV_ALIGN_BOTTOM_MID, 0, 0);
    /*Button event*/
    lv_obj_add_event_cb(dbtn, btn_down_cb, LV_EVENT_CLICKED, disp);

    
}
static void btn_reset_cb(lv_event_t * e)
{
    mainNumber = startNumber;
    example_lvgl_page2();
}

static void btn_resume_cb(lv_event_t * e)
{
    example_lvgl_page2();
}

void example_lvgl_page3()
{
    lv_obj_clean(lv_scr_act());
    lv_obj_t * scr = myscr;

    create_clickable_text_label(scr, "reset", -40, btn_reset_cb, thisdisp);
    create_clickable_text_label(scr, "resume", 40, btn_resume_cb, thisdisp);
}

static void btn_hold_cb(lv_event_t * e)
{
    example_lvgl_page3();
}

void example_lvgl_page2()
{
    lv_obj_clean(lv_scr_act());
    lv_obj_t * scr = myscr;
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x003a57), LV_PART_MAIN);

    int length = snprintf( NULL, 0, "%d", mainNumber );
    str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", mainNumber );
    /*Create a white label, set its text and align it to the center*/
    label = lv_label_create(scr);
    lv_obj_set_style_text_font(label,&lv_font_montserrat_48,0);
    lv_label_set_text(label, str);
    lv_obj_set_style_text_color(scr, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(label, btn_hold_cb, LV_EVENT_LONG_PRESSED, thisdisp);
    free(str);
    
    ubtn = lv_btn_create(scr);
    lv_obj_t * lbl = lv_label_create(ubtn);
    lv_label_set_text_static(lbl, LV_SYMBOL_UP);
    lv_obj_align(ubtn, LV_ALIGN_TOP_MID, 0, 0);
    /*Button event*/
    lv_obj_add_event_cb(ubtn, btn_up_cb, LV_EVENT_CLICKED, thisdisp);

    dbtn = lv_btn_create(scr);
    lv_obj_t * dlbl = lv_label_create(dbtn);
    lv_label_set_text_static(dlbl, LV_SYMBOL_DOWN);
    lv_obj_align(dbtn, LV_ALIGN_BOTTOM_MID, 0, 0);
    /*Button event*/
    lv_obj_add_event_cb(dbtn, btn_down_cb, LV_EVENT_CLICKED, thisdisp);

}

static void btn_20life_cb(lv_event_t * e)
{
    startNumber = 20;
    mainNumber = 20;
    example_lvgl_page2();
}

static void btn_40life_cb(lv_event_t * e)
{
    startNumber = 40;
    mainNumber = 40;
    example_lvgl_page2();
}

void example_lvgl_entry(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    thisdisp = disp;
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x003a57), LV_PART_MAIN);

    myscr = scr;

    create_clickable_label(scr, 40, -40, btn_40life_cb, disp);
    create_clickable_label(scr, 20, 40, btn_20life_cb, disp);

}

// lv_obj_t *scr = lv_disp_get_scr_act(disp);
    // meter = lv_meter_create(scr);
    // lv_obj_center(meter);
    // lv_obj_set_size(meter, 200, 200);

    // lv_obj_set_style_bg_color(scr, lv_color_hex(0x003a57), LV_PART_MAIN);

    // /*Add a scale first*/
    // lv_meter_scale_t *scale = lv_meter_add_scale(meter);
    // lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    // lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);

    // lv_meter_indicator_t *indic;

    // ESP_LOGI("lvgl", "Add a scale first");

    // /*Add a blue arc to the start*/
    // indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    // lv_meter_set_indicator_start_value(meter, indic, 0);
    // lv_meter_set_indicator_end_value(meter, indic, 20);

    // /*Make the tick lines blue at the start of the scale*/
    // indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    // lv_meter_set_indicator_start_value(meter, indic, 0);
    // lv_meter_set_indicator_end_value(meter, indic, 40);

    // /*Add a red arc to the end*/
    // indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    // lv_meter_set_indicator_start_value(meter, indic, 80);
    // lv_meter_set_indicator_end_value(meter, indic, 100);

    // /*Make the tick lines red at the end of the scale*/
    // indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    // lv_meter_set_indicator_start_value(meter, indic, 60);
    // lv_meter_set_indicator_end_value(meter, indic, 100);

    // /*Add a needle line indicator*/
    // indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_CYAN), -20);

    // btn = lv_btn_create(scr);
    // lv_obj_t * lbl = lv_label_create(btn);
    // lv_label_set_text_static(lbl, LV_SYMBOL_REFRESH" ROTATE");
    // lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 30, -30);
    // /*Button event*/
    // lv_obj_add_event_cb(btn, btn_cb, LV_EVENT_CLICKED, disp);

    // /*Create an animation to set the value*/
    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_exec_cb(&a, set_value);
    // lv_anim_set_var(&a, indic);
    // lv_anim_set_values(&a, 0, 100);
    // lv_anim_set_time(&a, 2000);
    // lv_anim_set_repeat_delay(&a, 100);
    // lv_anim_set_playback_time(&a, 100);
    // lv_anim_set_playback_delay(&a, 1000);
    // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_start(&a);