//CMPT300E1 - Assignment 2 (due Thursday, October 26 2023)
// Submitted By - Asmita Srivastava (Student No. 301436340), Rebecca Reedel (Student No. 301454910)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "receiver.h"
#include "sender.h"
#include "scanner.h"
#include "printer.h"
#include "list.h"
#include "shutdownManager.h"


void freeItem(void* item) {
	if (item) {
		free(item);
	}
}

int main(int argc, char* argv[]) {

    printf("S-talk Session Initiated\n");
	
	// check if too many input values
	if (argc != 4) {
		fprintf(stderr,"usage: myport remotehostname remoteport\n");
		exit(1);
	}
    
	// create two lists to store messages for different threads
	List* outputList = List_create();
	List* inputList = List_create();
    
	// initialize the four threads to start
	Receiver_init(inputList, argv[1]); // await a UDP datagram
	Scanner_init(outputList); // await input from the keyboard.
	Sender_init(outputList, argv[2], argv[3]); // sends data to the remote UNIX process over the network using UDP
	Printer_init(inputList); // prints characters to the screen.
    
	// shutdown all threads
	ShutdownManager_waitForShutdown(); // initialize shutdown 
	Receiver_shutdown(); 
	Sender_shutdown();
	Scanner_shutdown();
	Printer_shutdown();
    
	// free list so no memory leaks
	List_free(outputList, freeItem);
	List_free(inputList, freeItem);

	printf("S-Talk Session Stopped\n");
	return 0;
}