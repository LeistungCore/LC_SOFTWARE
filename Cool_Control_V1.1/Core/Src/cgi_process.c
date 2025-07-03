#include "main.h"
#include "cgi_process.h"
#include <string.h>
#include <stdio.h>
#include "lwip/apps/httpd.h"
#include <stdlib.h>
#include "../../lvgl/lvgl.h"
#include "../../lv_conf.h"
#include "../../hal_stm_lvgl/tft/tft.h"
#include "../../hal_stm_lvgl/touchpad/touchpad.h"
extern lv_obj_t * dd;
const char * led_cgi_handler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[]);
const char * CGI_Form_Handler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[]);
const char * setup_cgi_Handler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[]);


const tCGI LED_CGI ={"/leds.cgi", led_cgi_handler};

const tCGI FORM_CGI = {"/form.cgi", CGI_Form_Handler};
const tCGI SETUP_CGI = {"/setup.cgi", setup_cgi_Handler};

char valve1,valve2,BYPASS;
char name[30];
float number=0;


int temp_unit;

//int FloWarning_val;
//int Flofault_val;
//int slowleak_val;
//int slowdelay_val;
//int tempwarning_val;
//int tempfault_val;
//int tempdiffwarning_val;
//int tempdiff_fault_val;

char flow_warning_flag=0;
char flow_fault_flag=0;
char slow_leak_flag=0;
char slow_delay_flag=0;
char temp_warning_flag=0;
char temp_fault_flag=0;
char tempdiff_warning_flag=0;
char tempdiff_fault_flag=0;

char spinbox_stabilization_Delay_flag=0;


extern int flow_warning_value;

//extern int flow_warning_value;
extern int flow_fault_value;
extern float slow_leak_difference_value;
extern int  slow_leak_delay_value;

extern int outlet_temp1;
extern int  outlet_temp;
extern int differential_temp1;
extern int  differential_temp;
extern int Stabilization_delay;



extern int valve_for_webinterface;

char FloWarning[10];
char FlowFault[10];
char SlowLeak[10];
char SlowDelay[10];
char Stabildelay[10];
char leakResponse[10];
char flowUnit[10];
char Tempoutlatewarning[10];
char TempoutlateFault[10];
char TempDiffWarning[10];
char TempDiffFault[10];
char TempUnit[10];
char IPV01[10];
char IPV02[10];
extern float trip_point;
//extern volatile int slow_leak_difference_value;
extern int valve1_leak_detected;
extern bool calculate_flow;
tCGI CGI_ARR[3];
bool update_dropdown_flag=0;
bool valve_2_flag=0;
int BYPASS_flag=0;
extern bool valve_1display;
extern bool valve_1display1;
extern bool valve_1display2;
void toggle_txt_visibility_off(void);
void toggle_image_visibility_off(void);
void toggle_image_visibility(void);
void toggle_txt_visibility(void);
const char * led_cgi_handler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[])
{
	if(iIndex == 0)
	{
		//   ////HAL_GPIO_WritePin(GPIOB, GREEN_LED_Pin|RED_LED_Pin|BLUE_LED_Pin, GPIO_PIN_RE/SET);

		for (int i = 0; i < iNumParams; i++)
		{


			if(strcmp(pcParam[i] ,"valve11") == 0  )
						{

				//change
							if(strcmp(pcValue[i], "1") == 0 )
							{
							valve1=0;
							 valve_1display1=0;
							valve_1display=0;

							HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);
						    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
							update_dropdown_flag = 0;
							toggle_image_visibility_off();
						    toggle_txt_visibility_off();
							}



							else if(strcmp(pcValue[i], "0") == 0 )
							{
								valve1=1;
							valve_1display1=1;
							valve_1display=1;
							HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
							 HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
							update_dropdown_flag = 1;
							}
							}


		if(strcmp(pcParam[i] ,"valve12") == 0  )
								{
									if(strcmp(pcValue[i], "1") == 0)
									{
										valve2=0;
										valve_2_flag=0;
										valve_1display2=0;
									}
									else if(strcmp(pcValue[i], "0") == 0 )
									{
									valve2=1;
									valve_2_flag=1;
									valve_1display2=1;
									}
									}


	if(strcmp(pcParam[i] ,"valve13") == 0  )
							{
								if(strcmp(pcValue[i], "1") == 0)
								{
									BYPASS=0;
									BYPASS_flag=0;
								calculate_flow=1;
								}
								else if(strcmp(pcValue[i], "0") == 0)
								{
								BYPASS=1;
								BYPASS_flag=1;
							    calculate_flow=0;
								toggle_image_visibility_off();
								toggle_txt_visibility_off();
								}
	}

		}

	}

	return "/index.shtml";
}




const char * setup_cgi_Handler(int iIndex, int iNumParams, char *pcParam[],char *pcValue[])
{
	if (iIndex==1)
	{
		for (int i=0;i<iNumParams;i++)
		{
			if (strcmp(pcParam[i],"flowarning1")==0) // To Replace flow warning
			{
				memset (FloWarning,'\0',10);
				strcpy(FloWarning,pcValue[i]);
				flow_warning_value = atoi(pcValue[i]);
				flow_warning_flag=1;
			}
			else if (strcmp(pcParam[i],"Flowfault1")==0) // To replace flow fault value
			{
				memset (FlowFault,'\0',10);
				strcpy(FlowFault,pcValue[i]);
				flow_fault_value = atoi(pcValue[i]);
				flow_fault_flag=1;
			}
			else if (strcmp(pcParam[i],"Slowleak1")==0) // To replace slow leak
			{
				memset (SlowLeak,'\0',10);
				strcpy(SlowLeak,pcValue[i]);
				slow_leak_difference_value = atof(pcValue[i]);
				slow_leak_flag=1;
			}
			else if (strcmp(pcParam[i],"Slowdelay1")==0) // To replace slow delay
			{
				memset (SlowDelay,'\0',10);
				strcpy(SlowDelay,pcValue[i]);
				slow_leak_delay_value = atoi(pcValue[i]);
				slow_delay_flag=1;
			}
			else if (strcmp(pcParam[i],"StabilDelay1")==0) // To replace slow delay
			{
				memset (Stabildelay,'\0',10);
				strcpy(Stabildelay,pcValue[i]);
				Stabilization_delay = atoi(pcValue[i]);
				spinbox_stabilization_Delay_flag=1;

			}
			else if (strcmp(pcParam[i],"Leakresponse1")==0) // To replace slow delay
			{
				memset (leakResponse,'\0',10);
				strcpy(leakResponse,pcValue[i]);
				differential_temp = atoi(pcValue[i]);
				//tempdiff_fault_flag=1;
				//
			}
			else if (strcmp(pcParam[i],"Flowunit1")==0) // To replace slow delay
			{
				memset (flowUnit,'\0',10);
				strcpy(flowUnit,pcValue[i]);
				differential_temp = atoi(pcValue[i]);
				//	tempdiff_fault_flag=1;

			}
			else if (strcmp(pcParam[i],"Tempotlatewarning1")==0) // To replace slow delay
			{
				memset (Tempoutlatewarning,'\0',10);
				strcpy(Tempoutlatewarning,pcValue[i]);

				outlet_temp = atoi(pcValue[i]);
				temp_warning_flag=1;

			}
			else if (strcmp(pcParam[i],"TempoutlteFault1")==0)
			{
				memset (TempoutlateFault,'\0',10);
				strcpy(TempoutlateFault,pcValue[i]);
				outlet_temp1 = atoi(pcValue[i]);
				temp_fault_flag=1;

			}
			else if (strcmp(pcParam[i],"TempDifWarning1")==0)
			{
				memset (TempDiffWarning,'\0',10);
				strcpy(TempDiffWarning,pcValue[i]);
				differential_temp = atoi(pcValue[i]);
				tempdiff_warning_flag=1;

			}
			else if (strcmp(pcParam[i],"TempDifFault1")==0) //
			{
				memset (TempDiffFault,'\0',10);
				strcpy(TempDiffFault,pcValue[i]);
				differential_temp1 = atoi(pcValue[i]);
				tempdiff_fault_flag=1;

			}

			else if (strcmp(pcParam[i],"Tempunit1")==0) //
			{
				memset (TempUnit,'\0',10);
				strcpy(TempUnit,pcValue[i]);
				//									temp_unit = atoi(pcValue[i]);
				temp_unit=1;

			}
			else if (strcmp(pcParam[i],"IP1")==0) // To replace slow delay
			{
				memset (IPV01,'\0',10);
				strcpy(IPV01,pcValue[i]);
				//differential_temp = atoi(pcValue[i]);
				//									tempdiff_fault_flag=1;

			}
			else if (strcmp(pcParam[i],"IP1")==0) // To replace slow delay
			{
				memset (IPV02,'\0',10);
				strcpy(IPV02,pcValue[i]);
				//differential_temp = atoi(pcValue[i]);
				//									tempdiff_fault_flag=1;

			}
		}
		//			printf("vivek");
		printf("FloWarning :%s\r\n",FloWarning);
		printf("FlowFault :%s\r\n",FlowFault);
		printf("SlowLeak :%s\r\n",SlowLeak);
		printf("SlowDelay :%s\r\n",SlowDelay);
		printf("Stabildelay :%s\r\n",Stabildelay);
		printf("leakResponse :%s\r\n",leakResponse);
		printf("flowUnit :%s\r\n",flowUnit);
		printf("Tempoutlatewarning :%s\r\n",Tempoutlatewarning);
		printf("TempoutlateFault :%s\r\n",TempoutlateFault);
		printf("TempDiffWarning :%s\r\n",TempDiffWarning);
		printf("TempDiffFault :%s\r\n",TempDiffFault);
		printf("TempUnit :%s\r\n",TempUnit);
		printf("IPV01 :%s\r\n",IPV01);
		printf("IPV02 :%s\r\n",IPV02);
	}
	return "/setup.shtml";

}






/******************Code Reference*********************/
/*




const tCGI FORM_CGI = {"/form.cgi", CGIForm_Handler};
const tCGI LED_CGI = {"/led.cgi", CGILED_Handler};

char name[30];

tCGI CGI_TAB[2];


const char *CGIForm_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
	if (iIndex == 0)
	{
		for (int i=0; i<iNumParams; i++)
		{
			if (strcmp(pcParam[i], "fname") == 0)  // if the fname string is found
			{
				memset(name, '\0', 30);
				strcpy(name, pcValue[i]);
			}

			else if (strcmp(pcParam[i], "lname") == 0)  // if the fname string is found
			{
				strcat(name, " ");
				strcat(name, pcValue[i]);
			}
		}
	}

	return "/cgiform.html";
}


const char *CGILED_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
	if (iIndex == 1)
	{
		for (int i=0; i<iNumParams; i++)
		{
			if (strcmp(pcParam[i], "fname") == 0)  // if the fname string is found
			{
				memset(name, '\0', 30);
				strcpy(name, pcValue[i]);
			}

			else if (strcmp(pcParam[i], "lname") == 0)  // if the fname string is found
			{
				strcat(name, " ");
				strcat(name, pcValue[i]);
			}
		}
	}

	return "/cgiled.html";
}

void http_server_init (void)
{
	httpd_init();

	http_set_ssi_handler(ssi_handler, (char const**) TAGS, 3);

	CGI_TAB[0] = FORM_CGI;
	CGI_TAB[1] = LED_CGI;

//	http_set_cgi_handlers (&FORM_CGI, 1);
	http_set_cgi_handlers (CGI_TAB, 2);
}

 */
