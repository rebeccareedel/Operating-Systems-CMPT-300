// Rebecca Reedel 301454910, Asmita Srivastava 301436340

#include "dssimul.h"
#include <stdlib.h>
#include <stdio.h> 
#include <assert.h> 

#define n 50

// Shortest Seek Time First -- chooses request next closest to head -> not fair 
void sstf(int arr){

}

// Scan -- heads keeps moving back and forth across disk -> prevents starvation, middle passed 2x more than end
void scan(int arr){

}

void createRandomList(int **result_list){
    // used to check if random number already used
    int arr[200];

    // create list to hold values
    *result_list = (int*)malloc(n * sizeof(int));
    
    // get random numbers for list
    for (int i =0; i < n ; i++) {
        // get new random number
        int new_num = rand()%199;
        // keep running until finds free random number
        while(arr[new_num]==1){
            new_num = rand()%199; // set to new number each loop
        }
        arr[new_num] = 1; //set to status = busy
        (*result_list)[i] = new_num; // add number to list index
    }
    
}

void convertToList(char* str, int* num_elem, int **result_list){

    // should have atleast 1 element
    *num_elem = 1; 

    // allocate space to hold result
    *result_list = (int*)malloc(*num_elem * sizeof(int));
    
    // loop to split by comma
    int currentIndex = 0; // necessary so we can skip over commas
    int nextNumber = 0;  // holds next int to add to list, used to create ints from 1 digit to 3
    
    for (char* current = str; *current != '\0'; current++) {
        if (*current == ',') // current = delimiter
        {   
            // make sure integer input in [0,199] range
            if(nextNumber <0 || nextNumber > 199){
                fprintf(stderr,"Please provide integers in [0,199] range \n");
                exit(1);
            }
            (*result_list)[currentIndex++] = nextNumber; // add 
            *num_elem += 1;
            *result_list = realloc(*result_list, *num_elem * sizeof(int)); // allocate more space
            nextNumber = 0;  // set to 0 for next value
        } 
        else if (nextNumber == ' '){ // check for spaces
            fprintf(stderr,"Please provide integers in [0,199] range: with NO SPACES \n");
            exit(1);
        }
        else {
            // converts from string to int, using ASCII manipulation
            nextNumber = nextNumber * 10 + (*current - '0'); 
        }
    }
    // make sure integer input in [0,199] range
    if(nextNumber <0 || nextNumber > 199){
        fprintf(stderr,"Please provide integers in [0,199] range, no spaces\n");
        exit(1);
    }
    // add the last int
    (*result_list)[currentIndex] = nextNumber;

    // check number of elements, if <3 call make random
    if(*num_elem <3){
        // ERROR
        fprintf(stderr,"Please provide atleast 3 unique tracks within the range [0,199], no spaces: \n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    int num_elem;
    int* current_list;
    
    if(argc > 1){
        // split by comma, pass as int, put each in list
        convertToList(argv[1], &num_elem, &current_list);
        for( int i = 0; i < num_elem; i ++){
            printf("%d\n", current_list[i]);
        }
        
    }
    else{
        // make list of 50 random integers
        createRandomList(&current_list);
        num_elem = n;
        for( int i = 0; i < num_elem; i ++){
            printf("%d\n", current_list[i]);
        }
    }
    free(current_list);
    return 0;
}
