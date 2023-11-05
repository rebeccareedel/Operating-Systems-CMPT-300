#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "list.h"
#include "shutdownManager.h"
#include "sender.h"
#include "scanner.h"

static pthread_t threadPID;
static List* outputList = NULL;
static char* buffer = NULL;

#define BUFFERSIZE 256

void* ScannerThread(void* unused) {
	while (1) {
		buffer = malloc(BUFFERSIZE);
        
		// get msg from command line input from other user
		fgets(buffer, BUFFERSIZE, stdin);
		strtok(buffer, "\n");

		// add message to the list
		List_prepend(outputList, buffer);
        
		// tells sender thread to signal when lock available for list
		Sender_signalNextSend();
        
		// if msg == !, stop program
		if (!(strcmp(buffer, "!"))) {
			ShutdownManager_triggerShutdown();
			break;
		}

	}
	return NULL;
}

// initialize scanner thread
void Scanner_init(List* pList) {
	outputList = pList;
	pthread_create(&threadPID, NULL, ScannerThread, NULL);
}

// stop scanner thread
void Scanner_shutdown(void) {
	pthread_cancel(threadPID);
	pthread_join(threadPID, NULL);

}
