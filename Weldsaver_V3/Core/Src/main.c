/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>

#include<stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../lvgl/lvgl.h"
#include "../../lv_conf.h"
#include "../../hal_stm_lvgl/tft/tft.h"
#include "../../hal_stm_lvgl/touchpad/touchpad.h"
//#include "../../lv_examples.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
LV_IMG_DECLARE(leakage_warning_1);  // This assumes you have an image called 'my_image'
//int count;
// Declare the TFT display object and other global variables
lv_obj_t * img_obj = NULL;
lv_obj_t * txt_obj = NULL;
bool img_visible = false;  // Variable to track image visibility
bool txt_visible = false;
static bool calculate_flow = true;

//FOR ADC AND INPUT CAPTURE
uint32_t adc_temperature;
uint32_t adc_flow_rate;

uint32_t adc_temperature_1;
uint32_t adc_flow_rate_1;

uint32_t sensor_value,sensor_value1;
 uint8_t timer10s_flag = 0;
 uint8_t timer10s_flag1=0;

 volatile uint8_t programStarted = 0;
//static uint32_t timerCounter = 0;  // To count the timer interrupts
//static uint32_t lastActionTime = 0;  // To store the last action time
#define ACTION_DELAY_MS 5000  // 5 seconds delay

extern int flow_warning_value;
extern int flow_fault_value;
extern float slow_leak_difference_value;
extern int  slow_leak_delay_value;
extern int Stabilization_delay;

extern int outlet_temp;
extern int outlet_temp1;
extern int differential_temp;
extern int differential_temp1;
extern int thermal_load;
extern int thermal_load1;


float thermal_load_calculations=0;
float m=0.00f;
int initialtemp=24;



extern int celcious_flag;
extern int fahrenheit_flag;


extern int  Normal_Flag;
extern int Open_Flag;
extern int Presize_Flag;


float term1;
float term2;
float term3;
float term4;
float term5;
float term6;
//coolant_density_variables
float temperature = 60.0;  // Example: Change this value as needed

// Coefficients for the formula
const float a0 = 999.83952;
const float a1 = 16.945176;
const float a2 = -7.9870401e-3;
const float a3 = -46.170461e-6;
const float a4 = 105.56302e-9;
const float a5 = -280.54253e-12;


// Step-by-step calculation of each term

int mode = true;
// Sum up all terms to calculate the density
float density;

extern float GPM;
extern float GPM1;

volatile uint32_t timerOverflowCount = 0;
volatile bool timerExpired = false;



float temp1;
float temp2;

float trip_point;

 lv_obj_t *dd;
lv_obj_t* warning_lable;
lv_obj_t* warning_lable1;
//#define TIMCLOCK   108000000
//
//#define PRESCALAR  42000

#define TIMCLOCK   108000000

#define PRESCALAR  41000


#define MAX_VALUES 20
#define MAX_VALUES1 20

#define  MAX_VALUES_flow 20
#define MAX_VALUES_flow1 20
//#define TIMCLOCK   108000000
//#define PRESCALAR  104.8

#define MAX_VALID_CAPTURE 5000
#define MIN_VALID_CAPTURE 10
#define MAX_VALID_PULSE_PERIOD 10000


#define TIMEOUT_PERIOD 1000  // Timeout period in milliseconds (adjust as needed).
#define STUCK_THRESHOLD 1500
#define STUCK_THRESHOLD1 1500 // Number of cycles to detect stuck condition.

// Declare a global variable to track the timeout period (in callback cycles)
uint32_t no_pulse_timeout_counter = 0;
uint32_t previous_capture_time = 0;  // Store the previous capture time
//float average_flow = 50.00f;           // Variable to store average flow

int stuck_counter = 0;   // Counter to track if flow is stuck
int stuck_counter1 = 0;
int valve_Count=0;

volatile uint32_t IC_Val1_TIM13 = 0, IC_Val2_TIM13 = 0;
volatile uint32_t IC_Val1_TIM14 = 0, IC_Val2_TIM14 = 0;
volatile uint32_t Difference_TIM13 = 0, Difference_TIM14 = 0;
volatile float frequency_TIM13 = 0, frequency_TIM14 = 0;
volatile uint8_t Is_First_Captured_TIM13 = 0, Is_First_Captured_TIM14 = 0;

/* USER CODE END PTD */
uint64_t  sensor_values[MAX_VALUES];

uint64_t  sum;
  float average;
  uint64_t  count_adc = 0;


  uint64_t  sensor_values1[MAX_VALUES1];

  uint64_t  sum1;
    float average1;
    uint64_t  count_adc1 = 0;


    uint32_t flow_values[MAX_VALUES_flow];

      uint32_t flow_sum;
      float average_flow;
      int flow_count = 0;

      float last_Stored_value;
      uint32_t flow_values1[MAX_VALUES_flow1];

         uint32_t flow_sum1;
         float average_flow1;
         int flow_count1 = 0;


         float last_frequency = 0.00;
         float last_frequency1 = 0.00;
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc3;

LTDC_HandleTypeDef hltdc;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LTDC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM13_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */
static void MX_GPIO_Init(void);
void rgb_mixer_create_ui(void);
void show_text(void);
void lv_example_dropdown_1(void);
void lv_example_dropdown_2(void);
void lv_example_img_1(void);
void show_text1(uint32_t adc_temperature , uint32_t adc_flow_rate, uint32_t adc_temperature_1,uint32_t adc_flow_rate_1);
void toggle_image_visibility(void);
void toggle_txt_visibility(void);
void update_values(uint32_t adc_temperature ,uint32_t adc_flow_rate, uint32_t adc_temperature_1, uint32_t adc_flow_rate_1);
//void show_text1(void);
void lv_example_btn_1(void);
void lv_example_dropdown_BYPASS(void);
void transmit_value_via_uart(void);

void flow_settings(void);
void temp_settings(void);
void toggle_txt_visibility_temp(void);

void toggle_txt_visibility_off(void);
void toggle_image_visibility_off(void);

void trip_point_of_leak(void);

void two_channels_adc_calculation(void);
void stuck_logic(void);

void leak_response_dropdown(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void ADC_Select_CH0 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_0;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}
void ADC_Select_CH8 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_8;
	  sConfig.Rank = 2;
	  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
//if (timer10s_flag1==Stabilization_delay)
//{
////	timer10s_flag1=0;
//}
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  	  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  	  MX_GPIO_Init();
  	  MX_LTDC_Init();
  	  MX_USART1_UART_Init();
  	  MX_ADC3_Init();
  	  MX_TIM2_Init();
	  MX_TIM3_Init();
  	  MX_TIM13_Init();
  	  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
  /* Enable I-Cache */
  	  SCB_EnableICache();

  /* Enable D-Cache */
  	  SCB_EnableDCache();
  	  MX_GPIO_Init();

	  lv_init();

	  tft_init();

	  touchpad_init();

	  show_text();
	  show_text1(adc_temperature ,adc_flow_rate,adc_temperature_1,adc_flow_rate_1);
	  lv_example_dropdown_1();

	  lv_example_dropdown_2();

	  lv_example_img_1();

	  lv_example_btn_1();

	  HAL_TIM_IC_Start_IT(&htim13,TIM_CHANNEL_1);

	  HAL_TIM_IC_Start_IT(&htim14,TIM_CHANNEL_1);

	  HAL_TIM_Base_Start_IT(&htim2);
//	  HAL_Delay(5000);
	  HAL_TIM_Base_Start_IT(&htim3);

//	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
	  lv_example_dropdown_BYPASS();

	  img_obj = lv_img_create(lv_scr_act());  // Create image object on the active screen
	  lv_img_set_src(img_obj, &leakage_warning_1);  // Set the image source
	  lv_obj_set_size(img_obj, 40, 33);
	  lv_obj_align(img_obj, LV_ALIGN_OUT_TOP_MID, 180, 25);
	  lv_obj_add_flag(img_obj, LV_OBJ_FLAG_HIDDEN);

	  warning_lable = lv_label_create(lv_scr_act());
	  warning_lable1 = lv_label_create(lv_scr_act());

	  lv_style_t style;
	  lv_style_init(&style);


	  lv_obj_align(warning_lable, LV_ALIGN_TOP_MID, 50, 50);
	  lv_label_set_text(warning_lable, "FLOW WARNING");
	  lv_obj_add_flag(warning_lable, LV_OBJ_FLAG_HIDDEN);
	  lv_obj_add_style(warning_lable, &style, LV_PART_MAIN); // Apply style to the label
//	      lv_obj_set_style_bg_color(warning_lable, lv_color_hex(0xFF0000), LV_PART_MAIN);
	  lv_obj_set_style_text_color(warning_lable, lv_color_hex(0xFF0000), LV_PART_MAIN);
	  // Position the image in the middle of the screen
	  lv_obj_align(warning_lable1, LV_ALIGN_TOP_MID, 50, 50);
	  lv_label_set_text(warning_lable1, "TEMP WARNING");
	  lv_obj_add_flag(warning_lable1, LV_OBJ_FLAG_HIDDEN);
	  lv_obj_add_style(warning_lable1, &style, LV_PART_MAIN); // Apply style to the label
	  lv_obj_set_style_text_color(warning_lable1, lv_color_hex(0xFF0000), LV_PART_MAIN);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)

  {

	 if (programStarted) {

	 update_values(adc_temperature ,adc_flow_rate,adc_temperature_1,adc_flow_rate_1);
	 two_channels_adc_calculation();
	 stuck_logic();
	 trip_point_of_leak();
	 flow_settings();
	 temp_settings();
	 leak_response_dropdown();
    /* USER CODE BEGIN 3 */
	 transmit_value_via_uart();
	 lv_tick_inc(10);
	 lv_task_handler();


  }
//	 programStarted=0;
  /* USER CODE END 3 */
}
}

void two_channels_adc_calculation(void)
{
	ADC_Select_CH0();
		  HAL_ADC_Start(&hadc3);
		 // printf ("Sensor Value = %d \n\r", sensor_value); // Running at 38400, though set at 115200
		  sensor_value= HAL_ADC_GetValue(&hadc3);
		  HAL_ADC_PollForConversion(&hadc3, 1000);
		  HAL_ADC_Stop(&hadc3);
		  sensor_values[count_adc] = sensor_value;

			  sum = sum + sensor_value;
			  count_adc++;

			  if (count_adc >= MAX_VALUES)
			  {
				  average = (float)sum / MAX_VALUES;

					  temp1=(((average*0.00080566*1.232)-1)*1000)-39;

					  temp1=((temp1-1000)/(1000*0.00391))-100;

					  count_adc = 0;
					         sum = 0;
			  }

				  if (celcious_flag)
				  {
					  temp1=(((average*0.00080566*1.232)-1)*1000)-39;

					  temp1=((temp1-1000)/(1000*0.00391))-100;
				  }

					if (fahrenheit_flag)
					{

					  temp1=(((average*0.00080566*1.232)-1)*1000)-39;

					  temp1=((temp1-1000)/(1000*0.00391))-100;

					  temp1=(temp1 * 9/5) + 32;
					}
		  //adc1

		  ADC_Select_CH8();
		 	  HAL_ADC_Start(&hadc3);
		 	 // printf ("Sensor Value = %d \n\r", sensor_value); // Running at 38400, though set at 115200
		 	  sensor_value1= HAL_ADC_GetValue(&hadc3);
		 	  HAL_ADC_PollForConversion(&hadc3, 1000);
		 	  HAL_ADC_Stop(&hadc3);
		 	  sensor_values[count_adc1] = sensor_value1;

		 		  sum1 = sum1 + sensor_value1;
		 		  count_adc1++;

		 		  if (count_adc1 >= MAX_VALUES1)
		 		  {
		 			  average1 = (float)sum1 / MAX_VALUES1;

		 				  temp2=(((average1*0.00080566*1.232)-1)*1000)-39;

		 				  temp2=((temp2-1000)/(1000*0.00391))-100;


		 				  count_adc1 = 0;
		 				         sum1 = 0;
		 		  }
		 		  if (celcious_flag)
		 		  {
 				  temp2=(((average1*0.00080566*1.232)-1)*1000)-39;

	 				  temp2=((temp2-1000)/(1000*0.00391))-100;
		 		  }
					if (fahrenheit_flag)
					{
		 			temp2=(((average1*0.00080566*1.232)-1)*1000)-39;

			 		temp2=((temp2-1000)/(1000*0.00391))-100;
					temp2=(temp2 * 9/5) + 32;
					}


}

void trip_point_of_leak(void)
{
	if(timer10s_flag>=slow_leak_delay_value)
{
	   if (calculate_flow)
	   {
		    trip_point= average_flow - average_flow1;
//	 		   average_flow
			 if (trip_point >= slow_leak_difference_value)
		    {
			 toggle_image_visibility();
			 toggle_txt_visibility();
			 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);   //
			 HAL_Delay(10);

		    }
			 else
			 {
				toggle_image_visibility_off();
				toggle_txt_visibility_off();
			 }

	   }
//	 	  timer10s_flag=0;
}
}

void leak_response_dropdown(void)
{
	if  (Normal_Flag)
	{
    	if ((average_flow - average_flow1) >= 0)
    		 		    {
    		 toggle_image_visibility();
    		 toggle_txt_visibility();
    		 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);   //
    		 HAL_Delay(10);
	}
	}
	if ( Open_Flag)
	{
    	if ((average_flow - average_flow1) >= 1)
    		 		    {
    		 toggle_image_visibility();
    		 toggle_txt_visibility();
    		 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);   //
    		 HAL_Delay(10);
	}
	}
	if  (Presize_Flag)
	{
    	if ((average_flow - average_flow1) >= 1.50)
    		 		    {
    		 toggle_image_visibility();
    		 toggle_txt_visibility();
    		 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);   //
    		 HAL_Delay(10);
	}
}
}
void stuck_logic(void)
{
	 if (average_flow == average_flow )
				{
			stuck_counter++;
					if (stuck_counter == STUCK_THRESHOLD)
					{
						// Reset flow calculation if stuck
						average_flow = 0.00;

					   stuck_counter = 0;  // Reset stuck counter
					}
				}
		if (average_flow1 == average_flow1 )
						{
					stuck_counter1++;
							if (stuck_counter1 == STUCK_THRESHOLD1)
							{
								// Reset flow calculation if stuck
								average_flow1 = 0.00;

							   stuck_counter1 = 0;  // Reset stuck counter
							}
						}

//
//		if (average_flow1>=average_flow)
//		{
//			average_flow1=average_flow-
//		}
}

void flow_settings(void)
{
//	for flow settings
//    		    	flow warning
    		    	if (average_flow<flow_warning_value)
    		                            	{
    		 			 toggle_image_visibility();
    		 			 toggle_txt_visibility();
    		                            	}
    		    	//flow fault
//    		    	if (average_flow<flow_fault_value)
//    		    		{
//    		    		 NVIC_SystemReset();
//    		 		 }

}



void temp_settings(void)
{
//if (temp2>=outlet_temp)
//{
//		 			 toggle_image_visibility();
//		 			toggle_txt_visibility_temp();
//		 			 HAL_Delay(100);
//
//}
//
//
//else if (temp2>=outlet_temp1)
//{
//	{
//	   	 NVIC_SystemReset();
//	    }
//
//}
//	else if (temp1-temp2>=differential_temp)
//	{
//		 toggle_image_visibility();
//		 toggle_txt_visibility_temp();
//	}
//
//	else if (temp1-temp2>=differential_temp1)
//
//		{
//			   	 NVIC_SystemReset();
//			    }
//


//	thermal_load_settings

	m=average_flow1*1/60;
	thermal_load_calculations=m*4186*temp2-initialtemp;

	if (thermal_load_calculations>=thermal_load)
	{
		 toggle_image_visibility();
		 toggle_txt_visibility_temp();
		 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);   //
		 HAL_Delay(10);
	}

	if (thermal_load_calculations>=thermal_load1)
	{

			   	 NVIC_SystemReset();

	}

	density = 999.84 * (1 -( temperature - 4)  *0.000214);


}


void transmit_value_via_uart(void) {

char msg[7];  // Buffer to hold the value (max 3 digits + null terminator)
int len = 0;

char msg1[7];  // Buffer to hold the value (max 3 digits + null terminator)
int len1 = 0;

char msg2[7];  // Buffer to hold the value (max 3 digits + null terminator)
int len2 = 0;

char msg3[7];  // Buffer to hold the value (max 3 digits + null terminator)
int len3 = 0;

// Check if flow_warning_value is available (you can use a condition here to decide when to transmit)
if (flow_warning_value != 0)
{  // Example: check if flow_warning_value is non-zero
len = sprintf(msg, "%d\n", flow_warning_value);  // Format the flow_warning_value as a string
if (len > 0)
{
HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);  // Transmit it over UART1
}
}

// Check if flow_fault_value is available (you can use a condition here to decide when to transmit)
if (flow_fault_value != 0)
{  // Example: check if flow_fault_value is non-zero
len1 = sprintf(msg1, "%d\n", flow_fault_value);  // Format the flow_fault_value as a string
if (len1 > 0)
{
HAL_UART_Transmit(&huart1, (uint8_t*)msg1, len1, HAL_MAX_DELAY);  // Transmit it over UART1
}
}


if (slow_leak_difference_value != 0)
{  // Example: check if flow_warning_value is non-zero
len2 = sprintf(msg2, "%d\n", slow_leak_difference_value);
// Format the flow_warning_value as a string
if (len2 > 0)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)msg2, len, HAL_MAX_DELAY);  // Transmit it over UART1
}
}

// Check if flow_fault_value is available (you can use a condition here to decide when to transmit)
if (slow_leak_delay_value != 0)
{  // Example: check if flow_fault_value is non-zero
len3 = sprintf(msg3, "%d\n", slow_leak_delay_value);  // Format the flow_fault_value as a string

if (len3 > 0)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)msg3, len1, HAL_MAX_DELAY);  // Transmit it over UART1
}
}


}
void toggle_image_visibility(void) {
    if (img_obj != NULL) {
        // Toggle visibility based on the current state
        if (img_visible) {
            lv_obj_add_flag(img_obj, LV_OBJ_FLAG_HIDDEN);  // Hide the image

        } else {
            lv_obj_clear_flag(img_obj, LV_OBJ_FLAG_HIDDEN);  // Show the image

        }
        img_visible = !img_visible;  // Toggle the visibility flag
        HAL_Delay(10);

    }
}
void toggle_image_visibility_off(void)
{
    if (img_obj != NULL)
    {
        // Keep the image hidden without toggling
        lv_obj_add_flag(img_obj, LV_OBJ_FLAG_HIDDEN);  // Hide the image
        img_visible = false;  // Ensure the flag is set to false, no toggling
        HAL_Delay(10);  // Delay
    }
}
void toggle_txt_visibility_off(void)
{
    if (warning_lable != NULL) {
        // Keep the text hidden without toggling
        lv_obj_add_flag(warning_lable, LV_OBJ_FLAG_HIDDEN);  // Hide the warning label
        txt_visible = false;  // Ensure the flag is set to false, no toggling
        HAL_Delay(10);  // Delay
    }
}


void toggle_txt_visibility(void)
{
    if (warning_lable != NULL) {
        // Toggle visibility based on the current state
        if (txt_visible) {

            lv_obj_add_flag(warning_lable, LV_OBJ_FLAG_HIDDEN);  // Hide the warning label
        } else {
             // Show the image
            lv_obj_clear_flag(warning_lable, LV_OBJ_FLAG_HIDDEN);  // Show the warning label
        }
        txt_visible = !txt_visible;  // Toggle the visibility flag
        HAL_Delay(10);
    }
}

void toggle_txt_visibility_temp(void)
{
    if (warning_lable1 != NULL) {
        // Toggle visibility based on the current state
        if (txt_visible) {

            lv_obj_add_flag(warning_lable1, LV_OBJ_FLAG_HIDDEN);  // Hide the warning label
        } else {
             // Show the image
            lv_obj_clear_flag(warning_lable1, LV_OBJ_FLAG_HIDDEN);  // Show the warning label
        }
        txt_visible = !txt_visible;  // Toggle the visibility flag
        HAL_Delay(10);
        lv_task_handler();
    }
}

static void event_handler_bypass_btn(lv_event_t * e)
{
	lv_event_code_t code1 = lv_event_get_code(e);


	lv_obj_t * obj = lv_event_get_target(e);
	void* user_data_leakage = lv_event_get_user_data(e); // Get the user data (the ID we passed)
	int id = (int) user_data_leakage; // Cast the user data to an integer ID
	if(code1 == LV_EVENT_VALUE_CHANGED) {
    char buf[32];
    lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
    LV_LOG_USER("Option: %s", buf);

    if(id == 1) {
               // Valve 1 dropdown selected
               if(strcmp(buf, "On") == 0) {
                   // Valve 1 is ON, set RA5 pin
                   LV_LOG_USER("Valve 1 is ON. Setting RA5 pin...");
                   calculate_flow = false;
   				toggle_image_visibility_off();
   				toggle_txt_visibility_off();
               }
               else if(strcmp(buf, "Off") == 0) {
                   // Valve 1 is OFF, reset RA5 pin
                   LV_LOG_USER("Valve 1 is OFF. Resetting RA5 pin...");
                   calculate_flow = true;  // Enable calculations
               }
           }
}

}

void lv_example_dropdown_BYPASS(void)
{
    lv_obj_t * dd2 = lv_dropdown_create(lv_scr_act());
    lv_dropdown_set_options(dd2, "On\n"
                            "Off");

    lv_obj_set_style_pad_left(dd2, 7, 0);  // Left padding for options
    lv_obj_set_style_pad_right(dd2, 7, 0); // Right padding for options
    lv_obj_set_style_pad_top(dd2, 0, 0);   // Top padding for options
    lv_obj_set_style_pad_bottom(dd2, 7, 0); // Bottom padding for options

    lv_dropdown_set_selected(dd2, 1);

   lv_obj_align(dd2, LV_ALIGN_LEFT_MID, 140, 38); // Align dropdown next to the label at (X + 60)
   lv_obj_set_size(dd2, 70, 25);
   lv_obj_add_event_cb(dd2, event_handler_bypass_btn, LV_EVENT_ALL, NULL);
   lv_obj_add_event_cb(dd2, event_handler_bypass_btn, LV_EVENT_ALL, (void*) 1);
}

void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
if (__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE) != RESET)
	{
	__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
	timer10s_flag++;  // Set the flag to indicate that 10 seconds have passed
//  HAL_TIM_IRQHandler(&htim3);

}
}

void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET)
	{
	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
		timer10s_flag1++;

      if (timer10s_flag1 >= Stabilization_delay && programStarted == 0) {
          programStarted = 1;  // Set the program start flag
          timer10s_flag1 = 0;   // Reset the counter if needed
      }

}
}

//
//
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//    float refClock = TIMCLOCK / PRESCALAR;
//
//    // For TIM13 Channel 1
//    if (htim->Instance == TIM13 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//    {
//        if (Is_First_Captured_TIM13 == 0) // If the first rising edge is not captured
//        {
//            IC_Val1_TIM13 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // Read the first value
//            Is_First_Captured_TIM13 = 1;  // Set the first captured as true
//
//            // Optional: Add validity check for the first captured value
//            // Example: If the first captured value is suspiciously low or high, reset and wait for a valid first edge
//            if (IC_Val1_TIM13 < MIN_VALID_CAPTURE || IC_Val1_TIM13 > MAX_VALID_CAPTURE)
//            {
//                Is_First_Captured_TIM13 = 0;  // Reset the flag, discard invalid capture
//                return;  // Exit early and wait for a valid edge
//            }
//        }
//        else  // If the first rising edge is captured, now we will capture the second edge
//        {
//            IC_Val2_TIM13 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // Read second value
//
//            // Calculate the difference between the two captured values
//            if (IC_Val2_TIM13 > IC_Val1_TIM13)
//            {
//                Difference_TIM13 = IC_Val2_TIM13 - IC_Val1_TIM13;
//            }
//            else if (IC_Val1_TIM13 > IC_Val2_TIM13)
//            {
//                Difference_TIM13 = (0xffff - IC_Val1_TIM13) + IC_Val2_TIM13;
//            }
//
//            // Optional: Add a check for an unusually large difference between captures
//            if (Difference_TIM13 > MAX_VALID_PULSE_PERIOD)  // MAX_VALID_PULSE_PERIOD is the maximum period threshold
//            {
//                frequency_TIM13 = 0.0; // No valid pulse, set frequency to 0
//            }
//
//            // Calculate the frequency and apply the LPM formula for inlet
//            frequency_TIM13 = refClock / Difference_TIM13;
////            frequency_TIM13 = (frequency_TIM13 * 0.1861) - 0.2;  // LPM formula adjustment
//
//            if (mode == true) {
//                frequency_TIM13 = (frequency_TIM13 * 0.1861) - 0.2; // LPM formula
//            } else if (mode == false) {
//                frequency_TIM13 = ((frequency_TIM13 * 0.1861) - 0.2) * 0.264172; // GPM formula
//            }
//            frequency_TIM13 = 0.1 * frequency_TIM13 + 0.9 * last_frequency;
//            last_frequency = frequency_TIM13;
//            // Store the frequency in the flow_values array
//            flow_values[flow_count] = frequency_TIM13;
//
//            // Update the sum and count for averaging
//            flow_sum += frequency_TIM13;
//            flow_count++;
//
//            if (flow_count >= MAX_VALUES_flow)
//            {
//                average_flow = (float)flow_sum / MAX_VALUES_flow;
//                flow_count = 0;
//                flow_sum = 0;
//            }
//
//            // Reset average flow if it exceeds 50
//            if (average_flow >= 50)
//            {
//                average_flow = 0.00;
//            }
//
//            // Reset the timer counter to keep track of the next capture period
//            __HAL_TIM_SET_COUNTER(htim, 0);  // Reset the counter
//            Is_First_Captured_TIM13 = 0; // Reset the capture flag for the next cycle
//        }
//    }
//
//    // For TIM14 Channel 1
//    else if (htim->Instance == TIM14 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//    {
//        if (Is_First_Captured_TIM14 == 0) // If the first rising edge is not captured
//        {
//            IC_Val1_TIM14 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // Read the first value
//            Is_First_Captured_TIM14 = 1;  // Set the first captured as true
//
//            // Optional: Add validity check for the first captured value
//            if (IC_Val1_TIM14 < MIN_VALID_CAPTURE || IC_Val1_TIM14 > MAX_VALID_CAPTURE)
//            {
//                Is_First_Captured_TIM14 = 0;  // Reset the flag, discard invalid capture
//                return;  // Exit early and wait for a valid edge
//            }
//        }
//        else  // If the first rising edge is captured, now we will capture the second edge
//        {
//            IC_Val2_TIM14 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // Read second value
//
//            // Calculate the difference between the two captured values
//            if (IC_Val2_TIM14 > IC_Val1_TIM14)
//            {
//                Difference_TIM14 = IC_Val2_TIM14 - IC_Val1_TIM14;
//            }
//            else if (IC_Val1_TIM14 > IC_Val2_TIM14)
//            {
//                Difference_TIM14 = (0xffff - IC_Val1_TIM14) + IC_Val2_TIM14;
//            }
//
//            // Calculate the frequency and apply the LPM formula for inlet
//            frequency_TIM14 = refClock / Difference_TIM14;
//            frequency_TIM14 = (frequency_TIM14 * 0.1861) - 0.2;
//
//            if (mode == true)
//            {
//                frequency_TIM14 = (frequency_TIM14 * 0.1861) - 0.2; // LPM formula
//            }
//            else if (mode == false) {
//                frequency_TIM14 = ((frequency_TIM14 * 0.1861) - 0.2) * 0.264172; // GPM formula
//            }
//
//            frequency_TIM14 = 0.1 * frequency_TIM14 + 0.9 * last_frequency1;
//            last_frequency1 = frequency_TIM14;
//            // Store the frequency in the flow_values array
//            flow_values1[flow_count1] = frequency_TIM14;
//
//            // Update the sum and count for averaging
//            flow_sum1 += frequency_TIM14;
//            flow_count1++;
//
//            if (flow_count1 >= MAX_VALUES_flow1)
//            {
//                average_flow1 = (float)flow_sum1 / MAX_VALUES_flow1;
//                flow_count1 = 0;
//                flow_sum1 = 0;
//            }
//
//            // Reset average flow if it exceeds 50
//            if (average_flow1 >= 50)
//            {
//                average_flow1 = 0.00;
//            }
//
//            // Reset the timer counter to keep track of the next capture period
//            __HAL_TIM_SET_COUNTER(htim, 0);  // Reset the counter
//            Is_First_Captured_TIM14 = 0; // Reset the capture flag
//        }
//    }
//
//}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    float refClock = TIMCLOCK / PRESCALAR;

    // Constants for noise filtering
    const uint32_t MIN_VALID_PERIOD = 100;      // Minimum valid capture period
    const uint32_t MAX_VALID_PERIOD = 60000;   // Maximum valid capture period
    const float MAX_ALLOWED_CHANGE = 50.0;     // Maximum allowed change in frequency
    const uint32_t MAX_CAPTURE_TIMEOUT = 1000; // Timeout in ms for valid capture

    static uint32_t last_capture_time_TIM13 = 0;
    static uint32_t last_capture_time_TIM14 = 0;

    // For TIM13 Channel 1
    if (htim->Instance == TIM13 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        uint32_t current_time = HAL_GetTick();

        // Timeout handling
        if ((current_time - last_capture_time_TIM13) > MAX_CAPTURE_TIMEOUT)
        {
            Is_First_Captured_TIM13 = 0;
            __HAL_TIM_SET_COUNTER(htim, 0);
        }
        last_capture_time_TIM13 = current_time;

        if (Is_First_Captured_TIM13 == 0) // First rising edge
        {
            IC_Val1_TIM13 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            Is_First_Captured_TIM13 = 1;

            // Discard invalid initial capture values
            if (IC_Val1_TIM13 < MIN_VALID_PERIOD || IC_Val1_TIM13 > MAX_VALID_PERIOD)
            {
                Is_First_Captured_TIM13 = 0;
                return;
            }
        }
        else // Second rising edge
        {
            IC_Val2_TIM13 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

            // Calculate the difference
            if (IC_Val2_TIM13 > IC_Val1_TIM13)
                Difference_TIM13 = IC_Val2_TIM13 - IC_Val1_TIM13;
            else
                Difference_TIM13 = (0xFFFF - IC_Val1_TIM13) + IC_Val2_TIM13;

            // Discard invalid differences
            if (Difference_TIM13 < MIN_VALID_PERIOD || Difference_TIM13 > MAX_VALID_PERIOD)
            {
                frequency_TIM13 = 0.0;
                Is_First_Captured_TIM13 = 0;
                __HAL_TIM_SET_COUNTER(htim, 0);
                return;
            }

            // Calculate frequency
            frequency_TIM13 = refClock / Difference_TIM13;

            // Apply flow-specific formulas
            if (mode)
                frequency_TIM13 = (frequency_TIM13 * 0.1861) - 0.2; // LPM formula
            else
                frequency_TIM13 = ((frequency_TIM13 * 0.1861) - 0.2) * 0.264172; // GPM formula

            // Apply exponential moving average
            frequency_TIM13 = 0.1 * frequency_TIM13 + 0.9 * last_frequency;
            last_frequency = frequency_TIM13;

            // Check for large changes
            if ((frequency_TIM13 - last_frequency) > MAX_ALLOWED_CHANGE)
            {
                Is_First_Captured_TIM13 = 0;
                __HAL_TIM_SET_COUNTER(htim, 0);
                return;
            }

            // Update flow values and averaging
            flow_values[flow_count] = frequency_TIM13;
            flow_sum += frequency_TIM13;
            flow_count++;

            if (flow_count >= MAX_VALUES_flow)
            {
                average_flow = flow_sum / MAX_VALUES_flow;
                flow_count = 0;
                flow_sum = 0;
            }

            // Reset average flow if it exceeds 50
            if (average_flow >= 50)
                average_flow = 0.0;

            // Reset timer and flags
            __HAL_TIM_SET_COUNTER(htim, 0);
            Is_First_Captured_TIM13 = 0;
        }
    }

    // For TIM14 Channel 1
    else if (htim->Instance == TIM14 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        uint32_t current_time = HAL_GetTick();

        // Timeout handling
        if ((current_time - last_capture_time_TIM14) > MAX_CAPTURE_TIMEOUT)
        {
            Is_First_Captured_TIM14 = 0;
            __HAL_TIM_SET_COUNTER(htim, 0);
        }
        last_capture_time_TIM14 = current_time;

        if (Is_First_Captured_TIM14 == 0) // First rising edge
        {
            IC_Val1_TIM14 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            Is_First_Captured_TIM14 = 1;

            // Discard invalid initial capture values
            if (IC_Val1_TIM14 < MIN_VALID_PERIOD || IC_Val1_TIM14 > MAX_VALID_PERIOD)
            {
                Is_First_Captured_TIM14 = 0;
                return;
            }
        }
        else // Second rising edge
        {
            IC_Val2_TIM14 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

            // Calculate the difference
            if (IC_Val2_TIM14 > IC_Val1_TIM14)
                Difference_TIM14 = IC_Val2_TIM14 - IC_Val1_TIM14;
            else
                Difference_TIM14 = (0xFFFF - IC_Val1_TIM14) + IC_Val2_TIM14;

            // Discard invalid differences
            if (Difference_TIM14 < MIN_VALID_PERIOD || Difference_TIM14 > MAX_VALID_PERIOD)
            {
                frequency_TIM14 = 0.0;
                Is_First_Captured_TIM14 = 0;
                __HAL_TIM_SET_COUNTER(htim, 0);
                return;
            }

            // Calculate frequency
            frequency_TIM14 = refClock / Difference_TIM14;

            // Apply flow-specific formulas
            if (mode)
                frequency_TIM14 = (frequency_TIM14 * 0.1861) - 0.2; // LPM formula
            else
                frequency_TIM14 = ((frequency_TIM14 * 0.1861) - 0.2) * 0.264172; // GPM formula

            // Apply exponential moving average
            frequency_TIM14 = 0.1 * frequency_TIM14 + 0.9 * last_frequency1;
            last_frequency1 = frequency_TIM14;

            // Check for large changes
            if ((frequency_TIM14 - last_frequency1) > MAX_ALLOWED_CHANGE)
            {
                Is_First_Captured_TIM14 = 0;
                __HAL_TIM_SET_COUNTER(htim, 0);
                return;
            }

            // Update flow values and averaging
            flow_values1[flow_count1] = frequency_TIM14;
            flow_sum1 += frequency_TIM14;
            flow_count1++;

            if (flow_count1 >= MAX_VALUES_flow1)
            {
                average_flow1 = flow_sum1 / MAX_VALUES_flow1;
                flow_count1 = 0;
                flow_sum1 = 0;
            }

            // Reset average flow if it exceeds 50
            if (average_flow1 >= 50)
                average_flow1 = 0.0;

            // Reset timer and flags
            __HAL_TIM_SET_COUNTER(htim, 0);
            Is_First_Captured_TIM14 = 0;
        }
    }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */

static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc3.Init.ContinuousConvMode = ENABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 2;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 7;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 14;
  hltdc.Init.AccumulatedVBP = 5;
  hltdc.Init.AccumulatedActiveW = 654;
  hltdc.Init.AccumulatedActiveH = 485;
  hltdc.Init.TotalWidth = 660;
  hltdc.Init.TotalHeigh = 487;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 0;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 0;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = 0;
  pLayerCfg1.WindowX1 = 0;
  pLayerCfg1.WindowY0 = 0;
  pLayerCfg1.WindowY1 = 0;
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg1.Alpha = 0;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg1.FBStartAdress = 0;
  pLayerCfg1.ImageWidth = 0;
  pLayerCfg1.ImageHeight = 0;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */
	 __HAL_RCC_TIM2_CLK_ENABLE();

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 65535;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim2.Init.Period = 1666*Stabilization_delay;
  htim2.Init.Period = 1666;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */
	 __HAL_RCC_TIM3_CLK_ENABLE();
  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 65535;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim3.Init.Period = 1666*slow_leak_delay_value;
  htim3.Init.Period = 1666;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);  // Set priority to 0 (highest)
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE END TIM3_Init 2 */

//  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);

}

/**
  * @brief TIM13 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM13_Init(void)
{

  /* USER CODE BEGIN TIM13_Init 0 */

  /* USER CODE END TIM13_Init 0 */

  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM13_Init 1 */

  /* USER CODE END TIM13_Init 1 */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 108000-1;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 6000;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim13, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM13_Init 2 */
//
  /* USER CODE END TIM13_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 108000-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 6000;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim14, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1|LCD_DISP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DCMI_PWR_EN_GPIO_Port, DCMI_PWR_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EXT_RST_GPIO_Port, EXT_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OTG_HS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_HS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_HS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : QSPI_D2_Pin */
  GPIO_InitStruct.Pin = QSPI_D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
  HAL_GPIO_Init(QSPI_D2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_TXD1_Pin RMII_TXD0_Pin RMII_TX_EN_Pin */
  GPIO_InitStruct.Pin = RMII_TXD1_Pin|RMII_TXD0_Pin|RMII_TX_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : FMC_NBL1_Pin FMC_NBL0_Pin FMC_D5_Pin FMC_D6_Pin
                           FMC_D8_Pin FMC_D11_Pin FMC_D4_Pin FMC_D7_Pin
                           FMC_D9_Pin FMC_D12_Pin FMC_D10_Pin */
  GPIO_InitStruct.Pin = FMC_NBL1_Pin|FMC_NBL0_Pin|FMC_D5_Pin|FMC_D6_Pin
                          |FMC_D8_Pin|FMC_D11_Pin|FMC_D4_Pin|FMC_D7_Pin
                          |FMC_D9_Pin|FMC_D12_Pin|FMC_D10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_D7_Pin ULPI_D6_Pin ULPI_D5_Pin ULPI_D3_Pin
                           ULPI_D2_Pin ULPI_D1_Pin ULPI_D4_Pin */
  GPIO_InitStruct.Pin = ULPI_D7_Pin|ULPI_D6_Pin|ULPI_D5_Pin|ULPI_D3_Pin
                          |ULPI_D2_Pin|ULPI_D1_Pin|ULPI_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SPDIF_RX0_Pin */
  GPIO_InitStruct.Pin = SPDIF_RX0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF8_SPDIFRX;
  HAL_GPIO_Init(SPDIF_RX0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SDMMC_CK_Pin SDMMC_D3_Pin SDMMC_D2_Pin PC9
                           PC8 */
  GPIO_InitStruct.Pin = SDMMC_CK_Pin|SDMMC_D3_Pin|SDMMC_D2_Pin|GPIO_PIN_9
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_D6_Pin DCMI_D7_Pin */
  GPIO_InitStruct.Pin = DCMI_D6_Pin|DCMI_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : QSPI_NCS_Pin */
  GPIO_InitStruct.Pin = QSPI_NCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
  HAL_GPIO_Init(QSPI_NCS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FMC_SDNCAS_Pin FMC_SDCLK_Pin FMC_A11_Pin FMC_A10_Pin
                           FMC_BA1_Pin FMC_BA0_Pin */
  GPIO_InitStruct.Pin = FMC_SDNCAS_Pin|FMC_SDCLK_Pin|FMC_A11_Pin|FMC_A10_Pin
                          |FMC_BA1_Pin|FMC_BA0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_VBUS_Pin */
  GPIO_InitStruct.Pin = OTG_FS_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_VBUS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Audio_INT_Pin */
  GPIO_InitStruct.Pin = Audio_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Audio_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FMC_D2_Pin FMC_D3_Pin FMC_D1_Pin FMC_D15_Pin
                           FMC_D0_Pin FMC_D14_Pin FMC_D13_Pin */
  GPIO_InitStruct.Pin = FMC_D2_Pin|FMC_D3_Pin|FMC_D1_Pin|FMC_D15_Pin
                          |FMC_D0_Pin|FMC_D14_Pin|FMC_D13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_P_Pin OTG_FS_N_Pin OTG_FS_ID_Pin */
  GPIO_InitStruct.Pin = OTG_FS_P_Pin|OTG_FS_N_Pin|OTG_FS_ID_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SAI2_MCLKA_Pin SAI2_SCKA_Pin SAI2_FSA_Pin SAI2_SDA_Pin */
  GPIO_InitStruct.Pin = SAI2_MCLKA_Pin|SAI2_SCKA_Pin|SAI2_FSA_Pin|SAI2_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : SAI2_SDB_Pin */
  GPIO_InitStruct.Pin = SAI2_SDB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_SAI2;
  HAL_GPIO_Init(SAI2_SDB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_D5_Pin */
  GPIO_InitStruct.Pin = DCMI_D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(DCMI_D5_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : uSD_Detect_Pin */
  GPIO_InitStruct.Pin = uSD_Detect_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(uSD_Detect_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FMC_A0_Pin FMC_A1_Pin FMC_A2_Pin FMC_A3_Pin
                           FMC_A4_Pin FMC_A5_Pin FMC_A6_Pin FMC_A9_Pin
                           FMC_A7_Pin FMC_A8_Pin FMC_SDNRAS_Pin */
  GPIO_InitStruct.Pin = FMC_A0_Pin|FMC_A1_Pin|FMC_A2_Pin|FMC_A3_Pin
                          |FMC_A4_Pin|FMC_A5_Pin|FMC_A6_Pin|FMC_A9_Pin
                          |FMC_A7_Pin|FMC_A8_Pin|FMC_SDNRAS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_CTRL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_BL_CTRL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_VSYNC_Pin */
  GPIO_InitStruct.Pin = DCMI_VSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(DCMI_VSYNC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SDMMC_D0_Pin */
  GPIO_InitStruct.Pin = SDMMC_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
  HAL_GPIO_Init(SDMMC_D0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TP3_Pin NC2_Pin */
  GPIO_InitStruct.Pin = TP3_Pin|NC2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : PI1 LCD_DISP_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_1|LCD_DISP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : DCMI_PWR_EN_Pin */
  GPIO_InitStruct.Pin = DCMI_PWR_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DCMI_PWR_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_D4_Pin DCMI_D3_Pin DCMI_D0_Pin DCMI_D2_Pin
                           DCMI_D1_Pin */
  GPIO_InitStruct.Pin = DCMI_D4_Pin|DCMI_D3_Pin|DCMI_D0_Pin|DCMI_D2_Pin
                          |DCMI_D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_INT_Pin */
  GPIO_InitStruct.Pin = LCD_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ULPI_NXT_Pin */
  GPIO_InitStruct.Pin = ULPI_NXT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(ULPI_NXT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FMC_SDNME_Pin FMC_SDNE0_Pin */
  GPIO_InitStruct.Pin = FMC_SDNME_Pin|FMC_SDNE0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : PF7 PF6 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : FMC_SDCKE0_Pin */
  GPIO_InitStruct.Pin = FMC_SDCKE0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(FMC_SDCKE0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_STP_Pin ULPI_DIR_Pin */
  GPIO_InitStruct.Pin = ULPI_STP_Pin|ULPI_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
  GPIO_InitStruct.Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : QSPI_D1_Pin QSPI_D3_Pin QSPI_D0_Pin */
  GPIO_InitStruct.Pin = QSPI_D1_Pin|QSPI_D3_Pin|QSPI_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : EXT_RST_Pin */
  GPIO_InitStruct.Pin = EXT_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EXT_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_RXER_Pin */
  GPIO_InitStruct.Pin = RMII_RXER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(RMII_RXER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin RMII_CRS_DV_Pin */
  GPIO_InitStruct.Pin = RMII_REF_CLK_Pin|RMII_MDIO_Pin|RMII_CRS_DV_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DCMI_HSYNC_Pin PA6 */
  GPIO_InitStruct.Pin = DCMI_HSYNC_Pin|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_SCL_Pin LCD_SDA_Pin */
  GPIO_InitStruct.Pin = LCD_SCL_Pin|LCD_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_CLK_Pin ULPI_D0_Pin */
  GPIO_InitStruct.Pin = ULPI_CLK_Pin|ULPI_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
