#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "miniproject.h"
#include "pid_control.h"


struct udp_conn CONN;

int initMessages(){
	int status = udp_init_client(&CONN, 9999, "192.168.0.1");
	
	if(status != 0){
		printf("CONNECTION ERROR\n");
	}
	
	return status;
}

void closeConn(){
	udp_close(&CONN);
}

int sendMessage(char * msg){
	int status = udp_send(&CONN, msg, 15);

	return status;
}

void* messageListen(struct ArgStruct* arguments){

	/* Function for listening on UDP port. */

	char rcv_buf[15];

	while(1) {
		udp_receive(&CONN, rcv_buf, 15);

		if(rcv_buf[0] == 'G'){
			/* Received measurement. */
			PIDValue = atof(&rcv_buf[8]);
			sem_post(arguments->PID_SEM);

		}else if (rcv_buf[0] == 'S'){
			/* Received signal. */
			sem_post(arguments->RES_SEM);
		}
	}

	return 0;
}

void* signalRespond(sem_t* RES_SEM){

	while(1) {
		sem_wait(RES_SEM);
		sendMessage("SIGNAL_ACK");
	}

	return 0;
}
