#include "messages.h"
#include "../miniproject/client/miniproject.h"
#include "../pid/pid_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

struct udp_conn CONN;


int initMessages(){
	int status = udp_init_client(&CONN, 9999, "192.168.0.1");
	
	if(status != 0){
		printf("CONNECTION ERROR\n");
	}
	
	return status;
}


int sendMessage(char * msg){
	int status = udp_send(&CONN, msg, 15);

	return status;
}

void* messageListen(sem_t* PID_SEM){
	char rcv_buf[15];

	while(1){

		udp_receive(&CONN, rcv_buf, 15);

		if(rcv_buf[0] == 'G'){
			PIDValue = atof(&rcv_buf[8]);
			sem_post(PID_SEM);
		}/*else if (rcv_buf[0] == 'G'){
			//
		}*/

	}
	return 0;
}

/*
void* messageRespond(sem_t* RES_SEM){
	
}
