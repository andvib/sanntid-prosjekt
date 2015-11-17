#ifndef MESSAGES_H
#define MESSAGES_H


#include <semaphore.h>

struct ArgStruct{
	sem_t* PID_SEM;
	sem_t* RES_SEM;
};

int initMessages();
void closeConn();
int sendMessage(char * msg);
void* messageListen();
void* signalRespond();


#endif /* MESSAGES_H */
