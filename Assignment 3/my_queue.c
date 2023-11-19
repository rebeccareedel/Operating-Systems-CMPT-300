// Rebecca Reedel 301454910, Asmita Srivastava    -- Program that does operations on an array to create a circular queue
// Code adapted from: https://www.programiz.com/dsa/circular-queue

#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 256

size_t notInUse[MAX_SIZE];
int front;
int rear;
size_t numberElements;

void reset(){
    front = -1;
    rear = -1;
    numberElements = 0;
}

// check if the queue is full -- so cannot add anymore elements
int isFull() {
  if ((front == rear + 1) || (front == 0 && rear == MAX_SIZE - 1)){
    return 1;
  }
  return 0;
}

// check if the queue is empty -- so cannot dequeue
int isEmpty() {
  if (front == -1){
    return 1;
  } 
  return 0;
}

// adds available memory chunk key to queue
size_t enqueue(size_t key) {
  if (isFull()){
    printf("\n queue is full!! \n");
    return -1;
  }
  else {
    if (front == -1){
        front = 0;
    }
    rear = (rear + 1) % MAX_SIZE;
    notInUse[rear] = key;
    printf("\n inserted into queue at back-> %li", key);
    numberElements += 1;
  }
  return 0;
}

// removes key from queue, used for checking values in hash-array
// returns key if not empty -> -1 on failure
size_t dequeue() {
  size_t key;
  if (isEmpty()) {
    printf("\n queue is empty !! \n");
    return (-1);
  } else {
    key = notInUse[front];
    if (front == rear) {
      front = -1;
      rear = -1;
    }
    // queue only has one element, so we reset the
    // queue after dequeing it. ?
    else {
      front = (front + 1) % MAX_SIZE;
    }
    numberElements -= 1;
    printf("\n removed element from queue-> %ld \n", key);
    return (key);
  }
}

// displays the queue
void display() {
  size_t i;
  if (isEmpty()){
    printf(" \n empty queue\n");
  } 
  else {
    printf("\n front -> %d ", front);
    printf("\n elements -> ");
    for (i = front; i != rear; i = (i + 1) % MAX_SIZE) {
      printf("%ld ", notInUse[i]);
    }
    printf("%ld ", notInUse[i]);
    printf("\n rear -> %d \n", rear);
  }
}

size_t returnNumberElements(){
    return numberElements;
}
