#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include <semaphore.h>


//int IsNewPIDMessage;
//char PIDMessage[20];
double PIDValue;

/*Calculates input to system from PI(D) controller. Input to function is previous measurement.*/

double calculatePidOutput(double y);
void* pidController();



#endif /* PID_CONTROL_H */
