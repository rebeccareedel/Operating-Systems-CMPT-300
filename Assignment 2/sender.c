#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#include "list.h"
#include "sender.h"

static pthread_t threadPID;
static pthread_cond_t s_syncOkToSendCondVar = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t s_syncOkToSendMutex = PTHREAD_MUTEX_INITIALIZER;

static List* outputList = NULL;
static char* hostname;
static char* remotePort;
static char* msg;


void* senderThread(void* unused) {
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int s; // returns structs to address info : IP addr etc. 
	int numberBytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM; // used for UDP 

	if ((s = getaddrinfo(hostname, remotePort, &hints, &servinfo)) != 0) {
		// upon failure to getaddrinfo : convert error code to human-readable message. 
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return NULL;
	}

	// loop through all the possible IP addresses and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		// if socket creation fails, display error message. 
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("Error creating a socket"); 
			continue;
		}
		break;
	}

	if (p == NULL) { // no records of server address info : check if socket not created
		fprintf(stderr, "Failed to create socket\n");
		return NULL;
	}

    // free struct of possible IP addresses
	freeaddrinfo(servinfo);

	while (1) {
		// wait until signalled to get lock
		pthread_mutex_lock(&s_syncOkToSendMutex); 
		{
			// cond_wait automatically releases and re-aquires lock == stops deadlock
			pthread_cond_wait(&s_syncOkToSendCondVar, &s_syncOkToSendMutex);
		}
		// unlock so available to other threads
		pthread_mutex_unlock(&s_syncOkToSendMutex);

		// get msg from end of list and remove
		msg = List_trim(outputList);

        // if no. of bytes = -1, error during transmission. 
		if ((numberBytes = sendto(sockfd, msg, strlen(msg), 0,
				 p->ai_addr, p->ai_addrlen)) == -1) {
			perror("Error caused during sendto");
			exit(1);
		}

		free(msg);
		msg = NULL;
	}

	return 0;
}

// signals scanner thread
void Sender_signalNextSend() {
	pthread_mutex_lock(&s_syncOkToSendMutex); 
	{
		// locking around the signal
		pthread_cond_signal(&s_syncOkToSendCondVar);
	}
	// unlock so available to other threads
	pthread_mutex_unlock(&s_syncOkToSendMutex);
}

// initialize sender thread, and set global scope variables names
void Sender_init(List* pList, char* host, char* port2) {
	outputList = pList;
	hostname = host;
	remotePort = port2;
	pthread_create(&threadPID, NULL, senderThread, NULL);
}

// stop sender thread, free msg data
void Sender_shutdown(void) {
	pthread_cancel(threadPID);
	pthread_join(threadPID, NULL);

	if (msg) {
		free(msg);
		msg = NULL;
	}
}

