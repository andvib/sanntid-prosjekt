#include <pthread.h>
#include <semaphore.h>
#include "pid_control.h"
#include "messages.h"


int main(){
	initMessages();
	static sem_t PID_SEM;
	static sem_t RES_SEM;

	// SEMAPHORE-INITIALIZATION
	sem_init(&PID_SEM, 0, 0);
	sem_init(&RES_SEM, 0, 0);

	// LISTENING-THREAD
	struct ArgStruct arguments;
	arguments.PID_SEM = &PID_SEM;
	arguments.RES_SEM = &RES_SEM;

	pthread_t listen_thread;
	pthread_create(&listen_thread, NULL, messageListen, &arguments);

	// PID-CONTROLLER
	pthread_t pid_thread;
	pthread_create(&pid_thread, NULL, pidController, &PID_SEM);

	// RESPOND-THREAD
	pthread_t respond_thread;
	pthread_create(&respond_thread, NULL, signalRespond, &RES_SEM);

	// CLEANUP
	pthread_join(pid_thread, NULL);

	sem_destroy(&PID_SEM);
	sem_destroy(&RES_SEM);

	closeConn();

	return 0;
}
