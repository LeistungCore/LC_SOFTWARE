/* USER CODE BEGIN Header */
/**`
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
#include "adc.h"
#include "ltdc.h"
#include "lwip.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../lvgl/lvgl.h"
#include "../../lv_conf.h"
#include "../../hal_stm_lvgl/tft/tft.h"
#include "../../hal_stm_lvgl/touchpad/touchpad.h"
#include "../lwip/apps/httpd.h"
#include "ssi_process.h"
#include "cgi_process.h"
#include "tcp_client.h"
#include "tcp_server.h"
#define NUM_OF_TAGS		32
#define NUM_OF_CGI		17
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
bool calculate_flow = true;
volatile bool stop_toggling = false;  // Control flag for stopping toggle behavior

//FOR ADC AND INPUT CAPTURE
uint32_t adc_temperature;
uint32_t adc_flow_rate;

uint32_t adc_temperature_1;
uint32_t adc_flow_rate_1;

uint32_t sensor_value,sensor_value1;
uint8_t timer10s_flag = 0;
uint8_t lvgl_flag = 0;
uint8_t timer10s_flag1=0;
volatile int timer_running=0;
volatile int timer_count = 0;    // Counts the number of timer runs
const int max_timer_runs = 2;    // Limit timer to 2 cycles

static lv_obj_t *circle;

volatile uint8_t programStarted = 0;

extern int flow_warning_value;
extern int flow_fault_value;
extern float slow_leak_difference_value;
extern int  slow_leak_delay_value;
extern int Stabilization_delay;

extern bool update_dropdown_flag;

extern int BYPASS_flag;

extern char valve1;
int valve_for_webinterface;
//extern lv_obj_t *dd;
lv_obj_t *dd2;

//extern char valve1;


volatile int prev_slow_leak_difference_value;
volatile int prev_slow_leak_delay_value;
volatile int prev_flow_warning_value;
volatile int prev_flow_fault_value;
volatile int prev_Stabilization_delay;


volatile int prev_outlet_temp ;
volatile int prev_outlet_temp1 ;
volatile int prev_differential_temp ;
volatile int prev_differential_temp1;


extern bool valve_1display1;
extern bool valve_1display;

float int_to_float;

extern int outlet_temp;
extern int outlet_temp1;
extern int differential_temp;
extern int differential_temp1;

extern int celcious_flag;
extern int fahrenheit_flag;


extern int  Normal_Flag;
extern int Open_Flag;
extern int Presize_Flag;

int leak_detected = 0;



int mode = true;

float vp;


float temp1; //FOR TEMP2
float temp2; // FOR TEMP1

float trip_point;

// lv_obj_t *dd;


lv_obj_t* warning_lable;
lv_obj_t* warning_lable1;


#define TIMCLOCK   108000000

#define PRESCALAR  41000


#define MAX_VALUES 45
#define MAX_VALUES1 45

#define  MAX_VALUES_flow 45
#define MAX_VALUES_flow1 45


#define MAX_VALID_CAPTURE 5000
#define MIN_VALID_CAPTURE 10
#define MAX_VALID_PULSE_PERIOD 10000


#define TIMEOUT_PERIOD 1000  // Timeout period in milliseconds (adjust as needed).
#define STUCK_THRESHOLD 500
#define STUCK_THRESHOLD1 500 // Number of cycles to detect stuck condition.

// Declare a global variable to track the timeout period (in callback cycles)
uint32_t no_pulse_timeout_counter = 0;
uint32_t previous_capture_time = 0;  // Store the previous capture time

//FOR FLOW CAPTURE

volatile uint32_t IC_Val1_TIM13 = 0, IC_Val2_TIM13 = 0;
volatile uint32_t IC_Val1_TIM14 = 0, IC_Val2_TIM14 = 0;
volatile uint32_t Difference_TIM13 = 0, Difference_TIM14 = 0;
volatile float frequency_TIM13 = 0, frequency_TIM14 = 0;
volatile uint8_t Is_First_Captured_TIM13 = 0, Is_First_Captured_TIM14 = 0;

uint64_t  sensor_values[MAX_VALUES];

float  sum;
float average;
uint64_t  count_adc = 0;


uint64_t  sensor_values1[MAX_VALUES1];

float  sum1;
float average1;
uint64_t  count_adc1 = 0;


uint32_t flow_values[MAX_VALUES_flow];

float flow_sum;
float average_flow=0; // FOR FLOW 1
int flow_count = 0;

float last_Stored_value;
uint32_t flow_values1[MAX_VALUES_flow1];

float flow_sum1;
float average_flow1=0; //FOR FLOW 2
int flow_count1 = 0;


float last_frequency = 0.00;
float last_frequency1 = 0.00;


float  Vout_final;
float  Vout;
float  R_PT1000;

float  Vout_final_1;
float  Vout_1;
float  R_PT1000_1;


float flow_offset=0.5;



#define PULSE_TIMEOUT 1000


uint32_t last_capture_time_TIM13 = 0;
uint32_t last_capture_time_TIM14 = 0;


#define FLASH_SECTOR7_ADDRESS 0x080C0000 // Must be word-aligned (multiple of 4)
#define FLASH_MAX_ADDRESS     0x080FFFFF
#define FLASH_SECTOR           FLASH_SECTOR_7



#define TFT_HOR_RES  480   // Adjust based on your display
#define TFT_VER_RES  272

extern struct netif gnetif;
extern char const** tags;
extern tCGI CGI_ARR[2];
extern const tCGI LED_CGI;
extern const tCGI SETUP_CGI;
extern char const reflect[7];
uint32_t sensor_value,sensor_value1;
float temp1,temp2;
uint32_t flow_value,flow_value1;
char count,count1,count2;
uint32_t sys_count1, sys_count2,sys_count_diff;

extern int valve_toggle_flag;
char ip_str[16];



extern bool BYPASS;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern SDRAM_HandleTypeDef hsdram1;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//extern struct netif gnetif;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
void adc_calculations(void);
void trip_point_of_leak(void);

void two_channels_adc_calculation(void);
void stuck_logic(void);

void leak_response_dropdown(void);

void Check_Pulse_Timeout(void);

void Flash_Write_Data(void);
void Flash_Read_Data(void);
void Flash_Erase_Sector7(void);

void display_ip_address(void);
void create_dropdown(void);
void update_dropdown(void);

void update_BYPASS_dropdown(void);

void create_dropdown_valve2(void);
void update_dropdown_valve2(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
	return ch;
}
void ethernet_link_status_updated(struct netif *netif)
{
	if(netif_is_link_up(netif))
	{
		printf("Cable connected \n\r"); //Cable connection status over UART1
	}
	else
	{
		printf("No Cable \n\r"); // Send Cable connection status over UART1
	}
}
void ethernetif_notify_conn_changed(struct netif *netif)
{

	if(netif_is_link_up(netif))
	{
		printf("Cable is connected !! \n\r;");//Cable connection status over UART1
	}
	else
	{
		printf("Cable is disconnected !! \n\r");//Cable connection status over UART1
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
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_FMC_Init();
  MX_LWIP_Init();


  while (gnetif.ip_addr.addr == 0) {
        MX_LWIP_Process();
    }

    tcp_client_init();
    tcp_server_init();
  /* USER CODE BEGIN 2 */
	/* Enable I-Cache */
	//  ethernetif_notify_conn_changed(&gnetif);
	httpd_init();

	http_set_ssi_handler(ssi_handler,tags,NUM_OF_TAGS);
	CGI_ARR[0] = LED_CGI;
	CGI_ARR[1] = SETUP_CGI;
	http_set_cgi_handlers(CGI_ARR, NUM_OF_CGI);
	MPU_Config();
	SDRAM_Initialization_Sequence(&hsdram1);

	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
	MX_GPIO_Init();


	Flash_Read_Data();

	lv_init();

	tft_init();

	touchpad_init();

	show_text();    // FOR MAIN PAGE TEXT

	show_text1(adc_temperature ,adc_flow_rate,adc_temperature_1,adc_flow_rate_1); //UPDATE LIVE VALUES
	lv_example_dropdown_1();  //FOR MAIN PAGEE

	lv_example_dropdown_2();  //FOR SETTING PAGE

	lv_example_img_1(); //FOR IMAGES

	lv_example_btn_1();  //FOR BUTTONS

	HAL_TIM_IC_Start_IT(&htim13,TIM_CHANNEL_1); //FOR FLOW 1 INPUT CAPTURE

	HAL_TIM_IC_Start_IT(&htim14,TIM_CHANNEL_1);//FOR FLOW 2 INPUT CAPTURE

	HAL_TIM_Base_Start_IT(&htim2);  //FOR STABILIZATION DELAT TIMER

	lv_example_dropdown_BYPASS();  //FOR BYPASS DROPDOWN
	//check_spinbox_updates();

	// FOR WARNING TEXT AND IMAGE TOGGLE

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


	//  create_circle();
	// int prev_flag = -1;
	//
	create_dropdown();
	create_dropdown_valve2();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		if (programStarted) {  //FOR STABILIZATION DELAY
			//  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);// Switch on LD1 of EVAL Kit (STM32F746-DISCO)
			MX_LWIP_Process(); // To initiate the LWIP process
			//	 printf("IP Address:  %s \r\n",ip4addr_ntoa(&gnetif.ip_addr)); //Send the ip address assigned
			// ethernetif_notify_conn_changed(&gnetif); // check the cable connection status

			display_ip_address();
			update_values(adc_temperature ,adc_flow_rate,adc_temperature_1,adc_flow_rate_1);
			Flash_Write_Data();
			adc_calculations();
			trip_point_of_leak();
			Check_Pulse_Timeout();
			flow_settings();
			temp_settings();
			leak_response_dropdown();
			update_dropdown();
			update_BYPASS_dropdown();
			update_dropdown_valve2();

			//	      if (update_dropdown_flag != prev_flag) { // Check if flag has changed
			//	            update_circle_color(); // Update color
			//	            prev_flag = update_dropdown_flag; // Store new flag value
			//	        }

//			vp= slow_leak_difference_value * 0.1;
			//transmit_value_via_uart();
			lv_tick_inc(5);
			lv_task_handler();

			HAL_Delay(5);  // Small delay to prevent CPU overuse
		}
	}
}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

void update_circle_color() {
	if (circle == NULL) return; // Ensure the object exists

	if (update_dropdown_flag == 1) {
		lv_obj_set_style_bg_color(circle, lv_color_make(255, 0, 0), 0); // Red
	} else {
		lv_obj_set_style_bg_color(circle, lv_color_make(0, 255, 0), 0); // Green
	}

	lv_obj_invalidate(circle);  // Mark for redraw
}

// Function to create the circle
void create_circle() {
	circle = lv_obj_create(lv_scr_act());
	lv_obj_set_size(circle, 20, 20);
	lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, 0);
	lv_obj_set_style_bg_opa(circle, LV_OPA_COVER, 0);
	lv_obj_align(circle, LV_ALIGN_LEFT_MID, 230, -30);

	update_circle_color(); // Set initial color
}

void display_ip_address() {
	// Ensure the IP address string buffer is large enough
	char ip_str[16];  // Max length of an IPv4 address string is 15 characters + null terminator

	// Convert IP address to a string
	strncpy(ip_str, ip4addr_ntoa(&gnetif.ip_addr), sizeof(ip_str) - 1);
	ip_str[sizeof(ip_str) - 1] = '\0';  // Ensure null termination

	// Check if the label already exists, otherwise create it
	static lv_obj_t *label_ip = NULL;
	if (!label_ip) {
		label_ip = lv_label_create(lv_scr_act());
		lv_obj_align(label_ip, LV_ALIGN_TOP_MID, 120, 10);  // Center at the top
	}

	// Update the label text
	lv_label_set_text_fmt(label_ip, "IP Address : %s", ip_str);
}


void Flash_Erase_Sector(void) {
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SectorError;

	HAL_FLASH_Unlock();

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector = FLASH_SECTOR;
	EraseInitStruct.NbSectors = 1;

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK) {
		// Handle error (optional: log, retry, etc.)
	}

	HAL_FLASH_Lock();
}

uint32_t Flash_Find_Next_Address(void) {
	uint32_t address = FLASH_SECTOR7_ADDRESS;

	while (address < FLASH_MAX_ADDRESS) {
		if (*(uint32_t*)address == 0xFFFFFFFF) {  // Check if empty
			return address;
		}
		address += 36;  // Move to the next 20-byte block (5 * 4 bytes)
	}

	// If full, erase sector and return start address
	Flash_Erase_Sector();
	return FLASH_SECTOR7_ADDRESS;
}

void Flash_Write_Data(void) {
	if (flow_warning_value == prev_flow_warning_value &&
			flow_fault_value == prev_flow_fault_value &&
			Stabilization_delay == prev_Stabilization_delay &&
			slow_leak_difference_value == prev_slow_leak_difference_value &&
			slow_leak_delay_value == prev_slow_leak_delay_value&&

			outlet_temp == prev_outlet_temp &&
			outlet_temp1 == prev_outlet_temp1 &&
			differential_temp == prev_differential_temp &&
			differential_temp1 == prev_differential_temp1)

	{
		return;  // No change, avoid unnecessary flash write
	}

	HAL_FLASH_Unlock();

	uint32_t address = Flash_Find_Next_Address();

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, flow_warning_value);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, flow_fault_value);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, Stabilization_delay);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, slow_leak_difference_value);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, slow_leak_delay_value);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, outlet_temp);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, outlet_temp1);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, differential_temp);
	address += 4;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, differential_temp1);


	HAL_FLASH_Lock();

	// Update previous values
	prev_flow_warning_value = flow_warning_value;
	prev_flow_fault_value = flow_fault_value;
	prev_Stabilization_delay = Stabilization_delay;
	prev_slow_leak_difference_value = slow_leak_difference_value;
	prev_slow_leak_delay_value = slow_leak_delay_value;

	prev_outlet_temp =outlet_temp;
	prev_outlet_temp1 =outlet_temp1;
	prev_differential_temp =differential_temp;
	prev_differential_temp1=differential_temp1;
}

void Flash_Read_Data(void) {
	uint32_t address = FLASH_SECTOR7_ADDRESS;
	uint32_t last_valid_address = FLASH_SECTOR7_ADDRESS;
	uint32_t temp_flow_warning, temp_flow_fault;
	uint32_t temp_stabilization_delay, temp_slow_leak_diff, temp_slow_leak_delay;
	uint32_t temp_outlet_temp, temp_outlet_temp1,temp_differential_temp, temp_differential_temp1;

	while (address < FLASH_MAX_ADDRESS) {
		uint32_t int_value = *(uint32_t*)address;
		uint32_t int_value1 = *(uint32_t*)(address + 4);
		uint32_t int_value2 = *(uint32_t*)(address + 8);
		uint32_t int_value3 = *(uint32_t*)(address + 12);
		uint32_t int_value4 = *(uint32_t*)(address + 16);

		uint32_t int_value5 = *(uint32_t*)(address + 20);
		uint32_t int_value6 = *(uint32_t*)(address + 24);
		uint32_t int_value7 = *(uint32_t*)(address + 28);
		uint32_t int_value8 = *(uint32_t*)(address + 32);

		if (int_value == 0xFFFFFFFF && int_value1 == 0xFFFFFFFF &&
				int_value2 == 0xFFFFFFFF && int_value3 == 0xFFFFFFFF &&
				int_value4 == 0xFFFFFFFF  && int_value5 ==  0xFFFFFFFF && int_value6 ==  0xFFFFFFFF && int_value7 ==  0xFFFFFFFF
				&& int_value8 ==  0xFFFFFFFF) {
			break;  // Stop when we reach an empty block
		}

		// Store last valid values before stopping
		temp_flow_warning = int_value;
		temp_flow_fault = int_value1;
		temp_stabilization_delay = int_value2;
		temp_slow_leak_diff = int_value3;
		temp_slow_leak_delay = int_value4;
		temp_outlet_temp=int_value5;
		temp_outlet_temp1=int_value6;
		temp_differential_temp=int_value7;
		temp_differential_temp1=int_value8;

		last_valid_address = address;
		address += 36; // Move to next 5-value set (5 * 4 bytes)
	}

	// Assign the last valid values found
	flow_warning_value = temp_flow_warning;
	flow_fault_value = temp_flow_fault;
	Stabilization_delay = temp_stabilization_delay;
	slow_leak_difference_value = temp_slow_leak_diff;
	slow_leak_delay_value = temp_slow_leak_delay;

	outlet_temp= temp_outlet_temp;
	outlet_temp1=	temp_outlet_temp1;
	differential_temp=temp_differential_temp;
	differential_temp1=temp_differential_temp1;

	// Initialize previous values with restored data
	prev_flow_warning_value = flow_warning_value;
	prev_flow_fault_value = flow_fault_value;
	prev_Stabilization_delay = Stabilization_delay;
	prev_slow_leak_difference_value = slow_leak_difference_value;
	prev_slow_leak_delay_value = slow_leak_delay_value;

	prev_outlet_temp =outlet_temp;
	prev_outlet_temp1 =outlet_temp1;
	prev_differential_temp =differential_temp;
	prev_differential_temp1=differential_temp1;


}
void adc_calculations(void)
{
	HAL_ADC_Start(&hadc1);  //PF10
	// printf ("Sensor Value = %d \n\r", sensor_value); // Running at 38400, though set at 115200
	sensor_value= HAL_ADC_GetValue(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	HAL_ADC_Stop(&hadc1);
	sensor_values[count_adc] = sensor_value;

	sum = sum + sensor_value;
	count_adc++;

	if (count_adc >= MAX_VALUES)
	{
		average = (float)sum / MAX_VALUES;

		Vout_final=average*0.00080566;
		Vout=(Vout_final*53)/43;
		R_PT1000 =(((Vout/1.092)-1)*1000)-39;
		temp1=(((R_PT1000/1000)-1)/(0.00391)-2);


		count_adc = 0;
		sum = 0;
	}

	if (celcious_flag)
	{


	}

	if (fahrenheit_flag)
	{


	}
	//adc1


	HAL_ADC_Start(&hadc3); //PA0
	// printf ("Sensor Value = %d \n\r", sensor_value); // Running at 38400, though set at 115200
	sensor_value1= HAL_ADC_GetValue(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 1000);
	HAL_ADC_Stop(&hadc3);
	sensor_values1[count_adc1] = sensor_value1;

	sum1 = sum1 + sensor_value1;
	count_adc1++;

	if (count_adc1 >= MAX_VALUES1)
	{
		average1 = (float)sum1 / MAX_VALUES1;


		Vout_final_1=average1*0.00080566;
		Vout_1=(Vout_final_1*53)/43;
		R_PT1000_1 =(((Vout_1/1.092)-1)*1000)-39;
		temp2=(((R_PT1000_1/1000)-1)/(0.00391)-2);

		count_adc1 = 0;
		sum1 = 0;
	}


	if (celcious_flag)
	{


	}
	if (fahrenheit_flag)
	{


	}
}



void trip_point_of_leak(void)
{
	if (calculate_flow)
	{
		trip_point = average_flow1 - average_flow;

		// Start the timer only if trip_point is above threshold
		if (trip_point >= slow_leak_difference_value * 0.1)
		{
			if (!timer_running)
			{
				timer_running = 1;
				timer10s_flag = 0;
				HAL_TIM_Base_Start_IT(&htim3);
			}
		}
		else
		{
			timer_running = 0;
			HAL_TIM_Base_Stop_IT(&htim3);
		}

		// Check if timer has elapsed
		if (timer_running && timer10s_flag >= slow_leak_delay_value)
		{
			trip_point = average_flow1 - average_flow;

			if (trip_point >= slow_leak_difference_value * 0.1)
			{
				leak_detected=1;
				valve_for_webinterface=1;
				valve1=0;
				 valve_1display1=0;
				valve_1display=0;

				update_dropdown_flag = 0;
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);

//				HAL_Delay(20);

			}

			else
			{
				valve_for_webinterface=0;
				toggle_image_visibility_off();
				toggle_txt_visibility_off();
			}

			// **Handle toggling based on stop_toggling**
			if (leak_detected)
			{
				if (!stop_toggling) // Toggle normally
				{
					//	lv_dropdown_set_selected(dd, 1);
					toggle_image_visibility();
					toggle_txt_visibility();
				}
				//                else // If stop_toggling is ON, stop toggling & turn everything OFF
				//                {
				//                    toggle_image_visibility_off();
				//                    toggle_txt_visibility_off();
				//                }
			}

			// **Reset toggling when no leak is detected**
			if (!leak_detected)
			{
				stop_toggling = 0; // Allow toggling in the next detection cycle
			}
		}
	}
}




void leak_response_dropdown(void)
{
	if  (Normal_Flag)
	{
		if ((average_flow1 - average_flow) >= 0)
		{
			toggle_image_visibility();
			toggle_txt_visibility();
			//    		 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);   //
			//    		 HAL_Delay(20);
		}
	}

	if ( Open_Flag)
	{
		if ((average_flow1 - average_flow) >= 1)
		{
			toggle_image_visibility();
			toggle_txt_visibility();
			// HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);   //
			//HAL_Delay(20);
		}
	}
	if  (Presize_Flag)
	{
		if ((average_flow1 - average_flow) >= 1.50)
		{
			toggle_image_visibility();
			toggle_txt_visibility();
			// HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);   //
			//HAL_Delay(2);
		}
	}
}

void flow_settings(void)
{
	//	for flow settings
	//    		    	flow warning
	if (average_flow1<flow_warning_value)
	{
		toggle_image_visibility();
		toggle_txt_visibility();

	}

	//    		    	else
	//    		    	{
	//    		        		    		toggle_image_visibility_off();
	//    		        		    		toggle_txt_visibility_off();
	//    		 }
	//
	//    		    	//flow fault
	if (average_flow1<flow_fault_value)
	{
		//    		    		 NVIC_SystemReset();
		toggle_image_visibility();
		toggle_txt_visibility();
	}
	//    		    	else
	//    		    	{
	//    		    		toggle_image_visibility_off();
	//    		    		toggle_txt_visibility_off();
	//    		    	}

}



void temp_settings(void)
{
	if (temp1>=outlet_temp)
	{
		toggle_image_visibility();
		toggle_txt_visibility_temp();
		//		 			 HAL_Delay(10);

	}
	//
	//
	else if (temp1>=outlet_temp1)
	{
		{
			//	   	 NVIC_SystemReset();

			toggle_image_visibility();
			toggle_txt_visibility_temp();
		}
		//
	}
	//	else if (temp1-temp2>=differential_temp)
	//	{
	//		 toggle_image_visibility();
	//		 toggle_txt_visibility_temp();
	//	}
	//
	//	else if (temp1-temp2>=differential_temp1)
	//
	//		{
	//		 toggle_image_visibility();
	//		 toggle_txt_visibility_temp();
	// }
	//

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
			HAL_UART_Transmit(&huart1, (uint8_t*)msg2, len2, HAL_MAX_DELAY);  // Transmit it over UART1
		}
	}

	// Check if flow_fault_value is available (you can use a condition here to decide when to transmit)
	if (slow_leak_delay_value != 0)
	{  // Example: check if flow_fault_value is non-zero
		len3 = sprintf(msg3, "%d\n", slow_leak_delay_value);  // Format the flow_fault_value as a string

		if (len3 > 0)
		{
			HAL_UART_Transmit(&huart1, (uint8_t*)msg3, len3, HAL_MAX_DELAY);  // Transmit it over UART1
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
		HAL_Delay(2);

	}
}
void toggle_image_visibility_off(void)
{
	if (img_obj != NULL)
	{
		// Keep the image hidden without toggling
		lv_obj_add_flag(img_obj, LV_OBJ_FLAG_HIDDEN);  // Hide the image
		img_visible = false;  // Ensure the flag is set to false, no toggling
		HAL_Delay(2);  // Delay
	}
}
void toggle_txt_visibility_off(void)
{
	if (warning_lable != NULL) {
		// Keep the text hidden without toggling
		lv_obj_add_flag(warning_lable, LV_OBJ_FLAG_HIDDEN);  // Hide the warning label
		txt_visible = false;  // Ensure the flag is set to false, no toggling
		//        HAL_Delay(2);  // Delay
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
		HAL_Delay(2);
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
		HAL_Delay(2);
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
				BYPASS=1;
				// Valve 1 is ON, set RA5 pin
				LV_LOG_USER("Valve 1 is ON. Setting RA5 pin...");
				calculate_flow = false;
				BYPASS_flag=1;
				toggle_image_visibility_off();
				toggle_txt_visibility_off();

			}

			else if
			(strcmp(buf, "Off") == 0) {

				// Valve 1 is OFF, reset RA5 pin
				LV_LOG_USER("Valve 1 is OFF. Resetting RA5 pin...");
				calculate_flow = true;  // Enable calculations
				BYPASS=0;
				BYPASS_flag=0;
			}
		}
	}

}
void update_BYPASS_dropdown(void)
{
	if (dd2 == NULL) return;

	lv_dropdown_set_options(dd2, "Off\nOn");

	// Reverse the logic: 1 = OFF (index 0), 0 = ON (index 1)
	uint16_t target_index_1 = (BYPASS_flag == 1) ? 1 : 0;

	if (lv_dropdown_get_selected(dd2) != target_index_1) {
		lv_dropdown_set_selected(dd2, target_index_1);
		lv_obj_invalidate(dd2);
	}
}
void lv_example_dropdown_BYPASS(void)
{


	dd2 = lv_dropdown_create(lv_scr_act());
	lv_obj_set_style_pad_left(dd2, 7, 0);
	lv_obj_set_style_pad_right(dd2, 7, 0);
	lv_obj_set_style_pad_top(dd2, 0, 0);
	lv_obj_set_style_pad_bottom(dd2, 7, 0);

	lv_obj_align(dd2, LV_ALIGN_LEFT_MID, 140, 38);
	lv_obj_set_size(dd2, 70, 25);

	lv_dropdown_set_options(dd2, "Off\nOn");

	// Reverse the logic here too
	lv_dropdown_set_selected(dd2, BYPASS_flag ? 1 : 0);
	lv_obj_add_event_cb(dd2, event_handler_bypass_btn, LV_EVENT_ALL, (void*) 1);
	//lv_obj_add_event_cb(dd2, event_handler_bypass_btn, LV_EVENT_ALL, NULL);



}

void TIM3_IRQHandler(void)
{
	/* USER CODE BEGIN TIM3_IRQn 0 */
	if (__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE) != RESET)
	{
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
		timer10s_flag++;



	}
}

void TIM2_IRQHandler(void)
{
	/* USER CODE BEGIN TIM3_IRQn 0 */
	if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET)
	{
		__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
		timer10s_flag1++;

		if (timer10s_flag1 >= Stabilization_delay && programStarted == 0)
		{
			programStarted = 1;  // Set the program start flag
			timer10s_flag1 = 0;   // Reset the counter if needed
		}

	}
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	float refClock = TIMCLOCK / PRESCALAR;

	// For TIM13 Channel 1 PF8
	if (htim->Instance == TIM13 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if (Is_First_Captured_TIM13 == 0)
		{
			IC_Val1_TIM13 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			Is_First_Captured_TIM13 = 1;
			last_capture_time_TIM13 = HAL_GetTick();  // Store the current time
		}
		else
		{
			IC_Val2_TIM13 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

			if (IC_Val2_TIM13 > IC_Val1_TIM13)
			{
				Difference_TIM13 = IC_Val2_TIM13 - IC_Val1_TIM13;
			}
			else if (IC_Val1_TIM13 > IC_Val2_TIM13)
			{
				Difference_TIM13 = (65535 - IC_Val1_TIM13) + IC_Val2_TIM13;
			}
			frequency_TIM13 = refClock / Difference_TIM13;
			frequency_TIM13 = (frequency_TIM13 * 0.1861) - 0.2;

			flow_values[flow_count] = frequency_TIM13;
			flow_sum += frequency_TIM13;
			flow_count++;

			if (flow_count >= MAX_VALUES_flow)
			{
				average_flow = (float)flow_sum / MAX_VALUES_flow;
				flow_count = 0;
				flow_sum = 0;
			}

			if (mode == true) {
				//					frequency_TIM13 = (frequency_TIM13 * 0.1861) - 0.2 ; // LPM formula
				//                            frequency_TIM13 = (frequency_TIM13 * 0.1738) + 0.6132 ;
			} else if (mode == false)
			{
				//					frequency_TIM13 = ((frequency_TIM13 * 0.1861) - 0.2 ) * 0.264172; // GPM formula
				//                            frequency_TIM13 = (frequency_TIM13 * 0.1738) + 0.6132 *0.264172;
			}

			if (average_flow >= 50)
				average_flow = 0.00;

			__HAL_TIM_SET_COUNTER(htim, 0);
			Is_First_Captured_TIM13 = 0;
			last_capture_time_TIM13 = HAL_GetTick();  // Reset timeout timer
		}
	}

	// For TIM14 Channel 1 PF9
	else if (htim->Instance == TIM14 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if (Is_First_Captured_TIM14 == 0)
		{
			IC_Val1_TIM14 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			Is_First_Captured_TIM14 = 1;
			last_capture_time_TIM14 = HAL_GetTick();
		}
		else
		{
			IC_Val2_TIM14 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

			if (IC_Val2_TIM14 > IC_Val1_TIM14)
			{
				Difference_TIM14 = IC_Val2_TIM14 - IC_Val1_TIM14;
			}
			else if (IC_Val1_TIM14 > IC_Val2_TIM14)
			{
				Difference_TIM14 = (65535 - IC_Val1_TIM14) + IC_Val2_TIM14;
			}
			frequency_TIM14 = refClock / Difference_TIM14;
			frequency_TIM14 = (frequency_TIM14 * 0.1861) - 0.2;

			flow_values1[flow_count1] = frequency_TIM14;
			flow_sum1 += frequency_TIM14;
			flow_count1++;

			if (flow_count1 >= MAX_VALUES_flow1)
			{
				average_flow1 = (float)flow_sum1 / MAX_VALUES_flow1;
				flow_count1 = 0;
				flow_sum1 = 0;
			}
			if (mode == true)
			{
				//					frequency_TIM14 = (frequency_TIM14 * 0.1861) - 0.2; // LPM formula
				//					 frequency_TIM14 = (frequency_TIM14 * 0.1738) + 0.6132 ;
			}
			else if (mode == false) {
				//					frequency_TIM14 = ((frequency_TIM14 * 0.1861) - 0.2 ) * 0.264172; // GPM formula
				//					 frequency_TIM14 = (frequency_TIM14 * 0.1738) + 0.6132 *0.264172;
			}
			if (average_flow1 >= 50)
				average_flow1 = 0.00;

			__HAL_TIM_SET_COUNTER(htim, 0);
			Is_First_Captured_TIM14 = 0;
			last_capture_time_TIM14 = HAL_GetTick();  // Reset timeout timer
		}
	}
}

// Function to monitor timeout and reset values to 0
void Check_Pulse_Timeout(void)
{
	uint32_t current_time = HAL_GetTick();

	// Timeout for TIM13
	if ((current_time - last_capture_time_TIM13) > PULSE_TIMEOUT)
	{
		frequency_TIM13 = 0.0;
		average_flow = 0.0;
	}

	// Timeout for TIM14
	if ((current_time - last_capture_time_TIM14) > PULSE_TIMEOUT)
	{
		frequency_TIM14 = 0.0;
		average_flow1 = 0.0;
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

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
