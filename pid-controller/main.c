#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "pid/pid_control.h"
#include "messages/messages.h"


int main(){
	initMessages();
	static sem_t PID_SEM;
	// SEMAPHORE-INITIALIZATION
	int status = sem_init(&PID_SEM, 0, 0);
	//int status = sem_init(&RES_SEM, 0, 0);

	// LISTENING-THREAD
	pthread_t listen_thread;
	pthread_create(&listen_thread, NULL, messageListen, &PID_SEM);

	// PID-CONTROLLER
	pthread_t pid_thread;
	pthread_create(&pid_thread, NULL, pidController, &PID_SEM);

	// RESPOND-THREAD

	/*pthread_t respond_thread;
	pthread_create(&respond_thread, NULL, function, &RES_SEM);*/

	pthread_join(pid_thread, NULL);
	//pthread_join(listen_thread, NULL);
	//pthread_join(respond_thread, NULL);

	sem_destroy(&PID_SEM);

	return 0;
}
