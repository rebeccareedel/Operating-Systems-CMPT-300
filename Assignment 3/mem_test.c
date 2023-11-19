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

// checking doesn't malloc if no space in memory chunk
void test4() {
    // allocate 256 bytes
    void* ptr = my_malloc(4);
    void* ptr1 = my_malloc(2);
    void* ptr2 = my_malloc(250);
    void* ptr3 = my_malloc(1); // should fail since not enough memory
    if (ptr3 == NULL ) {
        printf("\n Test 4: Ensuring Allocation Unsuccessful When No Free Bytes -> Success\n");
    }
    else {
        printf("\n Test 4: Ensuring Allocation Unsuccessful When No Free Bytes -> Failure\n");
    }
}

// checks that malloc doesn't work if size requested = 0 or negative 
void test5(){
    void* ptr = my_malloc(250);
    void* ptr1 = my_malloc(8);
    if (ptr1 == NULL) {
        printf("\n Test 5: Ensuring Allocation Unsuccessful When Not Enough Free Bytes -> Success\n");
    }
    else {
        printf("\n Test 5: Ensuring Allocation Unsuccessful When Not Enough Free Bytes -> Failure\n");
    }
}

// checks that malloc doesn't work if size requested = 0 or negative 
void test6(){
    void* ptr = my_malloc(0);
    void* ptr1 = my_malloc(-5);
    if (ptr == NULL && ptr1 == NULL) {
        printf("\n Test 6: Ensuring Allocation Unsuccessful When Given 0 or Negative Values -> Success\n");
    }
    else {
        printf("\n Test 6: Ensuring Allocation Unsuccessful When Given 0 or Negative Values -> Failure\n");
    }
}

// allocates memory in order to check accuracy of coalesce property in malloc (Ability to merge contigous blocks of free memory)
void test7() {
    // allocate 256 bytes
    void* ptr = my_malloc(4);
    void* ptr1 = my_malloc(2);
    void* ptr2 = my_malloc(250);
    // free 6 bytes
    my_free(ptr);
    my_free(ptr1);
    void* ptr3 = my_malloc(6); // should allocate due to left-side coalescing during malloc
    if (ptr3 != NULL) {
        printf("\n Test 7: Allocating Memory w/ Left-Side Coalescing of Free Bytes during Malloc -> Success\n");
    }
    else {
        printf("\n Test 7: Allocating Memory w/ Left-Side Coalescing of Free Bytes during Malloc -> Failure\n");
    }
}

// allocates memory in order to check accuracy of coalesce property in free
void test8() {
    // allocate 256 bytes
    void* ptr = my_malloc(4);
    void* ptr1 = my_malloc(2);
    void* ptr2 = my_malloc(250);
    // free 6 bytes
    my_free(ptr1);
    my_free(ptr);
    void* ptr3 = my_malloc(6); // should allocate due to right-side coalescing during free
    if (ptr3 != NULL) {
        printf("\n Test 8: Allocating Memory w/ Right-Side Coalescing of Free Bytes during Free -> Success\n");
    }
    else {
        printf("\n Test 8: Allocating Memory w/ Right-Side Coalescing of Free Bytes during Free -> Failure\n");
    }
}


// tests that array of structs properly updated during left-side coalescing
void test9(){
    // allocate 256 bytes
    void* ptr = my_malloc(4);
    void* ptr1 = my_malloc(2);
    void* ptr2 = my_malloc(8);
    // free bytes in left-side coalesce pattern
    my_free(ptr1);
    my_free(ptr2);
    // should set key 4 to 252 and key 6 to 0 but since need to allocate 1 byte, 
    // will set key 4 = 1, key 5 = 251 and key 6 =0
    void* ptr3 = my_malloc(1); 
    // check if key 5 = 251 and key 6 = 0 in array after
    int key5 = getValue(5);
    int key6 = getValue(6);
    if (key5 == 251 && key6 == 0) {
        printf("\n Test 9: Allocating Memory w/ Left-Side Coalescing: Chunk Values Correct -> Success\n");
    }
    else {
        printf("\n Test 9: Allocating Memory w/ Left-Side Coalescing: Chunk Values Correct -> Failure\n");
    }
}

// tests that array of structs properly updated during right-side coalescing
void test10(){
    // allocate 256 bytes
    void* ptr = my_malloc(4);
    void* ptr1 = my_malloc(2);
    void* ptr2 = my_malloc(8);
    // free bytes in left-side coalesce pattern
    my_free(ptr2); // key 6 = 250
    int key6first = getValue(6);
    int key14 = getValue(14);
    my_free(ptr1); // key 4 = 252 key 6 = 0
    // check if key 4 = 252 and key 6 = 0 in array after
    int key4 = getValue(4);
    int key6second = getValue(6);
    if (key6first == 250 && key14 == 0 && key4 == 252 && key6second == 0) {
        printf("\n Test 10: Allocating Memory w/ Right-Side Coalescing: Chunk Values Correct -> Success\n");
    }
    else {
        printf("\n Test 10: Allocating Memory w/ Right-Side Coalescing: Chunk Values Correct -> Failure\n");
    }
}
// tests that queue properly updated during left side coalescing 

// tests that queue properly updated during right side coalescing 

int main() {
    printf("-------------------------START OF TESTS---------------------------\n");

    test1(); // tests allocation
    mem_init();

    test2(); // tests allocation and free + checks number of bytes
    mem_init();

    test3(); // tests allocation and free + checks number of headers in the queue
    mem_init();
    
    test4(); // tests allocation unsucessful when no more memory free
    mem_init();
   
    test5(); // tests allocation unsuccessful if not enough memory free
    mem_init();

    test6(); // checks that malloc doesn't work if size requested = 0 or negative // tests coalesce property of merging adjacent free blocks from left-side to allocate memory successfully. 
    mem_init();
    
    test7(); // tests coalesce property of merging adjacent free blocks from left-side to allocate memory successfully. 
    mem_init();
    
    test8(); // tests coalesce property of merging adjacent free blocks from right-side to allocate memory successfully. 
    mem_init();

    test9(); // tests that array of structs properly updated during left-side coalescing
    mem_init();

    test10(); // tests that array of structs properly updated during right-side coalescing
    mem_init();

    // tests that queue properly updated during left side coalescing 

    // tests that queue properly updated during right side coalescing 

    printf("\n---------------------------END OF TESTS-----------------------------\n");
}
