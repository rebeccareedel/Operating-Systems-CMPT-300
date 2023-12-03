// Rebecca Reedel 301454910, Asmita Srivastava 301436340

#ifndef _DSSIMUL_H_
#define _DSSIMUL_H_
#include <stdlib.h>

// Shortest Seek Time First -- chooses request next closest to head -> not fair 
void sstf(int* arr, int num_elem);

// Scan -- heads keeps moving back and forth across disk -> prevents starvation, middle passed 2x more than end
void scan(int* arr, int num_elem);

// used to create 50 int length list -> when the user doesn't give any input
void createRandomList(int **result_list);

// takes input from command line and makes it into a list to be used by the algorithms
void convertToList(char* str, int* num_elem, int **result_list);

#endif