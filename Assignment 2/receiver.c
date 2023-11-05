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
#include "receiver.h"
#include "printer.h"
#include "shutdownManager.h"

static pthread_t threadPID;
static List* inputList = NULL;
static char* myPort;
static char* buffer;

#define MAXBUFFERLEN 256 // msg size not more than 256 bytes

void *get_in_addr(struct sockaddr *sock_addr)
{
	if (sock_addr->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sock_addr)->sin_addr);
	}
	
	return &(((struct sockaddr_in6*)sock_addr)->sin6_addr);
}

void* receiverThread(void* unused) {
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int s; // returns structs to address info : IP addr etc. 
	int numberBytes;
	struct sockaddr_storage remote_addr;
	socklen_t addr_len;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	if ((s = getaddrinfo(NULL, myPort, &hints, &servinfo)) != 0) {
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

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("Error during bind");
			continue;
		}

		break;
	}

	if (p == NULL) { // no records of server address info : so socket cannot be binded
		fprintf(stderr, "Failed to bind socket\n");
		return NULL;
	}

	freeaddrinfo(servinfo);

	while(1) {
		buffer = malloc(MAXBUFFERLEN);

		addr_len = sizeof remote_addr;

		// if no. of bytes are -1, error during transmission. 
		if ((numberBytes = recvfrom(sockfd, buffer, MAXBUFFERLEN, 0,
			(struct sockaddr *) &remote_addr, &addr_len)) == -1) {
			// check for errors during receiving
			perror("Error caused during recvfrom");
			ShutdownManager_triggerShutdown();
		}
        
		// if complete msg  = !, should stop program
		if (!(strcmp(buffer, "!"))) {
			ShutdownManager_triggerShutdown();
		}
        
		// add message to list
		List_prepend(inputList, buffer);
		buffer = NULL;

		// signal printer to get msg when ready
		Printer_signalNextWrite();
	}

	return NULL;
}

// initilaize receiver thread with port, -- used to 
void Receiver_init(List* pList, char* port1) {
	inputList = pList;
	myPort = port1;
	pthread_create(&threadPID, NULL, receiverThread, NULL);
}

// stop receiver thread, free buffer, set to NULL
void Receiver_shutdown(void) {
	pthread_cancel(threadPID);
	pthread_join(threadPID, NULL);

	if (buffer) {
		free(buffer);
		buffer = NULL;
	}
}