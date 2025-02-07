#include "../lv_examples.h"
#if LV_BUILD_EXAMPLES && LV_USE_IMG

/**
 * Using the Size, Position and Padding style properties
 */
void lv_example_style_1(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_width(&style, 150);
    lv_style_set_height(&style, LV_SIZE_CONTENT);

    lv_style_set_pad_ver(&style, 20);
    lv_style_set_pad_left(&style, 5);

    lv_style_set_x(&style, lv_pct(50));
    lv_style_set_y(&style, 80);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);

    lv_obj_t * label = lv_label_create(obj);
    lv_label_set_text(label, "Hello");
}
//void rgb_mixer_create_ui(void)
//{
//    /* Create an image object */
//    lv_obj_t* img = lv_img_create(lv_scr_act());
//    lv_obj_add_flag(img, LV_OBJ_FLAG_IGNORE_LAYOUT);
//    //lv_img_set_src(img, &beacker_map); // Set the image source
//    lv_obj_set_size(img, 130, 50);   // Optional: Set the size to 40x40 pixels if resizing is needed
//    lv_obj_align(img, LV_ALIGN_TOP_LEFT, 25, 25); // Align the image to the top-left corner with padding
//    //lv_img_set_src(img,"D:\2\Projects\003_RGB_Mixer\2_32F746GDISCOVERY\Debug\lvgl\src\widgets\assets\beacker.png");
//}
#endif
