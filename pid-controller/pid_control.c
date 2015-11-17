#include <stdio.h>
#include <semaphore.h>
#include "messages.h"
#include "miniproject.h"
#include "pid_control.h"


/* Controller parameters: */

double K_P =    	10;
double K_I = 	   800;
double K_D =         0;
double T   =	0.008; // [s];
double DURATION =  0.5; // [s]

double INTEGRAL;
double DERIVATIVE;
double REFERENCE = 1;
double ERROR;


double calculatePidOutput(double y){

	/*Calculates input to system from PI(D) controller.
	Input to function is previous measurement.*/

	double current_error = REFERENCE - y;
	INTEGRAL = INTEGRAL + (ERROR * T);
	DERIVATIVE = current_error - ERROR;
	ERROR = current_error;
	double u = K_P * ERROR + K_I * INTEGRAL + K_D * DERIVATIVE;

	return u;
}

void* pidController(sem_t* PID_SEM){

	/*Main loop for the controller.*/

	struct timespec next;	
	double output;
	char outputMsg[15];

	clock_gettime(CLOCK_REALTIME, &next);

	int iterations = DURATION/T;
	
	sendMessage("START");
	while(iterations > 0){

		sendMessage("GET");
		sem_wait(PID_SEM);
		
		output = calculatePidOutput(PIDValue);
		sprintf(outputMsg, "SET:%f", output);
		sendMessage(outputMsg);

		timespec_add_us(&next, T*1000000);
		clock_nanosleep_new(&next);
		iterations -= 1;
	}
	
	sendMessage("STOP");

	return 0;
}
