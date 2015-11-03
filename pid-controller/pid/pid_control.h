#ifndef PID_CONTROL_H
#define PID_CONTROL_H


#define K_P	   10;
#define K_I 	   800;
#define K_D 	   1;
#define T 		   0.1;
#define DURATION 0.5; //[s]

int INTEGRAL;
int DERIVATIVE;
int REFERENCE;
int ERROR;


/*Calculates input to system from PI(D) controller. Input to function is previous measurement.*/

int calculatePidOutput(int y);



#endif /* PID_CONTROL_H */