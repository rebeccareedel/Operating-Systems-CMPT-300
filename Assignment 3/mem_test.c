// Rebecca Reedel 301454910, Asmita Srivastava 301436340 -- Test Program for my_malloc.c

#include "my_malloc.h"
#include "my_queue.h"
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// size_t = number of bytes
// int = 8 bytes

// allocates memory and checks that pointer values are correct
void test1() {
    void* ptr = my_malloc(8); // 1 int 
    void* ptr1 = my_malloc(8);
    void* ptr2 = my_malloc(16); // 2 ints

    //print_table();

    // set values into allocated memory
    ptr = (int*)2;
    ptr1 = (int*)6;
    ptr2 = (int*)235;

    if (&ptr1 == &ptr + 1 && &ptr2 == &ptr + 2) {
        if (ptr == (int*)2 && ptr1 == (int*)6 && ptr2 == (int*)235) {
            printf("\nTest 1: Allocating Memory and Checking pointer values -> Success");
        }
    }
    else {
        printf("\nTest 1: Allocating Memory and Checking pointer values -> Failure");
    }
}


// allocates memory and then deallocates -- checks number free bytes changes
void test2() {
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

    if (num_free == 192 && num_free2 == 208 && num_free3 == 224 && num_free4 == 256) {
        printf("\nTest 2: Allocating then Freeing: Number Free Bytes Correct -> Success");
    }
    else {
        printf("\nTest 2: Allocating then Freeing: Number Free Bytes Correct -> Failure");
    }
}

// allocates memory and then deallocates -- checks number free chunks in queue
void test3() {
    void* ptr = my_malloc(16); // 2 int 
    void* ptr1 = my_malloc(32); // 4 ints  // MUST MODIFY HAVENT DONE YET
    void* ptr2 = my_malloc(16); // 2 ints
    // get previous number of free bytes 
    int num_block = returnNumberElements();
    // free one of the ptrs to memory chunk
    my_free(ptr2);
    // get new number of free bytes
    int num_block2 = returnNumberElements();
    // free one of the ptrs to memory chunk
    my_free(ptr);
    void* ptr3 = my_malloc(16); // 2 int
    // get new number of free bytes
    int num_block3 = returnNumberElements();
    // free one of the ptrs to memory chunk
    void* ptr4 = my_malloc(16); // 2 int
    my_free(ptr1);
    // get new number of free bytes
    int num_block4 = returnNumberElements();

    if (num_block == 1 && num_block2 == 2 && num_block3 == 2 && num_block4 == 2) {
        printf("\nTest 3: Allocating & Freeing: Number Free Block Headers Correct -> Success");
    }
    else {
        printf("\nTest 3: Allocating & Freeing: Number Free Block Headers Correct -> Failure");
    }
}

// allocates memory in order to check accuracy of coalesce property (Ability to merge contigous blocks of free memory)
void test4() {
    printf("\nAllocating 256 bytes\n");
    void* ptr = my_malloc(4);
    void* ptr1 = my_malloc(2);
    void* ptr2 = my_malloc(250);
    printf("\nNumber of free bytes = %li", checkNumBytesFree());
    //print_table();
    printf("\nFreeing 6 continguous bytes\n");
    my_free(ptr);
    my_free(ptr1);
    printf("\nNumber of free bytes = %li", checkNumBytesFree());
    printf("\nAttempting to allocate 6 new bytes: Should succeed due to Coalescence, merging adjacent free blocks!!\n");
    void* ptr3 = my_malloc(6);
    if (ptr3 == NULL) {
        printf("\nMemory allocation failed.\n");
        exit(0);
    }
    else {
        printf("\nMemory allocation successful. %d bytes allocated at address %p.\n", 6, ptr3);
    }
    printf("\nNumber of free bytes = %li", checkNumBytesFree());
    printf("\nAttempting to allocate 6 more bytes: Should fail because not enough memory. Max. capacity reached!\n");
    void* ptr4 = my_malloc(6);
    if (ptr4 == NULL) {
        printf("\nMemory allocation failed.\n");
        exit(0);
    }
    else {
        printf("\nMemory allocation successful. %d bytes allocated at address %p.\n", 6, ptr4);
    }

}

int main() {
    printf("-------------------------START OF TESTS---------------------------\n");

    test1(); // tests allocation
    mem_init();

    test2(); // tests allocation and free + checks number of bytes
    mem_init();

    test3(); // tests allocation and free + checks number of headers in the queue
    mem_init();

    //test4(); // tests coalesce property of merging adjacent free blocks to allocate memory successfully. 

    printf("\n---------------------------END OF TESTS-----------------------------\n");
}
