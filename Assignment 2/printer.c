#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "list.h"
#include "printer.h"


static pthread_t threadPID;
// synchronization
static pthread_cond_t s_syncOkToWriteCondVar = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t s_syncOkToWriteMutex = PTHREAD_MUTEX_INITIALIZER;

static List* inputList = NULL;
static char* msg;

// using condition variables for synchronizing sending/receiving and mutexes to solve critical section problems 
void* PrinterThread(void* unused) {

	while (1) {
		// wait until signalled to get lock
		pthread_mutex_lock(&s_syncOkToWriteMutex); 
		{
		// cond_wait automatically releases and re-aquires lock == stops deadlock
		pthread_cond_wait(&s_syncOkToWriteCondVar, &s_syncOkToWriteMutex);
		}
		// unlock so available to other threads
		pthread_mutex_unlock(&s_syncOkToWriteMutex);

		// get msg from end of list and remove
		msg = List_trim(inputList);
		printf("%s\n", msg);

		free(msg);
		msg = NULL;
	}
}

void Printer_signalNextWrite() {
	// signal receiver thread to prompt writing again. 
	pthread_mutex_lock(&s_syncOkToWriteMutex); 
	{
		// locking around the signal 
		pthread_cond_signal(&s_syncOkToWriteCondVar);
	}
	pthread_mutex_unlock(&s_syncOkToWriteMutex);
}

// creates thread to output msgs onto the command line for other user
void Printer_init(List* pList) {
	inputList = pList;
	pthread_create(&threadPID, NULL, PrinterThread, NULL);
}

// stops printer thread, and frees msg values 
void Printer_shutdown(void) {
	pthread_cancel(threadPID);
	pthread_join(threadPID, NULL);

	if (msg) {
		free(msg);
		msg = NULL;
	}
}

