#include "pid_control.h"
#include "messages.h"

int calculatePidOutput(int y){
	current_error = REFERENCE - y;
	INTEGRAL = INTEGRAL + (ERROR * T);
	DERIVATIVE = current_error - ERROR;
	ERROR = current_error;
	u = K_P * ERROR + K_I * INTEGRAL + K_D * DERIVATIVE;

	return u;
}



void pidController(){
	while(1){

		y = getMeasurement();			

}
