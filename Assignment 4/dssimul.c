// Rebecca Reedel 301454910, Asmita Srivastava 301436340

#include "dssimul.h"
#include <stdlib.h>
#include <stdio.h> 
#include <assert.h> 

#define n 50

// Shortest Seek Time First -- chooses request next closest to head -> not fair 
void sstf(int* arr, int num_elem){

    int request_list[num_elem];
    printf("Initial Request List of track numbers =>\n");
    for( int i = 0; i < num_elem; i ++){
            request_list[i] = arr[i];
            printf("%d ", arr[i]);
    }
    // set track number to first index of arr
    int traverse_list[num_elem];
    traverse_list[0] = request_list[0];
    
    int head = 0;
    int min_diff = 202;
    int next_head = 0;
    int count = 1;
    int total_tracks = 0;

    while(count < num_elem){
        for(int i= 1; i<num_elem; i++){
            if(abs(request_list[head] - request_list[i]) < min_diff && head != i ){
            	min_diff = abs(request_list[head] - request_list[i]);
            	next_head = i;
            }
        }
        request_list[head] = 500;
        head = next_head;
        traverse_list[count] = request_list[head];
        total_tracks += min_diff;
        min_diff = 202;
        count++;
    }
    printf("\nFinal Traverse List of track numbers =>\n");
    for( int i = 0; i < num_elem; i ++){
            printf("%d ", traverse_list[i]);
    }
    printf("\nTotal number of tracks passed =  %d \n", total_tracks);

    //For longest delay - find the max shifted index
    int longest_delay = 0;
    int delay[num_elem]; // record the delays in all elements
    int num_delays = 0;
    int sum_delays = 0;
    for(int i= 0;i<num_elem;i++){
        delay[i] = 0; //no delay in head element
        for(int j=0;j<num_elem;j++){
            if(arr[i] == traverse_list[j]){
                //where the delay occurs, find the shifted index
                delay[i] = j-i; //with respect to the original index, how shifted is the new index? 
                break;
            }
        }
        if(delay[i] > longest_delay){
            longest_delay = delay[i]; //longest shifted index
        }
        //printf("%d ", delay[i]);
        if(delay[i]>0){ //only positively shifted index
            num_delays++;
            sum_delays += delay[i];
        }
    }
    printf("Longest Delay =  %d \n", longest_delay);
    printf("Average Delay =  %f \n", (float)sum_delays/num_delays);
    

}

// Scan -- heads keeps moving back and forth across disk -> prevents starvation, middle passed 2x more than end
void scan(int* arr, int num_elem){
    int request_list[num_elem];
    printf("Initial Request List of track numbers =>\n");
    for( int i = 0; i < num_elem; i ++){
            request_list[i] = arr[i];
            printf("%d ", arr[i]);
    }
    // set track number to first index of arr
    int traverse_list[num_elem];
    traverse_list[0] = request_list[0];
    
    int head = 0;
    int min_diff = 202;
    int next_head = 0;
    int count = 1;
    int travel_left = 1; // used to determine which way algorithm goes
    int total_tracks = 0;

    while(count < num_elem){

        // used to travel left
        while(travel_left == 1){
            
            for(int i= 1; i<num_elem; i++){
                if(request_list[head] > request_list[i]){
                    if(request_list[head] - request_list[i] < min_diff && head != i ){
                        min_diff = request_list[head] - request_list[i];
                        next_head = i;
                    }
                }
            }
            if(next_head == head || count == num_elem){// check if no more nodes to the left
                //calculate remaining tracks to 0
                total_tracks += request_list[head]; // since goes to zero should be the heads distnace from 0
                travel_left = 0; //set to false, so goes right next
                min_diff = 202;
                request_list[head]=0;
            }
            else{
                request_list[head] = 500;
                head = next_head;
                traverse_list[count] = request_list[head];
                total_tracks += min_diff;
                min_diff = 202;
                count++;
            }
        }
        // used to travel right
        while(travel_left == 0){
            
           for(int i=1; i<num_elem; i++){
                if(request_list[head] < request_list[i]){
                    if(request_list[i] - request_list[head] < min_diff && head != i ){
                        min_diff = request_list[i] - request_list[head];
                        next_head = i;
                    }
                }
            }
            if(next_head == head || count == num_elem){// check if no more nodes to the left
                //calculate remaining tracks to 0
                total_tracks += arr[num_elem-1]-request_list[head]; // since goes to zero should be the heads distnace from 0
                request_list[head] = 199;
                travel_left = 1; //set to false, so goes right next
                min_diff = 202;
            }
            else{
                request_list[head] = 500;
                head = next_head;
                traverse_list[count] = request_list[head];
                total_tracks += min_diff;
                min_diff = 202;
                count++;
            }
        }  
    }
    printf("\nFinal Traverse List of track numbers =>\n");
    for( int i = 0; i < num_elem; i ++){
            printf("%d ", traverse_list[i]);
    }
    printf("\nTotal number of tracks passed =  %d \n", total_tracks);

    //For longest delay - find the max shifted index
    int longest_delay = 0;
    int delay[num_elem]; // record the delays in all elements
    int num_delays = 0;
    int sum_delays = 0;
    for(int i= 0;i<num_elem;i++){
        delay[i] = 0; //no delay in head element
        for(int j=0;j<num_elem;j++){
            if(arr[i] == traverse_list[j]){
                //where the delay occurs, find the shifted index
                delay[i] = j-i; //with respect to the original index, how shifted is the new index? 
                break;
            }
        }
        if(delay[i] > longest_delay){
            longest_delay = delay[i]; //longest shifted index
        }
        //printf("%d ", delay[i]);
        if(delay[i]>0){ //only positively shifted index
            num_delays++;
            sum_delays += delay[i];
        }
    }
    printf("Longest Delay =  %d \n", longest_delay);
    printf("Average Delay =  %f \n", (float)sum_delays/num_delays);
    
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
        
    }
    else{
        // make list of 50 random integers
        createRandomList(&current_list);
        num_elem = n;
    }

    printf("\n\nSHORTEST SEEK TIME FIRST ALGORITHM: \n");
    // call sstf
    sstf(current_list, num_elem);
    
    printf("\n\nSCAN ALGORITHM: \n");
    // call scan
    scan(current_list, num_elem);

    //free malloc memory pointer
    free(current_list);
    return 0;
}