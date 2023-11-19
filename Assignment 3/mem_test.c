// Rebecca Reedel, 301454910 Asmita Srivastava, -- Test Program for my_malloc.c

#include "my_malloc.h"
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// size_t = number of bytes
// int = 8 bytes

// allocates memory and checks that pointer values are correct
void test1(){
    void* ptr = my_malloc(8); // 1 int 
    void* ptr1 = my_malloc(8);
    void* ptr2 = my_malloc(16); // 2 ints
    
    //print_table();
    
    // set values into allocated memory
    ptr = (int*)2;
    ptr1 = (int*)6;
    ptr2 = (int*)235;
    
    if(&ptr1 == &ptr + 1 && &ptr2 == &ptr + 2){
        if(ptr == (int*)2 && ptr1 == (int*)6 && ptr2 == (int*)235){
            printf("\nTest 1: Allocating Memory and Checking pointer values -> Success");
        }
    }
    else{
        printf("\nTest 1: Allocating Memory and Checking pointer values -> Failure");
    }
}


// allocates memory and then deallocates -- checks number free bytes changes
void test2(){
    void* ptr = my_malloc(16); // 2 int 
    void* ptr1 = my_malloc(32); // 4 ints
    void* ptr2 = my_malloc(16); // 2 ints

    // get previous number of free bytes 
    int num_free = checkNumBytesFree();

    // free one of the ptrs to memory chunk
    my_free(ptr2); 
    
    // get new number of free bytes
    int num_free2 = checkNumBytesFree(); 

    // free one of the ptrs to memory chunk
    my_free(ptr); 
    
    // get new number of free bytes
    int num_free3 = checkNumBytesFree();

    // free one of the ptrs to memory chunk
    my_free(ptr1); 

    // get new number of free bytes
    int num_free4 = checkNumBytesFree();

    if(num_free == 192 && num_free2 == 208 && num_free3 == 224 && num_free4 == 256){
        printf("\nTest 2: Allocating then Freeing: Number Free Bytes Correct -> Success");
    }
    else{
        printf("\nTest 2: Allocating then Freeing: Number Free Bytes Correct -> Failure");
    }
}

// allocates memory and then deallocates -- checks number free chunks in queue
void test3(){
    void* ptr = my_malloc(16); // 2 int 
    void* ptr1 = my_malloc(32); // 4 ints  // MUST MODIFY HAVENT DONE YET
    void* ptr2 = my_malloc(16); // 2 ints

    // get previous number of free bytes 
    int num_free = checkNumBytesFree();

    // free one of the ptrs to memory chunk
    my_free(ptr2); 
    
    // get new number of free bytes
    int num_free2 = checkNumBytesFree(); 

    // free one of the ptrs to memory chunk
    my_free(ptr); 
    
    // get new number of free bytes
    int num_free3 = checkNumBytesFree();

    // free one of the ptrs to memory chunk
    my_free(ptr1); 

    // get new number of free bytes
    int num_free4 = checkNumBytesFree();

    if(num_free == 192 && num_free2 == 208 && num_free3 == 224 && num_free4 == 256){
        printf("\nTest 2: Allocating then Freeing: Number Free Bytes Correct -> Success");
    }
    else{
        printf("\nTest 2: Allocating then Freeing: Number Free Bytes Correct -> Failure");
    }
}

int main() {
    printf("-------------------------START OF TESTS---------------------------\n");
   
    test1(); // tests allocation
    mem_init();

    test2(); // tests allocation and free + checks number of bytes
    mem_init();

    test3(); // tests allocation and free + checks number of headers in the queue

    printf("\n---------------------------END OF TESTS-----------------------------\n");
}
