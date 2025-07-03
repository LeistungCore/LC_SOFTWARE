#include "ssi_process.h"
#include <string.h>
#include "main.h"
#include "lwip/apps/httpd.h"
char abb1=1;

//extern uint32_t sensor_value,sensor_value1;
extern float temp1,temp2;
extern float average_flow,average_flow1;
extern int valve_1display;

extern int valve_for_webinterface;
extern ADC_HandleTypeDef hadc1;
extern char valve1,valve2,BYPASS;
extern char FloWarning[10];
extern char FlowFault[10];
extern char SlowLeak[10];
extern char SlowDelay[10];
extern char Stabildelay[10];
extern char leakResponse[10];
extern char flowUnit[10];
extern char Tempoutlatewarning[10];
extern char TempoutlateFault[10];
extern char TempDiffWarning[10];
extern char TempDiffFault[10];
extern char TempUnit[10];
extern char IPV01[10];
extern char IPV02[10];
void toggle_image_visibility(void);
void toggle_txt_visibility(void);


char const reflect[]="2";

char const* ssi_tags[]= {"FLOW","TEMP","T1","B1","B2","T2","T3","T4","MSG","FLOW1","TEMP1","FLOW2","TEMP2","BYPVALVE","FWARN","FFAULT","SLDIFF","SLDELAY","STADELAY","LEAKRESP","UNITGPLP","OutWar","OutFault","DiffWar","DFLT","CFUNIT","IP01","IP02"};
char const** tags = ssi_tags;
uint16_t   ssi_handler( int iIndex, char *pcInsert, int iInsertLen)
{
	switch (iIndex)
	{
	case 0:
		sprintf (pcInsert,"%0.2f", average_flow);
		return strlen(pcInsert);
		break;
	case 1:
//		sprintf (pcInsert,"%0.2f",  temp1 * 9.0 / 5.0 + 32.0);// (int) HAL_ADC_GetValue(&hadc1));
		sprintf (pcInsert,"%0.2f",  temp1);// (int) HAL_ADC_GetValue(&hadc1));
		return strlen(pcInsert);
		break;
	case 2:
		if(valve1 == 1)
		{

			sprintf (pcInsert,"<div id=\"flow\" class=\"state-indicator state-1\"   style=\"background-color: Green\">FLOW <br> OK ");

			return strlen(pcInsert);
		}

		else if(valve1 == 0)
		{
			sprintf (pcInsert,"<div id=\"flow\" class=\"state-indicator state-1\" style=\"background-color: red\">FLOW <br>NOT OK ");

			return strlen(pcInsert);

		}

		break;


	case 3: // <!--#valve1_state-->
		if(valve1 == 1  ) {
			sprintf(pcInsert, "<button id=\"Valve1\" name=\"valve11\"  value=\"1\" type=\"submit\" style=\"background-color: red\">VALVE 1 <br><span id=\"val_1\">OPEN</span></button>");
			return strlen(pcInsert);
		}




		else if (valve1 ==0)

			{
						sprintf(pcInsert, "<button id=\"Valve1\" name=\"valve11\" value=\"0\" type=\"submit\" style=\"background-color: blue\">VALVE 1 <br><span id=\"val_1\">CLOSE</span></button>");
						return strlen(pcInsert);

		}



		break;
	case 4:
		if(valve2 == 1)
		{

			sprintf (pcInsert,"<button id=\"Valve2\" name=\"valve12\" value=\"1\" type=\"submit\" style=\"background-color: red\" >VALVE 2 <br><span id=\"val_2\">OPEN");


			return strlen(pcInsert);
		}
		else
		{

			sprintf (pcInsert,"<button id=\"Valve2\" name=\"valve12\" value=\"0\" type=\"submit\" style=\"background-color: blue\" >VALVE 2 <br><span id=\"val_2\">CLOSE");


			return strlen(pcInsert);
		}
		break;
	case 5:
		if(valve1 == 1)
		{

			sprintf (pcInsert,"<div id=\"temp\" class=\"state-indicator state-1\"   style=\"background-color: Green\">TEMP <br> OK ");

			return strlen(pcInsert);
		}

		else if(valve1 == 0)
		{
			sprintf (pcInsert,"<div id=\"flow\" class=\"state-indicator state-1\" style=\"background-color: red\">TEMP <br>NOT OK ");

			return strlen(pcInsert);

		}

		break;

	case 6:
		if(valve1||valve2 == 1 )
		{

			sprintf (pcInsert,"<div id=\"flow\" class=\"state-indicator state-1\"   style=\"background-color: Green\">VALVE <br> ON ");

			return strlen(pcInsert);
		}

		else if(valve1||valve2 == 0)
		{
			sprintf (pcInsert,"<div id=\"flow\" class=\"state-indicator state-1\" style=\"background-color: red\">VALVE <br> OFF ");

			return strlen(pcInsert);

		}

		break;

	case 7:
		if(valve1 == 1)
		{

			sprintf (pcInsert,"<div id=\"flow\" class=\"state-indicator state-1\"   style=\"background-color: Green\">DETECTION <br> ENABLED ");

			return strlen(pcInsert);
		}

		else if(valve1 == 0)
		{
			sprintf (pcInsert,"<div id=\"flow\" class=\"state-indicator state-1\" style=\"background-color: red\">DETECTION <br>DISABLED ");

			return strlen(pcInsert);

		}

		break;

	case 8 :
		if(valve1 == 1)
		{

			sprintf (pcInsert,"OK TO WELD");

			return strlen(pcInsert);
		}

		else if(valve1 == 0)
		{
			sprintf (pcInsert,"NOT OK TO WELD ");

			return strlen(pcInsert);

		}

		break;
	case 9:
		sprintf (pcInsert,"%0.2f",  average_flow1);// (int) HAL_ADC_GetValue(&hadc1));
		return strlen(pcInsert);
		break;
	case 10:
		sprintf (pcInsert,"%0.2f",   temp1);// (int) HAL_ADC_GetValue(&hadc1));
		return strlen(pcInsert);
		break;
	case 11:
		sprintf (pcInsert,"%0.2f", average_flow);// (int) HAL_ADC_GetValue(&hadc1));
		return strlen(pcInsert);
		break;
	case 12:
		sprintf (pcInsert,"%0.2f",  temp2);// (int) HAL_ADC_GetValue(&hadc1));
		return strlen(pcInsert);
		break;



	case 13:

			if(BYPASS == 1)
			{
							sprintf (pcInsert,"<button id=\"Valve2\" name=\"valve13\" value=\"1\" type=\"submit\" style=\"background-color: red\" >BYPASS <br><span id=\"val_2\">ON");
      		return strlen(pcInsert);
			}
			else
			{

				sprintf (pcInsert,"<button id=\"Valve2\" name=\"valve13\" value=\"0\" type=\"submit\" style=\"background-color: blue\" >BYPASS <br><span id=\"val_2\">OFF");
				return strlen(pcInsert);
			}
		break;


	case 14:
		sprintf (pcInsert,"%s",FloWarning);
		return strlen(pcInsert);
		break;
	case 15:
		sprintf (pcInsert,"%s",FlowFault);
		return strlen(pcInsert);
		break;
	case 16:
		sprintf (pcInsert,"%s",SlowLeak);
		return strlen(pcInsert);
		break;
	case 17:
		sprintf (pcInsert,"%s",SlowDelay);
		return strlen(pcInsert);
		break;
	case 18:
		sprintf (pcInsert,"%s",Stabildelay);
		return strlen(pcInsert);
		break;
	case 19:
		sprintf (pcInsert,"%s",leakResponse);
		return strlen(pcInsert);
		break;
	case 20:
		sprintf (pcInsert,"%s",flowUnit);
		return strlen(pcInsert);
		break;
	case 21:
		sprintf (pcInsert,"%s",Tempoutlatewarning);
		return strlen(pcInsert);
		break;
	case 22:
		sprintf (pcInsert,"%s",TempoutlateFault);
		return strlen(pcInsert);
		break;
	case 23:
		sprintf (pcInsert,"%s",TempDiffWarning);
		return strlen(pcInsert);
		break;
	case 24:
		sprintf (pcInsert,"%s",TempDiffFault);
		return strlen(pcInsert);
		break;
	case 25:
		sprintf (pcInsert,"%s",TempUnit);
		return strlen(pcInsert);
		break;
	case 26:
		sprintf (pcInsert,"%s",IPV01);
		return strlen(pcInsert);
		break;
	case 27:
		sprintf (pcInsert,"%s",IPV02);
		return strlen(pcInsert);
		break;
		//break;
	default :
		break;
	}
	return 0;
}


