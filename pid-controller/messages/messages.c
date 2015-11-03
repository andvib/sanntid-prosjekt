#include "messages.h"
#include <stdio.h>
#include <stdlib.h>

/*struct udp_conn CONN;


int initMessages(){
	int status = udp_init_client(&CONN, 10013, "192.168.0.1");
	
	if(status != 0){
		printf("CONNECTION ERROR\n");
	}
	
	return status;
}


int sendMessage(char * msg){
	int status = udp_send(&CONN, msg, sizeof(*msg));

	if (status != 0){
		printf("SEND MESSAGE ERROR\n");
	}

	return status;
}*/

double getMeasurement(){
	char *rcv_buf[99];

	//int status = sendMessage("GET");

	//status = udp_receive(&CONN, rcv_buf, sizeof(*rcv_buf));

	*rcv_buf = "GET_ACK:123.456";

	int i = 0;
	while (rcv_buf[i] != ":"){
		i += 1;
	}

	char *temp = rcv_buf[i+1];

	double y = atof(temp);

	return y;

}

int main(){
	double y = getMeasurement();
	printf("%e", y);
	
	return 0;
}
