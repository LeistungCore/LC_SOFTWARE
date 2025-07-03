

#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>
#include "main.h"
#include "../../lvgl/lvgl.h"
#include "../../lv_conf.h"
#include "../../hal_stm_lvgl/tft/tft.h"
static struct tcp_pcb *server_pcb;

// Assume this is the variable you want to send to client
// In real case, define it in main.c or other logic module and declare as extern here
extern volatile int  flow_fault_value;
extern volatile int flow_warning_value;
extern  float slow_leak_difference_value;
extern int  slow_leak_delay_value;
extern int Stabilization_delay;

extern int outlet_temp;
extern int outlet_temp1;
extern int differential_temp;
extern int differential_temp1;


int server_flow_fault_flag;
int server_flow_warning_flag;
int server_slow_leak_difference_flag;
int  server_slow_leak_delay_flag;
int    server_stabilization_flag;
int server_outlet_temp_flag;
int   server_outlet_temp1_flag;
int server_differential_temp_flag;
int  server_differential_temp1_flag;
//int server_flow_fault_flag;

#define CMD_SET_FLOW_FAULT              "SET_FLOW_FAULT="
#define CMD_SET_FLOW_WARNING            "SET_FLOW_WARNING="
#define CMD_SET_SLOW_LEAK_DIFFERENCE    "SET_SLOW_LEAK_DIFFERENCE="
#define CMD_SET_SLOW_LEAK_DELAY         "SET_SLOW_LEAK_DELAY="
#define CMD_SET_STABILIZATION_DELAY     "SET_STABILIZATION_DELAY="
#define CMD_SET_OUTLET_TEMP             "SET_OUTLET_TEMP="
#define CMD_SET_OUTLET_TEMP1            "SET_OUTLET_TEMP1="
#define CMD_SET_DIFFERENTIAL_TEMP       "SET_DIFFERENTIAL_TEMP="
#define CMD_SET_DIFFERENTIAL_TEMP1      "SET_DIFFERENTIAL_TEMP1="


static err_t server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (p == NULL) {
        tcp_close(tpcb);
        return ERR_OK;
    }

    char buffer[1000] = {0};
    memcpy(buffer, p->payload, p->len);
    buffer[p->len] = '\0'; // Null terminate the string



    if (strcmp(buffer, "GET_FLOW_FAULT") == 0) {
        char response[100];
        snprintf(response, sizeof(response), " Flow Fault: %d LPM\n", flow_fault_value);
        tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);

    }

    else  if (strcmp(buffer, "GET_FLOW_WARNING") == 0) {
         char response[100];
         snprintf(response, sizeof(response), " Flow Warning: %d LPM\n", flow_warning_value);
         tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
     }
    else  if (strcmp(buffer, "GET_SLOW_LEAK_DIFFERENCE") == 0) {
         char response[100];
         snprintf(response, sizeof(response), " SLOW_LEAK_DIFFERENCE: %f LPM\n", slow_leak_difference_value);
         tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
     }


    else  if (strcmp(buffer, "GET_SLOW_LEAK_DELAY") == 0) {
           char response[100];
           snprintf(response, sizeof(response), " SLOW LEAK DELAY VALUE: %d S\n", slow_leak_delay_value);
           tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
       }
    else  if (strcmp(buffer, "GET_STABILIZATION_DELAY") == 0) {
           char response[100];
           snprintf(response, sizeof(response), " STABILIZATION DELAY : %d S\n", Stabilization_delay);
           tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
       }

    else  if (strcmp(buffer, "GET_OUTLET_TEMP") == 0) {
           char response[100];
           snprintf(response, sizeof(response), " OUTLET TEMP : %d °C\n", outlet_temp);
           tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
       }
    else  if (strcmp(buffer, "GET_OUTLET_TEMP1") == 0) {
           char response[100];
           snprintf(response, sizeof(response), " OUTLET TEMP1 : %d °C\n", outlet_temp1);
           tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
       }
    else  if (strcmp(buffer, "GET_DIFFERENTIAL_TEMP") == 0) {
           char response[100];
           snprintf(response, sizeof(response), " DIFFERENTIAL TEMP : %d °C\n", differential_temp);
           tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
       }
    else  if (strcmp(buffer, "GET_DIFFERENTIAL_TEMP1") == 0) {
           char response[100];
           snprintf(response, sizeof(response), " DIFFERENTIAL TEMP1 : %d °C\n", differential_temp1);
           tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
       }



    //SET VALUES
    else if (strncmp(buffer, CMD_SET_FLOW_FAULT, strlen(CMD_SET_FLOW_FAULT)) == 0) {
        flow_fault_value = atoi(&buffer[strlen(CMD_SET_FLOW_FAULT)]);
        server_flow_fault_flag = 1;
        tcp_write(tpcb, " Flow fault value updated\n", 26, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_FLOW_WARNING, strlen(CMD_SET_FLOW_WARNING)) == 0) {
        flow_warning_value = atoi(&buffer[strlen(CMD_SET_FLOW_WARNING)]);
        server_flow_warning_flag = 1;
        tcp_write(tpcb, " Flow warning value updated\n", 28, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_SLOW_LEAK_DIFFERENCE, strlen(CMD_SET_SLOW_LEAK_DIFFERENCE)) == 0) {
        slow_leak_difference_value = atoi(&buffer[strlen(CMD_SET_SLOW_LEAK_DIFFERENCE)]);
        server_slow_leak_difference_flag = 1;
        tcp_write(tpcb, " Slow leak difference updated\n", 32, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_SLOW_LEAK_DELAY, strlen(CMD_SET_SLOW_LEAK_DELAY)) == 0) {
        slow_leak_delay_value = atoi(&buffer[strlen(CMD_SET_SLOW_LEAK_DELAY)]);
        server_slow_leak_delay_flag = 1;
        tcp_write(tpcb, " Slow leak delay updated\n", 27, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_STABILIZATION_DELAY, strlen(CMD_SET_STABILIZATION_DELAY)) == 0) {
        Stabilization_delay = atoi(&buffer[strlen(CMD_SET_STABILIZATION_DELAY)]);
        server_stabilization_flag = 1;
        tcp_write(tpcb, " Stabilization delay updated\n", 29, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_OUTLET_TEMP, strlen(CMD_SET_OUTLET_TEMP)) == 0) {
        outlet_temp = atoi(&buffer[strlen(CMD_SET_OUTLET_TEMP)]);
        server_outlet_temp_flag = 1;
        tcp_write(tpcb, " Outlet temp updated\n", 21, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_OUTLET_TEMP1, strlen(CMD_SET_OUTLET_TEMP1)) == 0) {
        outlet_temp1 = atoi(&buffer[strlen(CMD_SET_OUTLET_TEMP1)]);
        server_outlet_temp1_flag = 1;
        tcp_write(tpcb, " Outlet temp1 updated\n", 22, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_DIFFERENTIAL_TEMP, strlen(CMD_SET_DIFFERENTIAL_TEMP)) == 0) {
        differential_temp = atoi(&buffer[strlen(CMD_SET_DIFFERENTIAL_TEMP)]);
        server_differential_temp_flag = 1;
        tcp_write(tpcb, " Differential temp updated\n", 27, TCP_WRITE_FLAG_COPY);
    }
    else if (strncmp(buffer, CMD_SET_DIFFERENTIAL_TEMP1, strlen(CMD_SET_DIFFERENTIAL_TEMP1)) == 0) {
        differential_temp1 = atoi(&buffer[strlen(CMD_SET_DIFFERENTIAL_TEMP1)]);
        server_differential_temp1_flag = 1;
        tcp_write(tpcb, " Differential temp1 updated\n", 28, TCP_WRITE_FLAG_COPY);
    }






    else if (strcmp(buffer, "GET_ALL") == 0) {
        char response[400];
        snprintf(response, sizeof(response),
            " Flow Fault: %d LPM\n"
            " Flow Warning: %d LPM\n"
            " SLOW LEAK DIFFERENCE VALUE: %f LPM\n"
            " SLOW LEAK DELAY VALUE: %d S\n"
            " STABILIZATION DELAY : %d S\n"
            " OUTLET TEMP : %d °C\n"
            " OUTLET TEMP1 : %d °C\n"
            " DIFFERENTIAL TEMP : %d °C\n"
            " DIFFERENTIAL TEMP1 : %d °C\n",
            flow_fault_value,
            flow_warning_value,
            slow_leak_difference_value,
            slow_leak_delay_value,
            Stabilization_delay,
            outlet_temp,
            outlet_temp1,
            differential_temp,
            differential_temp1
        );
        tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
    }

    else
    {
        const char *unknown = "Unknown command\n";
        tcp_write(tpcb, unknown, strlen(unknown), TCP_WRITE_FLAG_COPY);
    }

    pbuf_free(p);
    return ERR_OK;
}

static err_t server_accept(void *arg, struct tcp_pcb *newpcb, err_t err) {
    const char *msg = "Server connected\n";

    // Toggle LED on successful connection
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);

    // Send welcome message to client
    tcp_write(newpcb, msg, strlen(msg), TCP_WRITE_FLAG_COPY);

    // Set receive callback
    tcp_recv(newpcb, server_recv);

    return ERR_OK;
}

void tcp_server_init(void) {
    server_pcb = tcp_new();
    if (server_pcb != NULL) {
        ip_addr_t server_ip;
        IP4_ADDR(&server_ip, 172, 24, 1, 1);  // Bind to specific IP address
        if (tcp_bind(server_pcb, &server_ip, 6000) == ERR_OK) {
            server_pcb = tcp_listen(server_pcb);
            tcp_accept(server_pcb, server_accept);
        }
    }
}
