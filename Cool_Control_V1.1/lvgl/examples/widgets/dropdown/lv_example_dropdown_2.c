#include "../../lv_examples.h"
#include "main.h"
#include "stdint.h"
#include<stdio.h>

#include <string.h>
#if LV_USE_DROPDOWN && LV_USE_BTN && LV_BUILD_EXAMPLES

extern  TIM_HandleTypeDef htim2;

extern float temp1;
extern float temp2;
extern float frequency_TIM13;
extern float frequency_TIM14;
extern uint8_t lvgl_flag;
extern float average_flow;
extern float average_flow1;

extern float GPM;
extern float GPM1;
lv_obj_t *label1, *label2, *label3, *label4;




extern char flow_warning_flag;

extern char flow_fault_flag;
extern char slow_leak_flag;
extern char slow_delay_flag;
extern char temp_warning_flag;
extern char temp_fault_flag;
extern char tempdiff_warning_flag;
extern char tempdiff_fault_flag;
extern int  spinbox_stabilization_Delay_flag;
extern int FloWarning_val;
// Declare global variables
lv_obj_t * main_screen = NULL;
lv_obj_t * tabview_screen = NULL;
static lv_obj_t *active_spinbox = NULL;

extern int mode;

int celcious_flag=1;
int fahrenheit_flag=1;
int fahrenheit_flag1;
int Normal_Flag;
int Open_Flag;
int Presize_Flag;

#define LPM_TO_GPM 0.264172
#define CELSIUS_TO_FAHRENHEIT(c) ((c * 9.0 / 5.0) + 32.0)

extern uint8_t lvgl_flag;


//spinbox variables

//for flow

volatile int flow_warning_value;
volatile int flow_fault_value;
 float slow_leak_difference_value;
volatile int  slow_leak_delay_value;
volatile int Stabilization_delay=5;



//for temp setting value reading

int outlet_temp1;
int  outlet_temp;
int differential_temp1;
int  differential_temp;
float thermal_load1;
float thermal_load;
int coolant_density;
int coolant_heat_capacity;
int heatload_threshold;

#define SPINBOX_FLOW_WARNING_ID 1
#define SPINBOX_FLOW_FAULT_ID 2
#define SPINBOX_SLOW_LEAK_DIFFERENCE_ID 3


//for temp

static lv_obj_t *spinbox_outlet_temp;
static lv_obj_t *spinbox_diff_temp;

static lv_obj_t * spinbox_outlet_temp_FAULT;
static lv_obj_t *spinbox_diff_temp_FAULT;

//for flow setting

static lv_obj_t * spinbox_Flow_Warning=NULL;
static lv_obj_t * spinbox_Flow_Fault=NULL;
static lv_obj_t * spinbox_Slow_Leak_Difference=NULL;
static lv_obj_t * spinbox_Slow_leak_Delay;
static lv_obj_t  *spinbox_stabilization_Delay;

extern int server_flow_fault_flag;
extern int server_flow_warning_flag;
extern int server_slow_leak_difference_flag;
extern int  server_slow_leak_delay_flag;
extern int    server_stabilization_flag;
extern int server_outlet_temp_flag;
extern int   server_outlet_temp1_flag;
extern int server_differential_temp_flag;
extern int  server_differential_temp1_flag;

lv_obj_t *last_focused_spinbox = NULL;

// Function prototypes
static void return_event_handler(lv_event_t * e);
static void event_handler(lv_event_t * e);
void lv_example_btn_1(void);
static void increment_temp_event_handler(lv_event_t *e);
static void decrement_temp_event_handler(lv_event_t *e);
static void spinbox_event_handler(lv_event_t *e);
//void show_text1(void);
void show_text1(int value , int value1, int value2, int value3);
static void event_handler_Flow_3_parameters(lv_event_t *e);

void toggle_image_visibility(void);
void toggle_txt_visibility(void) ;
void  update_values();



static void event_handler_Flow_3_parameters(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	void* user_data = lv_event_get_user_data(e); // Get the user data (the ID we passed)
	int id = (int) user_data; // Cast the user data to an integer ID

	if (code == LV_EVENT_VALUE_CHANGED)
	{
		char buf[32];
		lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
		LV_LOG_USER("Option: %s", buf);

		Normal_Flag = 0;
		Open_Flag = 0;
		Presize_Flag = 0;

		if (id == 2)
		{
			// Handle case for id == 2
			if (strcmp(buf, "Normal") == 0)
			{
				Normal_Flag=1;

				LV_LOG_USER("Normal");
			}
			else if (strcmp(buf, "Open") == 0)
			{
				Open_Flag=1;
				LV_LOG_USER("Open");
			}
			else if (strcmp(buf, "Presize") == 0)
			{
				Presize_Flag=1;
				LV_LOG_USER("Presize");
			}
		}
		else if (id == 3)
		{
			// Handle case for id == 3
			if (strcmp(buf, "GPM") == 0)
			{
				LV_LOG_USER("GPM");

				mode = false;
			}
			else if (strcmp(buf, "LPM") == 0)
			{
				mode = true;
				LV_LOG_USER("LPM");
			}
			update_values();
		}

		else if (id==4)
		{
			// Handle case for id == 3
			if (strcmp(buf, "°C") == 0)
			{
				LV_LOG_USER("°C");

				celcious_flag=1;
				//        	                fahrenheit_flag = 0;
				fahrenheit_flag=1;
			}

			else if (strcmp(buf, "°f") == 0)
			{

				LV_LOG_USER("°f");
				//        	                fahrenheit_flag=0;
				fahrenheit_flag=0;
				celcious_flag = 0;
			}
		}

	}
}



static void return_event_handler(lv_event_t * e) {
	lv_scr_load(main_screen);  // Return to the main screen
}
//
//static void spinbox_event_handler(lv_event_t *e) {
//    lv_event_code_t code = lv_event_get_code(e);
//    lv_obj_t *spinbox = lv_event_get_target(e);
////    int id = (int)lv_event_get_user_data(e);
//
//    void* user_data = lv_event_get_user_data(e); // Get the user data (the ID we passed)
//      int id = (int) user_data;
//
//    if (code == LV_EVENT_FOCUSED) {
//        if (last_focused_spinbox != NULL && last_focused_spinbox != spinbox) {
//            lv_obj_set_style_bg_color(last_focused_spinbox, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
//            lv_obj_set_style_border_color(last_focused_spinbox, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
//        }
//
//        lv_obj_set_style_bg_color(spinbox, lv_color_hex(0x00FF00), LV_PART_MAIN);
//        lv_obj_set_style_border_color(spinbox, lv_color_hex(0x00FF00), LV_PART_MAIN);
//
//        last_focused_spinbox = spinbox;
//        active_spinbox = spinbox;
//    }
//
//    if (code == LV_EVENT_VALUE_CHANGED) {
//        int32_t value = lv_spinbox_get_value(active_spinbox);
//
//        switch (id) {
//                        case 1:
//                        	flow_warning_value=  value;
//                            break;
//                        case 2:
//                        	flow_fault_value = value;
//                            break;
//                        case 3:
////                        	slow_leak_difference_value = value*0.1;
//                        	slow_leak_difference_value = value;
//                           break;
//
//                        case 4 :
//						slow_leak_delay_value = value;
//						break;
//
//                        case 5 :
//                        	Stabilization_delay = value;
//					    break;
//
//
//                        case 6 :
//                        	outlet_temp=value;
//                        	break;
//                        case 7 :
//                        	outlet_temp1=value;
//                        	break;
//
//                        case 8 :
//                        	differential_temp=value;
//                        	break;
//
//                        case 9 :
//                        	 differential_temp1=value;
//                        	 break;
//
//
//                    }
//
//    }
//}
//
//// Increment button event handler
//static void increment_temp_event_handler(lv_event_t *e) {
//    if (active_spinbox)
//    {
//        lv_spinbox_increment(active_spinbox);
//        int32_t value = lv_spinbox_get_value(active_spinbox);
//        int id = (int)lv_obj_get_user_data(active_spinbox);
//
//        switch (id) {
//                        case 1:
//                        	flow_warning_value=  value;
//
//                            break;
//                        case 2:
//                        	flow_fault_value = value;
//
//                            break;
//                        case 3:
//                        	slow_leak_difference_value = value;
//
//                            break;
//
//                        case 4 :
////                        	slow_leak_delay_value = value*0.1;
//                        	slow_leak_difference_value = value;
//                        	break;
//
//                        case 5 :
//                        	Stabilization_delay = value;
//					    break;
//
//                        case 6 :
//                        	outlet_temp=value;
//                        	break;
//                        case 7 :
//                        	outlet_temp1=value;
//                        	break;
//
//                        case 8 :
//                        	differential_temp=value;
//                        	break;
//
//                        case 9 :
//                        	 differential_temp1=value;
//                        	 break;
//
//
//
//
//                    }
//    }
//}
//
//// Decrement button event handler
//static void decrement_temp_event_handler(lv_event_t *e) {
//    if (active_spinbox) {
//        lv_spinbox_decrement(active_spinbox);
//        int32_t value = lv_spinbox_get_value(active_spinbox);
//        int id = (int)lv_obj_get_user_data(active_spinbox);
//
//        switch (id) {
//                  case 1:
//                  	flow_warning_value=  value;
//
//                      break;
//                  case 2:
//                  	flow_fault_value = value;
//////
//                      break;
//                  case 3:
////                  	slow_leak_difference_value = value*0.1;
//                  	slow_leak_difference_value = value;
//
//                      break;
//
//                  case 4 :
//                  slow_leak_delay_value = value;
//                  break;
//
//                  case 5 :
//                  	Stabilization_delay = value;
//				    break;
//
//
//                  case 6 :
//                  	outlet_temp=value;
//                  	break;
//                  case 7 :
//                  	outlet_temp1=value;
//
//
//                  case 8 :
//                  	differential_temp=value;
//                  	break;
//
//                  case 9 :
//                  	 differential_temp1=value;
//                  	 break;
//
//
//              }
//    }
//}
//

#include <stdint.h> // For intptr_t

static void spinbox_event_handler(lv_event_t *e) {
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *spinbox = lv_event_get_target(e);

	// Safely retrieve the user data
	int id = (intptr_t)lv_event_get_user_data(e);

	if (code == LV_EVENT_FOCUSED) {
		if (last_focused_spinbox != NULL && last_focused_spinbox != spinbox) {
			lv_obj_set_style_bg_color(last_focused_spinbox, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
			lv_obj_set_style_border_color(last_focused_spinbox, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
		}

		lv_obj_set_style_bg_color(spinbox, lv_color_hex(0x00FF00), LV_PART_MAIN);
		lv_obj_set_style_border_color(spinbox, lv_color_hex(0x00FF00), LV_PART_MAIN);

		last_focused_spinbox = spinbox;
		active_spinbox = spinbox;
	}

	if (code == LV_EVENT_VALUE_CHANGED) {
		int32_t value = lv_spinbox_get_value(spinbox); // Use spinbox instead of active_spinbox

		switch (id) {
		case 1:  flow_warning_value = value; break;
		case 2:  flow_fault_value = value; break;
		case 3:  slow_leak_difference_value = value; break;
		case 4:  slow_leak_delay_value = value; break;
		case 5:  Stabilization_delay = value; break;
		case 6:  outlet_temp = value; break;
		case 7:  outlet_temp1 = value; break;
		case 8:  differential_temp = value; break;
		case 9:  differential_temp1 = value; break;

		}

		lv_obj_invalidate(spinbox); // Force UI refresh
	}
}

// Increment button event handler
static void increment_temp_event_handler(lv_event_t *e) {
	if (active_spinbox) {
		lv_spinbox_increment(active_spinbox);
		int32_t value = lv_spinbox_get_value(active_spinbox);
		int id = (intptr_t)lv_obj_get_user_data(active_spinbox); // Fix casting

		switch (id) {
		case 1:  flow_warning_value = value; break;
		case 2:  flow_fault_value = value; break;
		case 3:  slow_leak_difference_value = value; break;
		case 4:  slow_leak_delay_value = value; break;
		case 5:  Stabilization_delay = value; break;
		case 6:  outlet_temp = value; break;
		case 7:  outlet_temp1 = value; break;
		case 8:  differential_temp = value; break;
		case 9:  differential_temp1 = value; break;

		}

		lv_obj_invalidate(active_spinbox); // Refresh display
	}
}

// Decrement button event handler
static void decrement_temp_event_handler(lv_event_t *e) {
	if (active_spinbox) {
		lv_spinbox_decrement(active_spinbox);
		int32_t value = lv_spinbox_get_value(active_spinbox);
		int id = (intptr_t)lv_obj_get_user_data(active_spinbox);

		switch (id) {
		case 1:  flow_warning_value = value; break;
		case 2:  flow_fault_value = value; break;
		case 3:  slow_leak_difference_value = value; break;
		case 4:  slow_leak_delay_value = value; break;
		case 5:  Stabilization_delay = value; break;
		case 6:  outlet_temp = value; break;
		case 7:  outlet_temp1 = value; break;
		case 8:  differential_temp = value; break;
		case 9:  differential_temp1 = value; break;

		}

		lv_obj_invalidate(active_spinbox); // Refresh display
	}
}


static void update_spinbox_queue(lv_timer_t * timer)
{
	if (flow_warning_flag == 1) {
		lv_spinbox_set_value(spinbox_Flow_Warning, flow_warning_value);
		lv_obj_invalidate(spinbox_Flow_Warning);
		flow_warning_flag = 0;

	}

	if (flow_fault_flag == 1) {
		lv_spinbox_set_value(spinbox_Flow_Fault, flow_fault_value);
		lv_obj_invalidate(spinbox_Flow_Fault);
		flow_fault_flag = 0;
		//   return;
	}

	if (slow_leak_flag == 1) {
		lv_spinbox_set_value(spinbox_Slow_Leak_Difference, slow_leak_difference_value*10);
		lv_obj_invalidate(spinbox_Slow_Leak_Difference);
		slow_leak_flag = 0;
		// return;
	}

	if (slow_delay_flag == 1) {
		lv_spinbox_set_value(spinbox_Slow_leak_Delay, slow_leak_delay_value);
		lv_obj_invalidate(spinbox_Slow_leak_Delay);
		slow_delay_flag = 0;
		// return;
	}

	if (temp_warning_flag == 1) {
		lv_spinbox_set_value(spinbox_outlet_temp, outlet_temp);
		lv_obj_invalidate(spinbox_outlet_temp);
		temp_warning_flag = 0;
		//  return;
	}

	if (temp_fault_flag == 1) {
		lv_spinbox_set_value(spinbox_outlet_temp_FAULT, outlet_temp1);
		lv_obj_invalidate(spinbox_outlet_temp_FAULT);
		temp_fault_flag = 0;
		//  return;
	}

	if (tempdiff_warning_flag == 1)
	{
		lv_spinbox_set_value(spinbox_diff_temp, differential_temp);
		lv_obj_invalidate(spinbox_diff_temp);
		tempdiff_warning_flag = 0;
		// return;
	}

	if (tempdiff_fault_flag == 1) {
		lv_spinbox_set_value(spinbox_diff_temp_FAULT, differential_temp1);
		lv_obj_invalidate(spinbox_diff_temp_FAULT);
		tempdiff_fault_flag = 0;
		// return;
	}


	if (spinbox_stabilization_Delay_flag==1)
	{
		lv_spinbox_set_value(spinbox_stabilization_Delay, Stabilization_delay);
		lv_obj_invalidate(spinbox_stabilization_Delay);
		spinbox_stabilization_Delay_flag = 0;
		// return;
	}


//for ethernet client to board interface


		if (server_flow_fault_flag==1)
		{
			lv_spinbox_set_value(spinbox_Flow_Fault, flow_fault_value);
			lv_obj_invalidate(spinbox_Flow_Fault);
			server_flow_fault_flag = 0;
		}

		if (server_flow_warning_flag == 1) {
			lv_spinbox_set_value(spinbox_Flow_Warning, flow_warning_value);
			lv_obj_invalidate(spinbox_Flow_Warning);
			server_flow_warning_flag = 0;
		}


		if (server_slow_leak_difference_flag == 1) {
			lv_spinbox_set_value(spinbox_Slow_Leak_Difference,slow_leak_difference_value);
			lv_obj_invalidate(spinbox_Slow_Leak_Difference);
			server_slow_leak_difference_flag = 0;
			// return;
		}

		if ( server_slow_leak_delay_flag == 1) {
			lv_spinbox_set_value(spinbox_Slow_leak_Delay, slow_leak_delay_value);
			lv_obj_invalidate(spinbox_Slow_leak_Delay);
			 server_slow_leak_delay_flag = 0;
			// return;
		}
		if (server_stabilization_flag==1)
			{
				lv_spinbox_set_value(spinbox_stabilization_Delay, Stabilization_delay);
				lv_obj_invalidate(spinbox_stabilization_Delay);
				server_stabilization_flag = 0;
				// return;
			}
		if ( server_outlet_temp_flag == 1) {
			lv_spinbox_set_value(spinbox_outlet_temp, outlet_temp);
			lv_obj_invalidate(spinbox_outlet_temp);
			 server_outlet_temp_flag = 0;
			//  return;
		}

		if (server_outlet_temp1_flag == 1) {
			lv_spinbox_set_value(spinbox_outlet_temp_FAULT, outlet_temp1);
			lv_obj_invalidate(spinbox_outlet_temp_FAULT);
			server_outlet_temp1_flag = 0;
			//  return;
		}

		if (server_differential_temp_flag == 1)
		{
			lv_spinbox_set_value(spinbox_diff_temp, differential_temp);
			lv_obj_invalidate(spinbox_diff_temp);
			server_differential_temp_flag = 0;
			// return;
		}

		if ( server_differential_temp1_flag == 1) {
			lv_spinbox_set_value(spinbox_diff_temp_FAULT, differential_temp1);
			lv_obj_invalidate(spinbox_diff_temp_FAULT);
			 server_differential_temp1_flag = 0;
			// return;
		}



}


// Event handler for the "Press" button
static void event_handler(lv_event_t * e) {


	if (!tabview_screen)
	{
		// Create a new screen with a tabview
		tabview_screen = lv_tabview_create(NULL, LV_DIR_TOP, 35);  // Corrected function call
		//        lv_scr_load(tabview_screen);  // Load the tabview screen
		lv_tabview_set_act(tabview_screen, 0, LV_ANIM_OFF);
		// Add the "Flow" tab
		lv_obj_t * flow_tab = lv_tabview_add_tab(tabview_screen, "Flow Settings");


		//1

		lv_obj_t * flow_label = lv_label_create(flow_tab);
		lv_label_set_text(flow_label, "Flow Warning");
		lv_obj_align(flow_label, LV_ALIGN_TOP_LEFT, 10, -15);


		//2
		lv_obj_t * flow_label1 = lv_label_create(flow_tab);
		lv_label_set_text(flow_label1, "Flow Fault");
		lv_obj_align(flow_label1, LV_ALIGN_TOP_LEFT, 10, 15);

		//3
		lv_obj_t * flow_label2 = lv_label_create(flow_tab);
		lv_label_set_text(flow_label2, "Slow Leak Difference");
		lv_obj_align(flow_label2, LV_ALIGN_TOP_LEFT, 10, 45);


		//4
		lv_obj_t * flow_label3 = lv_label_create(flow_tab);
		lv_label_set_text(flow_label3, "Slow Leak Delay");
		lv_obj_align(flow_label3, LV_ALIGN_LEFT_MID, 10, -10);


		//5
		lv_obj_t * flow_label4 = lv_label_create(flow_tab);
		lv_label_set_text(flow_label4, "Stabilization Delay");
		lv_obj_align(flow_label4, LV_ALIGN_LEFT_MID, 10, 20);


		//6
		lv_obj_t * flow_label5 = lv_label_create(flow_tab);
		lv_label_set_text(flow_label5, "Leak Response");
		lv_obj_align(flow_label5, LV_ALIGN_LEFT_MID, 10, 50);


		//7
		lv_obj_t * flow_label6 = lv_label_create(flow_tab);
		lv_label_set_text(flow_label6, "Unit");
		lv_obj_align(flow_label6, LV_ALIGN_LEFT_MID, 10, 80);


		//SPINBOX FOR FLOW WARNING
		spinbox_Flow_Warning = lv_spinbox_create(flow_tab);
		lv_spinbox_set_range(spinbox_Flow_Warning, 0, 50);

		lv_spinbox_set_value(spinbox_Flow_Warning, flow_warning_value);



		lv_spinbox_set_digit_format(spinbox_Flow_Warning, 2, 3);
		lv_obj_set_size(spinbox_Flow_Warning, 70, 25);
		lv_obj_align(spinbox_Flow_Warning, LV_ALIGN_TOP_LEFT, 205, -15);


		//                      lv_timer_create(update_flow_warning_spinbox, 200, NULL);
		//
		//                      lv_timer_create(update_spinbox1, 200, NULL);
		//                      lv_timer_create(update_spinbox2, 200, NULL);
		//                      lv_timer_create(update_spinbox3, 200, NULL);
		//                      lv_timer_create(update_spinbox4, 200, NULL);
		//                      lv_timer_create(update_spinbox5, 200, NULL);
		//                      lv_timer_create(update_spinbox6, 200, NULL);
		//                      lv_timer_create(update_spinbox7, 200, NULL);

		lv_timer_create(update_spinbox_queue, 100, NULL);


		lv_obj_set_style_text_align(spinbox_Flow_Warning, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_Flow_Warning, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_Flow_Warning, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_Flow_Warning, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_Flow_Warning, 0, LV_PART_MAIN);
		//
		lv_obj_add_event_cb(spinbox_Flow_Warning, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)1);
		lv_obj_add_event_cb(spinbox_Flow_Warning, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)1);
		//  lv_obj_add_event_cb(spinbox_Flow_Warning, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)1);
		//   lv_obj_add_event_cb(spinbox_Flow_Warning, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)1);

		lv_obj_t * spinbox_Flow_Warning_Text = lv_label_create(flow_tab);
		lv_label_set_text(spinbox_Flow_Warning_Text, "LPM");
		lv_obj_align(spinbox_Flow_Warning_Text, LV_ALIGN_TOP_RIGHT, -100, -10);



		//SPINBOX FOR FLOW fault

		spinbox_Flow_Fault = lv_spinbox_create(flow_tab);
		lv_spinbox_set_range(spinbox_Flow_Fault, 0, 50);
		lv_spinbox_set_value(spinbox_Flow_Fault, flow_fault_value);
		lv_spinbox_set_digit_format(spinbox_Flow_Fault, 2, 3);
		lv_obj_set_size(spinbox_Flow_Fault, 70, 25);
		lv_obj_align(spinbox_Flow_Fault, LV_ALIGN_TOP_LEFT, 205, 15);

		lv_obj_set_style_text_align(spinbox_Flow_Fault, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_Flow_Fault, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_Flow_Fault, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_Flow_Fault, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_Flow_Fault, 0, LV_PART_MAIN);


		lv_obj_add_event_cb(spinbox_Flow_Fault, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)2);
		lv_obj_add_event_cb(spinbox_Flow_Fault, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)2);
		//                           lv_obj_add_event_cb(spinbox_Flow_Fault, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)2);
		//                           lv_obj_add_event_cb(spinbox_Flow_Fault, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)2);

		lv_obj_t * spinbox_Flow_Fault_TEXT = lv_label_create(flow_tab);
		lv_label_set_text(spinbox_Flow_Fault_TEXT, "LPM");
		lv_obj_align(spinbox_Flow_Fault_TEXT, LV_ALIGN_TOP_RIGHT, -100, 20);



		//SPINBOX FOR SLOW LEAK DIFFERENCE

		spinbox_Slow_Leak_Difference = lv_spinbox_create(flow_tab);
		lv_spinbox_set_range(spinbox_Slow_Leak_Difference, 0, 100);
		lv_spinbox_set_value(spinbox_Slow_Leak_Difference, slow_leak_difference_value);
		lv_spinbox_set_digit_format(spinbox_Slow_Leak_Difference, 2, 1);
		lv_obj_set_size(spinbox_Slow_Leak_Difference, 70, 25);
		lv_obj_align(spinbox_Slow_Leak_Difference, LV_ALIGN_TOP_LEFT, 205, 45);

		lv_obj_set_style_text_align(spinbox_Slow_Leak_Difference, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_Slow_Leak_Difference, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_Slow_Leak_Difference, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_Slow_Leak_Difference, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_Slow_Leak_Difference, 0, LV_PART_MAIN);

		lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)3);
		lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)3);
		//                      lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)3);
		//                      lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)3);


		lv_obj_t * spinbox_Slow_Leak_Difference_TEXT = lv_label_create(flow_tab);
		lv_label_set_text(spinbox_Slow_Leak_Difference_TEXT, "LPM");
		lv_obj_align(spinbox_Slow_Leak_Difference_TEXT, LV_ALIGN_TOP_RIGHT, -100, 50);


		// Create spinbox for Slow Leak Difference
		// Convert float to integer scaled by 10 (for 1 decimal)
//		int32_t scaled_value = (int32_t)(slow_leak_difference_value * 10.0f);
//
//		// Create spinbox
//		spinbox_Slow_Leak_Difference = lv_spinbox_create(flow_tab);
//
//		// Set range: 0.0 to 100.0 (scaled by 10)
//		lv_spinbox_set_range(spinbox_Slow_Leak_Difference, 0, 1000);
//
//		// Set value (already scaled)
//		lv_spinbox_set_value(spinbox_Slow_Leak_Difference, scaled_value);
//
//		// Format: total digits, decimal places (e.g., 10.0 → 3 digits, 1 decimal)
//		lv_spinbox_set_digit_format(spinbox_Slow_Leak_Difference, 3, 2);
//
//		// Optional step size (e.g., 0.1 steps)
//		lv_spinbox_set_step(spinbox_Slow_Leak_Difference, 1);
//
//		// Align and style
//		lv_obj_set_size(spinbox_Slow_Leak_Difference, 70, 25);
//		lv_obj_align(spinbox_Slow_Leak_Difference, LV_ALIGN_TOP_LEFT, 205, 45);
//
//		lv_obj_set_style_text_align(spinbox_Slow_Leak_Difference, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
//		lv_obj_set_style_pad_left(spinbox_Slow_Leak_Difference, 3, LV_PART_MAIN);
//		lv_obj_set_style_pad_right(spinbox_Slow_Leak_Difference, 0, LV_PART_MAIN);
//		lv_obj_set_style_pad_top(spinbox_Slow_Leak_Difference, 3, LV_PART_MAIN);
//		lv_obj_set_style_pad_bottom(spinbox_Slow_Leak_Difference, 0, LV_PART_MAIN);
//
//		// Events
//		lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)3);
//		lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)3);
//
////		 Optional: Increment/decrement button callbacks
//		 lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)3);
//		 lv_obj_add_event_cb(spinbox_Slow_Leak_Difference, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)3);

////		 Unit Label (LPM)
//		lv_obj_t * spinbox_Slow_Leak_Difference_TEXT = lv_label_create(flow_tab);
//		lv_label_set_text(spinbox_Slow_Leak_Difference_TEXT, "LPM");
//		lv_obj_align(spinbox_Slow_Leak_Difference_TEXT, LV_ALIGN_TOP_RIGHT, -100, 50);

		//SPINBOX FOR SLOW LEAK DELAY

		spinbox_Slow_leak_Delay = lv_spinbox_create(flow_tab);
		lv_spinbox_set_range(spinbox_Slow_leak_Delay, 0, 100);
		lv_spinbox_set_value(spinbox_Slow_leak_Delay, slow_leak_delay_value);
		lv_spinbox_set_digit_format(spinbox_Slow_leak_Delay, 2, 3);
		lv_obj_set_size(spinbox_Slow_leak_Delay, 70, 25);
		lv_obj_align(spinbox_Slow_leak_Delay, LV_ALIGN_TOP_LEFT, 205, 75);

		lv_obj_set_style_text_align(spinbox_Slow_leak_Delay, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_Slow_leak_Delay, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_Slow_leak_Delay, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_Slow_leak_Delay, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_Slow_leak_Delay, 0, LV_PART_MAIN);
		lv_obj_add_event_cb(spinbox_Slow_leak_Delay, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);

		lv_obj_add_event_cb(spinbox_Slow_leak_Delay, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)4);
		lv_obj_add_event_cb(spinbox_Slow_leak_Delay, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)4);
		//                       lv_obj_add_event_cb(spinbox_Slow_leak_Delay, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)4);
		//                      lv_obj_add_event_cb(spinbox_Slow_leak_Delay, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)4);



		lv_obj_t * spinbox_Slow_leak_Delay_TEXT = lv_label_create(flow_tab);
		lv_label_set_text(spinbox_Slow_leak_Delay_TEXT, "S");
		lv_obj_align(spinbox_Slow_leak_Delay_TEXT, LV_ALIGN_TOP_RIGHT, -107, 80);


		//  drop down for stabilization_delay



		spinbox_stabilization_Delay = lv_spinbox_create(flow_tab);
		lv_spinbox_set_range(spinbox_stabilization_Delay, 0, 10);
		lv_spinbox_set_value(spinbox_stabilization_Delay, Stabilization_delay);
		lv_spinbox_set_digit_format(spinbox_stabilization_Delay, 2, 3);
		lv_obj_set_size(spinbox_stabilization_Delay, 70, 25);
		lv_obj_align(spinbox_stabilization_Delay, LV_ALIGN_TOP_LEFT, 205, 105);

		lv_obj_set_style_text_align(spinbox_stabilization_Delay, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_stabilization_Delay, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_stabilization_Delay, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_stabilization_Delay, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_stabilization_Delay, 0, LV_PART_MAIN);
		lv_obj_add_event_cb(spinbox_stabilization_Delay, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);

		lv_obj_add_event_cb(spinbox_stabilization_Delay, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)5);
		lv_obj_add_event_cb(spinbox_stabilization_Delay, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)5);
		//                        lv_obj_add_event_cb(spinbox_stabilization_Delay, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)5);
		//                       lv_obj_add_event_cb(spinbox_stabilization_Delay, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)5);



		lv_obj_t * spinbox_stabilization_Delay_TEXT = lv_label_create(flow_tab);
		lv_label_set_text(spinbox_stabilization_Delay_TEXT, "S");
		lv_obj_align(spinbox_stabilization_Delay_TEXT, LV_ALIGN_TOP_RIGHT, -107, 110);







		// LEAK_RESPONSE_spinbox
		lv_obj_t *  LEAK_RESPONSE_DROPDOWN = lv_dropdown_create(flow_tab);
		lv_dropdown_set_options( LEAK_RESPONSE_DROPDOWN, "Normal\n"
				"Open\n"
				"Presize"
		);
		lv_dropdown_set_selected(LEAK_RESPONSE_DROPDOWN, 2);
		lv_obj_set_style_pad_left( LEAK_RESPONSE_DROPDOWN, 6, 0);  // Left padding for options
		lv_obj_set_style_pad_right( LEAK_RESPONSE_DROPDOWN, 6, 0); // Right padding for options
		lv_obj_set_style_pad_top( LEAK_RESPONSE_DROPDOWN, 6, 0);   // Top padding for options
		lv_obj_set_style_pad_bottom( LEAK_RESPONSE_DROPDOWN, 6, 0); // Bottom padding for options


		lv_obj_align( LEAK_RESPONSE_DROPDOWN, LV_ALIGN_TOP_LEFT, 205, 135); // Align dropdown next to the label at (X + 60)
		lv_obj_set_size( LEAK_RESPONSE_DROPDOWN, 90, 25);
		lv_obj_add_event_cb( LEAK_RESPONSE_DROPDOWN, event_handler_Flow_3_parameters, LV_EVENT_ALL, NULL);
		lv_obj_add_event_cb( LEAK_RESPONSE_DROPDOWN, event_handler_Flow_3_parameters, LV_EVENT_ALL, (void*) 2);







		// unit flow

		lv_obj_t *  UNIT = lv_dropdown_create(flow_tab);
		lv_dropdown_set_options( UNIT, "GPM\n"
				"LPM"
		);
		lv_obj_set_style_pad_left( UNIT, 6, 0);  // Left padding for options
		lv_obj_set_style_pad_right( UNIT, 6, 0); // Right padding for options
		lv_obj_set_style_pad_top( UNIT, 6, 0);   // Top padding for options
		lv_obj_set_style_pad_bottom( UNIT, 6, 0); // Bottom padding for options
		lv_dropdown_set_selected(UNIT, 1);

		update_values();

		lv_obj_align( UNIT, LV_ALIGN_TOP_LEFT, 205, 165); // Align dropdown next to the label at (X + 60)
		lv_obj_set_size( UNIT, 70, 25);
		lv_obj_add_event_cb( UNIT, event_handler_Flow_3_parameters, LV_EVENT_ALL, NULL);
		lv_obj_add_event_cb( UNIT, event_handler_Flow_3_parameters, LV_EVENT_ALL, (void*) 3); // Pass unique ID for Valve 1




		///// INCREMENT DECREMENT BUTTONS


		lv_obj_t *inc_btn1 = lv_btn_create(flow_tab);
		lv_obj_set_size(inc_btn1, 50, 50);
		lv_obj_align(inc_btn1, LV_ALIGN_CENTER, 185, -20);
		lv_obj_t *inc_label1 = lv_label_create(inc_btn1);
		lv_label_set_text(inc_label1, LV_SYMBOL_PLUS);
		lv_obj_set_style_bg_color(inc_btn1, lv_color_hex(0x008000), LV_PART_MAIN);
		lv_obj_center(inc_label1);
		lv_obj_add_event_cb(inc_btn1, increment_temp_event_handler, LV_EVENT_CLICKED, NULL);

		// Decrement Button for Outlet Temperature
		lv_obj_t *dec_btn1 = lv_btn_create(flow_tab);
		lv_obj_set_size(dec_btn1, 50, 50);
		lv_obj_align(dec_btn1, LV_ALIGN_CENTER, 185, 40);
		lv_obj_t *dec_label1 = lv_label_create(dec_btn1);
		lv_label_set_text(dec_label1, LV_SYMBOL_MINUS);
		lv_obj_set_style_bg_color(dec_btn1, lv_color_hex(0xFF0000), LV_PART_MAIN); // Set decrement button color to red
		lv_obj_center(dec_label1);
		lv_obj_add_event_cb(dec_btn1, decrement_temp_event_handler, LV_EVENT_CLICKED, NULL);




		////// / / / ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		//TEMP TAB ALL WORK

		lv_obj_t * temp_tab = lv_tabview_add_tab(tabview_screen, "Temperature Settings");


		lv_obj_t * Temp_label = lv_label_create(temp_tab);
		lv_label_set_text(Temp_label, "Outlet Temprature");
		lv_obj_align(Temp_label, LV_ALIGN_TOP_LEFT, 10, 0);


		//2
		lv_obj_t * Temp_label1 = lv_label_create(temp_tab);
		lv_label_set_text(Temp_label1, "Differential Temprature");
		lv_obj_align(Temp_label1, LV_ALIGN_TOP_LEFT, 10, 32);

		//3
		//                lv_obj_t * Temp_label2 = lv_label_create(temp_tab);
		//                lv_label_set_text(Temp_label2, "Thermal Load");
		//                lv_obj_align(Temp_label2, LV_ALIGN_TOP_LEFT, 10, 63);


		//4
		//                lv_obj_t * Temp_label3 = lv_label_create(temp_tab);
		//                lv_label_set_text(Temp_label3, "Coolant Density");
		//                lv_obj_align(Temp_label3, LV_ALIGN_LEFT_MID, 10, 5);
		//
		//
		//                //5
		//                lv_obj_t * Temp_label4= lv_label_create(temp_tab);
		//                lv_label_set_text(Temp_label4, "Coolant Heat Capacity");
		//                lv_obj_align(Temp_label4, LV_ALIGN_LEFT_MID, 10, 35);
		//
		//
		//                //6
		//                lv_obj_t * Temp_label5 = lv_label_create(temp_tab);
		//                lv_label_set_text(Temp_label5, "Heat Load Threshold");
		//                lv_obj_align(Temp_label5, LV_ALIGN_LEFT_MID, 10, 65);


		//7
		lv_obj_t * Temp_label6 = lv_label_create(temp_tab);
		lv_label_set_text(Temp_label6, "Unit");
		lv_obj_align(Temp_label6, LV_ALIGN_TOP_LEFT, 10, 63);


		lv_obj_t * Temp_label7 = lv_label_create(temp_tab);
		lv_label_set_text(Temp_label7, "WARNING");
		lv_obj_align(Temp_label7, LV_ALIGN_TOP_LEFT, 220, -18);
		lv_obj_set_style_text_color(Temp_label7, lv_color_hex(0xFF00FF), LV_PART_MAIN);

		lv_obj_t * Temp_label8 = lv_label_create(temp_tab);
		lv_label_set_text(Temp_label8, "FAULT");
		lv_obj_align(Temp_label8, LV_ALIGN_TOP_RIGHT, -80, -18);
		lv_obj_set_style_text_color(Temp_label8, lv_color_hex(0xFF0000), LV_PART_MAIN);
		//SPINBOX FOR OUTLET TEMP WARNING
		spinbox_outlet_temp = lv_spinbox_create(temp_tab);
		lv_spinbox_set_range(spinbox_outlet_temp, 0, 100);
		lv_spinbox_set_value(spinbox_outlet_temp, outlet_temp);
		lv_spinbox_set_digit_format(spinbox_outlet_temp, 3, 3);
		lv_obj_set_size(spinbox_outlet_temp, 70, 25);
		lv_obj_align(spinbox_outlet_temp, LV_ALIGN_TOP_LEFT, 220, 0);

		lv_obj_set_style_text_align(spinbox_outlet_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_outlet_temp, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_outlet_temp, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_outlet_temp, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_outlet_temp, 0, LV_PART_MAIN);
		//                       lv_obj_add_event_cb(spinbox_outlet_temp, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);

		lv_obj_add_event_cb(spinbox_outlet_temp, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)6);
		lv_obj_add_event_cb(spinbox_outlet_temp, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)6);
		//                        lv_obj_add_event_cb(spinbox_outlet_temp, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)6);
		//                       lv_obj_add_event_cb(spinbox_outlet_temp, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)6);

		lv_obj_t * spinbox_outlet_temp_TEXT = lv_label_create(temp_tab);
		lv_label_set_text(spinbox_outlet_temp_TEXT, "°C");
		lv_obj_align(spinbox_outlet_temp_TEXT, LV_ALIGN_TOP_RIGHT, -40, 5);

		//SPINBOX FOR OUTLET TEMP FAULT
		spinbox_outlet_temp_FAULT = lv_spinbox_create(temp_tab);
		lv_spinbox_set_range(spinbox_outlet_temp_FAULT, 0, 100);
		lv_spinbox_set_value(spinbox_outlet_temp_FAULT, outlet_temp1);
		lv_spinbox_set_digit_format(spinbox_outlet_temp_FAULT, 3, 3);
		lv_obj_set_size(spinbox_outlet_temp_FAULT, 70, 25);
		lv_obj_align(spinbox_outlet_temp_FAULT, LV_ALIGN_TOP_RIGHT, -70, 0);

		lv_obj_set_style_text_align(spinbox_outlet_temp_FAULT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_outlet_temp_FAULT, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_outlet_temp_FAULT, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_outlet_temp_FAULT, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_outlet_temp_FAULT, 0, LV_PART_MAIN);
		//                     lv_obj_add_event_cb(spinbox_outlet_temp_FAULT, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);

		lv_obj_add_event_cb(spinbox_outlet_temp_FAULT, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)7);
		lv_obj_add_event_cb(spinbox_outlet_temp_FAULT, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)7);
		//                       lv_obj_add_event_cb(spinbox_outlet_temp_FAULT, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)7);
		//                       lv_obj_add_event_cb(spinbox_outlet_temp_FAULT, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)7);



		//SPINBOX FOR DIFFERENTIAL TEMPRATURE WARNING
		spinbox_diff_temp = lv_spinbox_create(temp_tab);
		lv_spinbox_set_range(spinbox_diff_temp, 0, 100);
		lv_spinbox_set_value(spinbox_diff_temp, differential_temp);
		lv_spinbox_set_digit_format(spinbox_diff_temp, 3, 3);
		lv_obj_set_size(spinbox_diff_temp, 70, 25);
		lv_obj_align(spinbox_diff_temp, LV_ALIGN_TOP_LEFT, 220, 30);

		lv_obj_set_style_text_align(spinbox_diff_temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_diff_temp, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_diff_temp, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_diff_temp, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_diff_temp, 0, LV_PART_MAIN);
		//                       lv_obj_add_event_cb(spinbox_diff_temp, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);



		lv_obj_add_event_cb(spinbox_diff_temp, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)8);
		lv_obj_add_event_cb(spinbox_diff_temp, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)8);
		//                       lv_obj_add_event_cb(spinbox_diff_temp, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)8);
		//                       lv_obj_add_event_cb(spinbox_diff_temp, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)8);
		//

		lv_obj_t * spinbox_diff_temp_TEXT = lv_label_create(temp_tab);
		lv_label_set_text(spinbox_diff_temp_TEXT, "°C");
		lv_obj_align(spinbox_diff_temp_TEXT, LV_ALIGN_TOP_RIGHT, -40, 35);

		//SPINBOX FOR DIFFERENTIAL TEMPRATURE FAULT
		spinbox_diff_temp_FAULT = lv_spinbox_create(temp_tab);
		lv_spinbox_set_range(spinbox_diff_temp_FAULT, 0, 100);
		lv_spinbox_set_value(spinbox_diff_temp_FAULT, differential_temp1);
		lv_spinbox_set_digit_format(spinbox_diff_temp_FAULT, 3, 3);
		lv_obj_set_size(spinbox_diff_temp_FAULT, 70, 25);
		lv_obj_align(spinbox_diff_temp_FAULT, LV_ALIGN_TOP_RIGHT, -70, 30);

		lv_obj_set_style_text_align(spinbox_diff_temp_FAULT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_pad_left(spinbox_diff_temp_FAULT, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_right(spinbox_diff_temp_FAULT, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_top(spinbox_diff_temp_FAULT, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_bottom(spinbox_diff_temp_FAULT, 0, LV_PART_MAIN);
		//                       lv_obj_add_event_cb(spinbox_diff_temp_FAULT, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);

		lv_obj_add_event_cb(spinbox_diff_temp_FAULT, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)9);
		lv_obj_add_event_cb(spinbox_diff_temp_FAULT, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)9);
		//                       lv_obj_add_event_cb(spinbox_diff_temp_FAULT, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)9);
		//                       lv_obj_add_event_cb(spinbox_diff_temp_FAULT, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)9);
		//SPINBOX FOR THERMAL LOAD WARNING

		//                      spinbox_Thermal_load = lv_spinbox_create(temp_tab);
		//                      lv_spinbox_set_range(spinbox_Thermal_load, 0, 100);
		//                      lv_spinbox_set_value(spinbox_Thermal_load, 70);
		//                      lv_spinbox_set_digit_format(spinbox_Thermal_load, 3, 3);
		//                      lv_obj_set_size(spinbox_Thermal_load, 70, 25);
		//                      lv_obj_align(spinbox_Thermal_load, LV_ALIGN_TOP_LEFT, 220, 60);
		//
		//                      lv_obj_set_style_text_align(spinbox_Thermal_load, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_left(spinbox_Thermal_load, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_right(spinbox_Thermal_load, 0, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_top(spinbox_Thermal_load, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_bottom(spinbox_Thermal_load, 0, LV_PART_MAIN);
		////                      lv_obj_add_event_cb(spinbox_Thermal_load, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);
		//
		//
		//                      lv_obj_add_event_cb(spinbox_Thermal_load, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)10);
		//                      lv_obj_add_event_cb(spinbox_Thermal_load, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)10);
		//                      lv_obj_add_event_cb(spinbox_Thermal_load, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)10);
		//                      lv_obj_add_event_cb(spinbox_Thermal_load, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)10);
		//                      lv_obj_t * spinbox_Thermal_load_TEXT = lv_label_create(temp_tab);
		//                      lv_label_set_text(spinbox_Thermal_load_TEXT, "KW");
		//                      lv_obj_align(spinbox_Thermal_load_TEXT, LV_ALIGN_TOP_RIGHT, -40, 50);

		//SPINBOX FOR THERMAL LOAD FAULT

		//                      spinbox_Thermal_load_FAULT = lv_spinbox_create(temp_tab);
		//                      lv_spinbox_set_range(spinbox_Thermal_load_FAULT, 0, 100);
		//                      lv_spinbox_set_value(spinbox_Thermal_load_FAULT, 90);
		//                      lv_spinbox_set_digit_format(spinbox_Thermal_load_FAULT, 3, 3);
		//                      lv_obj_set_size(spinbox_Thermal_load_FAULT, 70, 25);
		//                      lv_obj_align(spinbox_Thermal_load_FAULT, LV_ALIGN_TOP_RIGHT, -70, 60);
		//
		//                      lv_obj_set_style_text_align(spinbox_Thermal_load_FAULT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_left(spinbox_Thermal_load_FAULT, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_right(spinbox_Thermal_load_FAULT, 0, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_top(spinbox_Thermal_load_FAULT, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_bottom(spinbox_Thermal_load_FAULT, 0, LV_PART_MAIN);
		////                      lv_obj_add_event_cb(spinbox_Thermal_load_FAULT, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);
		//
		//                      lv_obj_add_event_cb(spinbox_Thermal_load_FAULT, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)11);
		//                      lv_obj_add_event_cb(spinbox_Thermal_load_FAULT, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)11);
		//                      lv_obj_add_event_cb(spinbox_Thermal_load_FAULT, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)11);
		//                      lv_obj_add_event_cb(spinbox_Thermal_load_FAULT, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)11);


		//        //SPINBOX FOR COOLANT DENSITY
		//                      spinbox_Coolant_Density = lv_spinbox_create(temp_tab);
		//                      lv_spinbox_set_range(spinbox_Coolant_Density, 0, 100);
		//                      lv_spinbox_set_value(spinbox_Coolant_Density, 0);
		//                      lv_spinbox_set_digit_format(spinbox_Coolant_Density, 3, 3);
		//                      lv_obj_set_size(spinbox_Coolant_Density, 70, 25);
		//                      lv_obj_align(spinbox_Coolant_Density, LV_ALIGN_TOP_LEFT, 220, 90);
		//
		//                      lv_obj_set_style_text_align(spinbox_Coolant_Density, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_left(spinbox_Coolant_Density, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_right(spinbox_Coolant_Density, 0, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_top(spinbox_Coolant_Density, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_bottom(spinbox_Coolant_Density, 0, LV_PART_MAIN);
		////                      lv_obj_add_event_cb(spinbox_Coolant_Density, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);
		//
		//                      lv_obj_add_event_cb(spinbox_Coolant_Density, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)12);
		//                      lv_obj_add_event_cb(spinbox_Coolant_Density, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)12);
		////                      lv_obj_add_event_cb(spinbox_Coolant_Density, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)12);
		////                      lv_obj_add_event_cb(spinbox_Coolant_Density, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)12);
		//
		//                      //TEXT
		//                      lv_obj_t * spinbox_Coolant_Density_TEXT = lv_label_create(temp_tab);
		//                      lv_label_set_text(spinbox_Coolant_Density_TEXT, "  kg/m³ ");
		//                      lv_obj_align(spinbox_Coolant_Density_TEXT, LV_ALIGN_RIGHT_MID, -75, 5);
		//
		//           //SPINBOX FOR COOLANT HEAT CAPACITY
		//                      spinbox_Coolant_Heat_Capacity = lv_spinbox_create(temp_tab);
		//                      lv_spinbox_set_range(spinbox_Coolant_Heat_Capacity, 0, 100);
		//                      lv_spinbox_set_value(spinbox_Coolant_Heat_Capacity, 0);
		//                      lv_spinbox_set_digit_format(spinbox_Coolant_Heat_Capacity, 3, 3);
		//                      lv_obj_set_size(spinbox_Coolant_Heat_Capacity, 70, 25);
		//                      lv_obj_align(spinbox_Coolant_Heat_Capacity, LV_ALIGN_TOP_LEFT, 220, 120);
		//
		//                      lv_obj_set_style_text_align(spinbox_Coolant_Heat_Capacity, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_left(spinbox_Coolant_Heat_Capacity, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_right(spinbox_Coolant_Heat_Capacity, 0, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_top(spinbox_Coolant_Heat_Capacity, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_bottom(spinbox_Coolant_Heat_Capacity, 0, LV_PART_MAIN);
		////                      lv_obj_add_event_cb(spinbox_Coolant_Heat_Capacity, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);
		//
		//                      lv_obj_add_event_cb(spinbox_Coolant_Heat_Capacity, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)13);
		//                      lv_obj_add_event_cb(spinbox_Coolant_Heat_Capacity, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)13);
		////                      lv_obj_add_event_cb(spinbox_Coolant_Heat_Capacity, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)13);
		////                      lv_obj_add_event_cb(spinbox_Coolant_Heat_Capacity, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)13);
		//
		//                      lv_obj_t * spinbox_Coolant_Heat_Capacity_TEXT = lv_label_create(temp_tab);
		//                      lv_label_set_text(spinbox_Coolant_Heat_Capacity_TEXT, " J/kg.°C");
		//                      lv_obj_align(spinbox_Coolant_Heat_Capacity_TEXT, LV_ALIGN_RIGHT_MID, -80, 35);
		//
		//              //SPINBOX FOR HEAT LOAD THRESHOLD
		//                      spinbox_Heat_Load_Threshold = lv_spinbox_create(temp_tab);
		//                      lv_spinbox_set_range(spinbox_Heat_Load_Threshold, 0, 100);
		//                      lv_spinbox_set_value(spinbox_Heat_Load_Threshold, 0);
		//                      lv_spinbox_set_digit_format(spinbox_Heat_Load_Threshold, 3, 3);
		//                      lv_obj_set_size(spinbox_Heat_Load_Threshold, 70, 25);
		//                      lv_obj_align(spinbox_Heat_Load_Threshold, LV_ALIGN_TOP_LEFT, 220, 150);
		//
		//                      lv_obj_set_style_text_align(spinbox_Heat_Load_Threshold, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_left(spinbox_Heat_Load_Threshold, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_right(spinbox_Heat_Load_Threshold, 0, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_top(spinbox_Heat_Load_Threshold, 3, LV_PART_MAIN);
		//                      lv_obj_set_style_pad_bottom(spinbox_Heat_Load_Threshold, 0, LV_PART_MAIN);
		////                      lv_obj_add_event_cb(spinbox_Heat_Load_Threshold, spinbox_event_handler, LV_EVENT_FOCUSED, NULL);
		//                      lv_obj_add_event_cb(spinbox_Heat_Load_Threshold, spinbox_event_handler, LV_EVENT_FOCUSED, (void*)14);
		//                      lv_obj_add_event_cb(spinbox_Heat_Load_Threshold, spinbox_event_handler, LV_EVENT_VALUE_CHANGED, (void*)14);
		////                      lv_obj_add_event_cb(spinbox_Heat_Load_Threshold, increment_temp_event_handler, LV_EVENT_PRESSED, (void*)14);
		////                      lv_obj_add_event_cb(spinbox_Heat_Load_Threshold, decrement_temp_event_handler, LV_EVENT_PRESSED, (void*)14);
		//
		//
		//                      lv_obj_t * spinbox_Heat_Load_Threshold_TEXT = lv_label_create(temp_tab);
		//                      lv_label_set_text(spinbox_Heat_Load_Threshold_TEXT, " °C ");
		//                      lv_obj_align(spinbox_Heat_Load_Threshold_TEXT, LV_ALIGN_RIGHT_MID, -95, 60);




		//dropdown for unit temp

		lv_obj_t *  Unit_Temp = lv_dropdown_create(temp_tab);
		lv_dropdown_set_options( Unit_Temp, "°C\n"
				"°f"  );
		lv_obj_set_style_pad_left( Unit_Temp, 5, 0);  // Left padding for options
		lv_obj_set_style_pad_right( Unit_Temp, 5, 0); // Right padding for options
		lv_obj_set_style_pad_top( Unit_Temp, 5, 0);   // Top padding for options
		lv_obj_set_style_pad_bottom( Unit_Temp, 5, 0); // Bottom padding for options


		lv_obj_align( Unit_Temp, LV_ALIGN_TOP_RIGHT, -70, 60); // Align dropdown next to the label at (X + 60)
		lv_obj_set_size( Unit_Temp, 70, 25);
		lv_obj_add_event_cb( Unit_Temp, event_handler_Flow_3_parameters, LV_EVENT_ALL, NULL);
		lv_obj_add_event_cb( Unit_Temp, event_handler_Flow_3_parameters, LV_EVENT_ALL, (void*) 4);


		// Increment Button for Outlet Temperature
		lv_obj_t *inc_btn = lv_btn_create(temp_tab);
		lv_obj_set_size(inc_btn, 50, 50);
		lv_obj_align(inc_btn, LV_ALIGN_CENTER, 185, -20);
		lv_obj_t *inc_label = lv_label_create(inc_btn);
		lv_label_set_text(inc_label, LV_SYMBOL_PLUS);
		lv_obj_set_style_bg_color(inc_btn, lv_color_hex(0x008000), LV_PART_MAIN);
		lv_obj_center(inc_label);
		lv_obj_add_event_cb(inc_btn, increment_temp_event_handler, LV_EVENT_CLICKED, NULL);

		// Decrement Button for Outlet Temperature
		lv_obj_t *dec_btn = lv_btn_create(temp_tab);
		lv_obj_set_size(dec_btn, 50, 50);
		lv_obj_align(dec_btn, LV_ALIGN_CENTER, 185, 40);
		lv_obj_t *dec_label = lv_label_create(dec_btn);
		lv_label_set_text(dec_label, LV_SYMBOL_MINUS);
		lv_obj_set_style_bg_color(dec_btn, lv_color_hex(0xFF0000), LV_PART_MAIN); // Set decrement button color to red
		lv_obj_center(dec_label);
		lv_obj_add_event_cb(dec_btn, decrement_temp_event_handler, LV_EVENT_CLICKED, NULL);







		//RETURN BUTTON ON BOTH TAB VIEWS
		lv_obj_t * return_btn = lv_btn_create(flow_tab);  // Use lv_scr_act() to place the button on the active screen
		lv_obj_set_size(return_btn, 80, 30);  // Adjust size as needed
		lv_obj_align(return_btn, LV_ALIGN_BOTTOM_RIGHT, -70, 0);  // Align to the bottom right with an offset
		lv_obj_t * return_label = lv_label_create(return_btn);
		lv_label_set_text(return_label, "Return");
		lv_obj_add_event_cb(return_btn, return_event_handler, LV_EVENT_CLICKED, NULL);  // Attach the event handler
		lv_obj_set_style_bg_color(return_btn, lv_color_hex(0x000000), LV_PART_MAIN);

		lv_obj_t * return_btn1 = lv_btn_create(temp_tab);  // Use lv_scr_act() to place the button on the active screen
		lv_obj_set_size(return_btn1, 80, 30);  // Adjust size as needed
		lv_obj_align(return_btn1, LV_ALIGN_BOTTOM_RIGHT, -80, -5);  // Align to the bottom right with an offset
		lv_obj_t * return_label1 = lv_label_create(return_btn1);
		lv_label_set_text(return_label1, "Return");
		lv_obj_set_style_bg_color(return_btn1, lv_color_hex(0x000000), LV_PART_MAIN);
		lv_obj_add_event_cb(return_btn1, return_event_handler, LV_EVENT_CLICKED, NULL);  // Attach the event handler

	}

	lv_scr_load(tabview_screen);  // Load the tabview screen
}

void lv_example_btn_1(void)
{
	// Create the main screen (if not already created)
	if (!main_screen) {
		main_screen = lv_scr_act();  // Store the reference to the main screen
	}

	// Create the "Press" button
	lv_obj_t * btn1 = lv_btn_create(main_screen);
	lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_CLICKED, NULL);  // Attach the event handler
	lv_obj_align(btn1, LV_ALIGN_LEFT_MID, 140, 72);  // Align the button
	lv_obj_set_size(btn1, 70, 25);  // Set button size

	// Create a label on the button
	lv_obj_t * label = lv_label_create(btn1);
	lv_label_set_text(label, "PRESS");
	lv_obj_center(label);


	lv_obj_set_style_bg_color(btn1, lv_color_hex(0x0000FF), LV_PART_MAIN);
}


void show_text1(int value , int value1, int value2, int value3)
{
	// Create a container for the labels
	lv_obj_t *cont = lv_obj_create(lv_scr_act());
	lv_obj_set_size(cont, 210, 180);  // Adjust the size as needed
	lv_obj_align(cont, LV_ALIGN_TOP_RIGHT, -20, 80);  // Align the container to the top-right corner
	lv_obj_set_style_border_width(cont, 2, LV_PART_MAIN);  // Set border width
	lv_obj_set_style_border_color(cont, lv_color_hex(0x00000F), LV_PART_MAIN);  // Border color (blue)
	lv_obj_set_style_radius(cont, 10, LV_PART_MAIN);  // Rounded corners

	// Create labels inside the container
	label1 = lv_label_create(lv_scr_act());
	label2 = lv_label_create(lv_scr_act());
	label3 = lv_label_create(lv_scr_act());
	label4 = lv_label_create(lv_scr_act());

	// Format the text for the labels
	char temp_text[32];
	char flow_text[32];
	char temp_text1[32];
	char flow_text1[32];

	//    snprintf(temp_text, sizeof(temp_text), "INPUT TEMP =  %0.2f °C", temp2);
	//    snprintf(flow_text, sizeof(flow_text), "INPUT FLOW = %0.2f LPM", average_flow);
	//    snprintf(temp_text1, sizeof(temp_text1), "TEMP OUT =  %0.2f °C", temp1);
	//    snprintf(flow_text1, sizeof(flow_text1), " FLOW OUT =  %0.2f LPM", average_flow1);
	float flow_in = mode ? average_flow1 : average_flow1 * LPM_TO_GPM;
	float flow_out = mode ? average_flow : average_flow * LPM_TO_GPM;

	float temp_in = celcious_flag ? temp1 : CELSIUS_TO_FAHRENHEIT(temp1);
	float temp_out = fahrenheit_flag ? temp2 : CELSIUS_TO_FAHRENHEIT(temp2);


	snprintf(temp_text, sizeof(temp_text), "INPUT TEMP = %0.2f %s", temp_in, celcious_flag ? "°C" : "°F");
	snprintf(flow_text, sizeof(flow_text), "INPUT FLOW = %0.2f %s", flow_in, mode ? "LPM" : "GPM");
	snprintf(temp_text1, sizeof(temp_text1), "TEMP OUT = %0.2f %s", temp_out, fahrenheit_flag ? "°C" : "°F");
	snprintf(flow_text1, sizeof(flow_text1), "FLOW OUT = %0.2f %s", flow_out, mode ? "LPM" : "GPM");

	lv_label_set_text(label1, temp_text);
	lv_label_set_text(label2, flow_text);
	lv_label_set_text(label3, temp_text1);
	lv_label_set_text(label4, flow_text1);

	// Align the labels inside the container
	lv_obj_align(label1, LV_ALIGN_CENTER, 115, -30);  // Align label1 to the top-left of the container
	lv_obj_align(label2, LV_ALIGN_CENTER, 115, 0); // Align label2 below label1
	lv_obj_align(label3, LV_ALIGN_CENTER, 115, 65); // Align label3 below label2
	lv_obj_align(label4, LV_ALIGN_CENTER, 115, 95); // Align label4 below label3



}

void update_values(int value , int value1, int value2, int value3)
{
	// Update the text of each label with the new values
	char temp_text[32];
	char flow_text[32];
	char temp_text1[32];
	char flow_text1[32];


	float flow_in = mode ? average_flow1 : average_flow1 * LPM_TO_GPM;
	float flow_out = mode ? average_flow : average_flow * LPM_TO_GPM;


	float temp_in = celcious_flag ? temp1 : CELSIUS_TO_FAHRENHEIT(temp1);
	float temp_out = fahrenheit_flag ? temp2 : CELSIUS_TO_FAHRENHEIT(temp2);

	//    snprintf(temp_text, sizeof(temp_text), "INPUT TEMP =  %0.2f °C", temp2);
	//    snprintf(flow_text, sizeof(flow_text), "INPUT FLOW = %0.2f LPM", average_flow);
	//    snprintf(temp_text1, sizeof(temp_text1), "TEMP OUT =  %0.2f °C", temp1);
	//    snprintf(flow_text1, sizeof(flow_text1), " FLOW OUT =  %0.2f LPM", average_flow1);

	snprintf(temp_text, sizeof(temp_text), "INPUT TEMP = %0.2f %s", temp_in, celcious_flag ? "°C" : "°F");
	snprintf(flow_text, sizeof(flow_text), "INPUT FLOW = %0.2f %s", flow_in, mode ? "LPM" : "GPM");
	snprintf(temp_text1, sizeof(temp_text1), "TEMP OUT = %0.2f %s", temp_out, fahrenheit_flag ? "°C" : "°F");
	snprintf(flow_text1, sizeof(flow_text1), "FLOW OUT = %0.2f %s", flow_out, mode ? "LPM" : "GPM");

	lv_label_set_text(label1, temp_text);
	lv_label_set_text(label2, flow_text);
	lv_label_set_text(label3, temp_text1);
	lv_label_set_text(label4, flow_text1);

	// Redraw the updated labels to reflect the new values
	lv_obj_refresh_ext_draw_size(label1);
	lv_obj_refresh_ext_draw_size(label2);
	lv_obj_refresh_ext_draw_size(label3);
	lv_obj_refresh_ext_draw_size(label4);
}

// Dummy dropdown example function
void lv_example_dropdown_2(void) {
	// Add dropdown example logic here if needed
}

#endif  // LV_USE_DROPDOWN && LV_USE_BTN && LV_BUILD_EXAMPLES
