#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_cond_t s_syncOkToShutdownCondVar = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t s_syncOkToShutdownMutex = PTHREAD_MUTEX_INITIALIZER;

// blocks current thread until some other thread initiates triggerShutdown()
void ShutdownManager_waitForShutdown() {
	// wait until signalled to get lock
	pthread_mutex_lock(&s_syncOkToShutdownMutex); 
		{
			// cond_wait automatically releases and re-aquires lock == stops deadlock
			pthread_cond_wait(&s_syncOkToShutdownCondVar, &s_syncOkToShutdownMutex);
		}
	// unlock so available to other threads
	pthread_mutex_unlock(&s_syncOkToShutdownMutex);
}

// ready for shutdown, allows all threads previously waiting on shutdown to continue.
void ShutdownManager_triggerShutdown() {
	// wait until signalled to get lock 
	pthread_mutex_lock(&s_syncOkToShutdownMutex); 
	{
		// locking around the signal
		pthread_cond_signal(&s_syncOkToShutdownCondVar);
	}
	// unlock so available to other threads
	pthread_mutex_unlock(&s_syncOkToShutdownMutex);
}
