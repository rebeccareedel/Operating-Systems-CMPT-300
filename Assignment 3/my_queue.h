// Rebecca Reedel 301454910, Asmita Srivastava 301436340  --- CIRCULAR QUEUE

#ifndef _MY_QUEUE_H_
#define _MY_QUEUE_H_
#include <stdlib.h>

// check if the queue is full -- so cannot enqueue
int isFull();

// check if the queue is empty -- so cannot dequeue
int isEmpty();

// adds available memory chunk key to queue
size_t enqueue(size_t key);

// removes key from queue, used for checking values in hash-array
size_t dequeue();

// displays the queue
void display();

// returns number of total elements in queue
int returnNumberElements();

// used to reset values between test runs
void reset();

#endif
