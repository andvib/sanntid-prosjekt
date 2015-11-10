#include "pid_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include "../messages/messages.h"
#include "../miniproject/client/miniproject.h"


double K_P =    	10;
double K_I = 	   800;
double K_D =         0;
double T   =	0.0021;//0.0013;
double DURATION =  0.5; //[s]

double INTEGRAL;
double DERIVATIVE;
double REFERENCE = 1;
double ERROR;



double calculatePidOutput(double y){
	double current_error = REFERENCE - y;
	INTEGRAL = INTEGRAL + (ERROR * T);
	//DERIVATIVE = current_error - ERROR;
	ERROR = current_error;
	double u = K_P * ERROR + K_I * INTEGRAL + K_D * DERIVATIVE;

	return u;
}

void* pidController(sem_t* PID_SEM){
	struct timespec next;	
	double output;
	double y;
	char msg[15];

	clock_gettime(CLOCK_REALTIME, &next);

	int iterations = DURATION/T;
	
	sendMessage("START");
	while(iterations > 0){

		sendMessage("GET");
		sem_wait(PID_SEM);

		//y = atof(&PIDMessage[8]);
		y = PIDValue;
		
		output = calculatePidOutput(y);
		sprintf(msg, "SET:%f", output);
		sendMessage(msg);

		timespec_add_us(&next, T*1000000);
		clock_nanosleep_new(&next);
		iterations -= 1;
	}

	sendMessage("STOP");
	return 0;
}
