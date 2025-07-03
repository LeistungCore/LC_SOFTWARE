/*
 * tcp_client.c
 *
 *  Created on: Jun 12, 2025
 *      Author: admin
 */


#include "lwip/tcp.h"
#include <string.h>

static struct tcp_pcb *client_pcb;

static err_t client_connected(void *arg, struct tcp_pcb *tpcb, err_t err) {
    const char *msg = "Client connected";
    tcp_write(tpcb, msg, strlen(msg), TCP_WRITE_FLAG_COPY);
    return ERR_OK;
}

void tcp_client_init(void) {
    ip_addr_t server_ip;
    IP4_ADDR(&server_ip, 192,168,0,107);  // PC IP

    client_pcb = tcp_new();
    if (client_pcb != NULL) {
        tcp_connect(client_pcb, &server_ip, 6000, client_connected);
    }
}
