
#include "../../lv_examples.h"
#include "main.h"
#include "stm32746g_discovery.h"
#if LV_USE_DROPDOWN && LV_BUILD_EXAMPLES

extern float average_flow;
extern float average_flow1;
static void event_handler_reset_btn(lv_event_t * e);
void toggle_image_visibility(void);

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    void* user_data = lv_event_get_user_data(e); // Get the user data (the ID we passed)
    int id = (int) user_data; // Cast the user data to an integer ID
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Option: %s", buf);

        if(id == 1) {
                   // Valve 1 dropdown selected
                   if(strcmp(buf, "On") == 0) {
                       // Valve 1 is ON, set RA5 pin
                       LV_LOG_USER("Valve 1 is ON. Setting RA5 pin...");
                       HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);   // Set PI1 high
                       HAL_Delay(50);

                   }
                   else if(strcmp(buf, "Off") == 0) {
                       // Valve 1 is OFF, reset RA5 pin
                       LV_LOG_USER("Valve 1 is OFF. Resetting RA5 pin...");
                       HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);   // Set PI1 high
                       HAL_Delay(50);
                   }
               }

        else if(id == 2)
        {
                   // Valve 2 dropdown selected
                   if(strcmp(buf, "On") == 0) {
                       // Valve 2 is ON, set RA6 pin
                       LV_LOG_USER("Valve 2 is ON. Setting RA6 pin...");
                       HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET); //VALVE 2 SET

                   }
                   else if(strcmp(buf, "Off") == 0) {
                       // Valve 2 is OFF, reset RA6 pin
                       LV_LOG_USER("Valve 2 is OFF. Resetting RA6 pin...");
                       HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);//VALVE 2 RESET
                   }
               }

//        else if(id == 3) {
//                   // BYPASS dropdown selected
//                   if(strcmp(buf, "On") == 0) {
//                       // BYPASS is ON
//                       LV_LOG_USER("BYPASS is ON. Changing parameters...");
//                       // Handle BYPASS ON action (e.g., enable bypass functionality)
//                   }
//                   else if(strcmp(buf, "Off") == 0) {
//                       // BYPASS is OFF
//                       LV_LOG_USER("BYPASS is OFF. Resetting parameters...");




}
}


static void event_handler_reset_btn(lv_event_t * e)
{

    lv_event_code_t reset_event = lv_event_get_code(e);


    if (reset_event == LV_EVENT_CLICKED) {

//        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
//        HAL_Delay(100);
    	 NVIC_SystemReset();


    }

}


void lv_example_dropdown_1(void)
{



	 lv_style_t style;
	lv_style_init(&style);
    /* Create a dropdown with valve and parameter options */
    lv_obj_t * dd = lv_dropdown_create(lv_scr_act());
    lv_dropdown_set_options(dd, "On\n"
                                "Off");


    lv_obj_t * dd1 = lv_dropdown_create(lv_scr_act());
    lv_dropdown_set_options(dd1, "On\n"
                                    "Off");

//    lv_obj_t * dd2 = lv_dropdown_create(lv_scr_act());
//    lv_dropdown_set_options(dd2, "On\n"
//                            "Off");
//    lv_obj_t *dd3 = lv_label_create(lv_scr_act()); // Create a label on the active screen
//    lv_label_set_text(dd3, "PRESS");

//    lv_obj_t *dd4 = lv_label_create(lv_scr_act()); // Create a label on the active screen
//    lv_label_set_text(dd4, "RESET");

    lv_obj_t * reset_btn = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(reset_btn, event_handler_reset_btn, LV_EVENT_CLICKED, NULL);  // Attach the event handler
    lv_obj_align(reset_btn, LV_ALIGN_LEFT_MID, 140, 106); // Align dropdown next to the label at (X + 60)
    lv_obj_set_size(reset_btn, 70, 25);
    lv_obj_add_style(reset_btn, &style, LV_PART_MAIN); // Apply style to the label

    // Create a label on the button
    lv_obj_t * reset_lable = lv_label_create(reset_btn);
    lv_label_set_text(reset_lable, "RESET");
    lv_obj_center(reset_lable);
    lv_obj_set_style_bg_color(reset_btn, lv_color_hex(0xFF0000), LV_PART_MAIN);


    //dropdown 1

       lv_obj_set_style_pad_left(dd, 7, 0);  // Left padding for options
       lv_obj_set_style_pad_right(dd, 7, 0); // Right padding for options
       lv_obj_set_style_pad_top(dd, 0, 0);   // Top padding for options
       lv_obj_set_style_pad_bottom(dd, 7, 0); // Bottom padding for options


    lv_obj_align(dd, LV_ALIGN_LEFT_MID, 140, -30); // Align dropdown next to the label at (X + 60)
    lv_obj_set_size(dd, 70, 25);
    lv_obj_add_event_cb(dd, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(dd, event_handler, LV_EVENT_ALL, (void*) 1); // Pass unique ID for Valve 1
    lv_dropdown_set_selected(dd, 1);

    //dropdown 2

    lv_obj_set_style_pad_left(dd1, 7, 0);  // Left padding for options
           lv_obj_set_style_pad_right(dd1, 7, 0); // Right padding for options
           lv_obj_set_style_pad_top(dd1, 0, 0);   // Top padding for options
           lv_obj_set_style_pad_bottom(dd1, 7, 0); // Bottom padding for options


        lv_obj_align(dd1, LV_ALIGN_LEFT_MID, 140, 4); // Align dropdown next to the label at (X + 60)
        lv_obj_set_size(dd1, 70, 25);
        lv_obj_add_event_cb(dd1, event_handler, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(dd1, event_handler, LV_EVENT_ALL, (void*) 2);
        lv_dropdown_set_selected(dd1, 1);
  //dropdown 3

//        lv_obj_set_style_pad_left(dd2, 7, 0);  // Left padding for options
//        lv_obj_set_style_pad_right(dd2, 7, 0); // Right padding for options
//        lv_obj_set_style_pad_top(dd2, 0, 0);   // Top padding for options
//        lv_obj_set_style_pad_bottom(dd2, 7, 0); // Bottom padding for options

//        lv_dropdown_set_selected(dd2, 1);

//       lv_obj_align(dd2, LV_ALIGN_LEFT_MID, 140, 38); // Align dropdown next to the label at (X + 60)
//       lv_obj_set_size(dd2, 70, 25);
//       lv_obj_add_event_cb(dd2, event_handler, LV_EVENT_ALL, NULL);
//       lv_obj_add_event_cb(dd2, event_handler, LV_EVENT_ALL, (void*) 3);
//       //dropdown 4

//      lv_obj_align(dd3, LV_ALIGN_LEFT_MID, 150, 60); // Align dropdown next to the label at (X + 60)
//      lv_obj_set_size(dd3, 70, 25);
//      lv_obj_add_style(dd3, &style, LV_PART_MAIN); // Apply style to the label
     // lv_obj_add_event_cb(dd3, event_handler, LV_EVENT_ALL, NULL);

      //dropdown 4
//      lv_obj_align(dd4, LV_ALIGN_LEFT_MID, 150, 106); // Align dropdown next to the label at (X + 60)
//      lv_obj_set_size(dd4, 70, 25);
//      lv_obj_add_style(dd4, &style, LV_PART_MAIN); // Apply style to the label

//      lv_obj_t *label = lv_label_create(lv_scr_act()); // Create a label on the active screen
//      lv_label_set_text(label, "Valve 1"); // Set label text
//      lv_obj_align(label, LV_ALIGN_TOP_LEFT, 60, 98); // Align to top-left corner
//      lv_obj_add_style(label, &style, LV_PART_MAIN); // Apply style to the label
}

void show_text(void)
{
	lv_obj_t * cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 210, 180); // Adjust the size as needed
    lv_obj_align(cont, LV_ALIGN_TOP_LEFT, 20, 80); // Align the container to the top-left corner
    lv_obj_set_style_border_width(cont, 2, LV_PART_MAIN); // Set border width
    lv_obj_set_style_border_color(cont, lv_color_hex(0x00000F), LV_PART_MAIN); // Set border color (blue)
    lv_obj_set_style_line_rounded(cont, 10, LV_PART_MAIN); // Rounded corners (optional)

    //lv_obj_set_style_pad_all(cont, 10, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(lv_scr_act()); // Create a label on the active screen
    lv_obj_t *label1 = lv_label_create(lv_scr_act());
    lv_obj_t *label2 = lv_label_create(lv_scr_act());
    lv_obj_t *label3 = lv_label_create(lv_scr_act());
    lv_obj_t *label4 = lv_label_create(lv_scr_act());

    lv_obj_t *label5 = lv_label_create(lv_scr_act());


    lv_label_set_text(label, "Valve 1"); // Set label text
    lv_label_set_text(label1, "Valve 2"); // Set label text
    lv_label_set_text(label2, "BYPASS"); // Set label text
    lv_label_set_text(label3, "SETUP"); // Set label text
    lv_label_set_text(label4, "Fault"); // Set label text

    lv_label_set_text(label5, "COOL CONTROL - 2"); // Set label text
    lv_obj_set_style_text_color(label5, lv_color_hex(0xD2691E), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 60, 97); // Align to top-left corner
    lv_obj_align(label1, LV_ALIGN_LEFT_MID, 60, 3); // Align to top-left corner
    lv_obj_align(label2, LV_ALIGN_LEFT_MID, 60, 38); // Align to top-left corner
    lv_obj_align(label3, LV_ALIGN_LEFT_MID, 60, 73); // Align to top-left corner
    lv_obj_align(label4, LV_ALIGN_LEFT_MID, 60, 103); // Align to top-left corner

    lv_obj_align(label5, LV_ALIGN_TOP_MID, 60, 30); // Align to top-left corner

//    lv_style_t style;
//    lv_style_init(&style);
//    lv_style_set_text_color(&style, lv_color_hex(0xFF0000)); // Set text color to red
//    lv_style_set_text_font(&style, &lv_font_montserrat_16); // Use a custom font
//
//    lv_obj_add_style(label, &style, LV_PART_MAIN); // Apply style to the label
//    lv_obj_add_style(label1, &style, LV_PART_MAIN); // Apply style to the label
//    lv_obj_add_style(label2, &style, LV_PART_MAIN); // Apply style to the label
//    lv_obj_add_style(label3, &style, LV_PART_MAIN); // Apply style to the label
//    lv_obj_add_style(label4, &style, LV_PART_MAIN); // Apply style to the label
//    lv_obj_add_style(label5, &style, LV_PART_MAIN); // Apply style to the label
}

#endif
