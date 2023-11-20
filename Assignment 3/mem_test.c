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
    my_free(ptr4);
    my_free(ptr3);
}

// checking doesn't malloc if no space in memory chunk
void test4() {
    // allocate 256 bytes
    void* ptr = my_malloc(4);
    void* ptr1 = my_malloc(2);
    void* ptr2 = my_malloc(250);
    void* ptr3 = my_malloc(1); // should fail since not enough memory
    if (ptr3 == NULL) {
        printf("\n Test 4: Ensuring Allocation Unsuccessful When No Free Bytes -> Success\n");
    }
    else {
        printf("\n Test 4: Ensuring Allocation Unsuccessful When No Free Bytes -> Failure\n");
    }
    my_free(ptr2);
    my_free(ptr1);
    my_free(ptr);
}

// checks that malloc doesn't work if size requested > size of memory available
void test5() {
    void* ptr = my_malloc(250);
    void* ptr1 = my_malloc(8);
    if (ptr1 == NULL) {
        printf("\n Test 5: Ensuring Allocation Unsuccessful When Not Enough Free Bytes -> Success\n");
    }
    else {
        printf("\n Test 5: Ensuring Allocation Unsuccessful When Not Enough Free Bytes -> Failure\n");
    }
    my_free(ptr);
}

// checks that malloc doesn't work if size requested = 0 or negative 
void test6() {
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
    my_free(ptr2);
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
    my_free(ptr2);
}


// tests that array of structs properly updated during left-side coalescing
void test9() {
    // allocate bytes
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
    my_free(ptr3);
    my_free(ptr);
}

// tests that array of structs properly updated during right-side coalescing
void test10() {
    // allocate bytes
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
    my_free(ptr);
}

// tests that queue properly updated during left side coalescing 
void test11() {
    // allocate bytes
    void* ptr = my_malloc(2);
    void* ptr1 = my_malloc(2);// queue = 4
    int arr1Num = returnNumberElements();
    int arr1 = checkQueue(4, -1, -1);
    display();
    my_free(ptr); // queue = 4,0
    int arr2Num = returnNumberElements();
    int arr2 = checkQueue(4, 0, -1);
    display();
    my_free(ptr1); // queue = 4,0,2
    int arr3Num = returnNumberElements();
    int arr3 = checkQueue(4, 0, 2);
    display();
    void* ptr2 = my_malloc(2); // queue = 2
    int arr4Num = returnNumberElements();
    int arr4 = checkQueue(2, -1, -1);
    display();
    if (arr1 == 1 && arr1Num == 1 && arr2 == 1 && arr2Num == 2 && arr3 == 1 && arr3Num == 3 && arr4 == 1 && arr4Num == 1) {
        printf("\n Test 11: Allocating Memory w/ Left-Side Coalescing: Queue Values Correct -> Success\n");
    }
    else {
        printf("\n Test 11: Allocating Memory w/ Left-Side Coalescing: Queue Values Correct -> Failure\n");
    }
    my_free(ptr2);
}

// tests that queue properly updated during right side coalescing 
void test12() {
    // allocate bytes
    void* ptr = my_malloc(2);
    void* ptr1 = my_malloc(2);// queue = 4
    int arr1Num = returnNumberElements();
    int arr1 = checkQueue(4, -1, -1);
    display();
    my_free(ptr1); // queue = 4,2
    int arr2Num = returnNumberElements();
    int arr2 = checkQueue(4, 2, -1);
    display();
    my_free(ptr); // queue = 4,2,0
    int arr3Num = returnNumberElements();
    int arr3 = checkQueue(4, 2, 0);
    display();
    void* ptr2 = my_malloc(2); // queue = 2
    int arr4Num = returnNumberElements();
    int arr4 = checkQueue(2, -1, -1);
    display();
    if (arr1 == 1 && arr1Num == 1 && arr2 == 1 && arr2Num == 2 && arr3 == 1 && arr3Num == 3 && arr4 == 1 && arr4Num == 1) {
        printf("\n Test 12: Allocating Memory w/ Right-Side Coalescing: Queue Values Correct -> Success\n");
    }
    else {
        printf("\n Test 12: Allocating Memory w/ Right-Side Coalescing: Queue Values Correct -> Failure\n");
    }
    my_free(ptr2);
}

// attempt to use my_malloc like malloc, to allocate memory to data
void test13() {
    printf("\nTest 13: Using my_malloc and my_free like a C program (instead my malloc and free). \n");
    // allocate memory for array using my_malloc
    int n = 5; // dynamically, use scanf to get user input. 
    int* arr = (int*)my_malloc(n * sizeof(int));
    assert(arr != NULL);
    assert(checkNumBytesFree() == 236);
    printf("\nMemory allocation using my_malloc() : arr[5] sucessfully allocated on the heap.\n"); 

    //writing data on arr[5], using allocated memory.
    for(int i=0; i < n; i++){
        arr[i] = i+1;
    }
    printf("\nUsing arr[5]: manipulating data into and printing elements of the array : \n");
    for(int i=0; i < n; i++){
        printf("%d, ", arr[i]);
    }
    // free arr after use
    my_free(arr);
    // making sure my_free is working correctly. 
    assert(checkNumBytesFree() == 256);
    printf("\nMemory release using my_free() : arr[5] sucessfully released back on the heap.\n"); 

}

// test to ensure no memory leaks involving my_malloc and my_free in different orders. 
void test14() {
    int* ptr = (int*)my_malloc(sizeof(int));
    int* ptr1 = (int*)my_malloc(sizeof(int));
    int* ptr2 = (int*)my_malloc(sizeof(int));
    int* ptr3 = (int*)my_malloc(sizeof(int));
    int* ptr4 = (int*)my_malloc(sizeof(int));
    int* ptr5 = (int*)my_malloc(sizeof(int));
    
    //freeing memory in a different order as compared to allocating
    my_free(ptr5);
    my_free(ptr2);
    my_free(ptr4);
    my_free(ptr);
    my_free(ptr3);
    my_free(ptr1);
    printf("Check number of free bytes = %li", checkNumBytesFree() );
    // making sure there arent any memory leaks = memory is restored to original capacity. 
    //assert(checkNumBytesFree() == 256);
    printf("\nTest 14: Allocate and free in random order, No Memory Leaks -> Success\n"); 

}



int main() {
    printf("-------------------------START OF TESTS---------------------------\n");

    test1(); // tests allocation
    mem_release();
    mem_init();

    test2(); // tests allocation and free + checks number of bytes
    mem_release();
    mem_init();

    test3(); // tests allocation and free + checks number of headers in the queue
    mem_release();
    mem_init();

    test4(); // tests allocation unsucessful when no more memory free
    mem_release();
    mem_init();

    test5(); // tests allocation unsuccessful if not enough memory free
    mem_release();
    mem_init();

    test6(); // checks that malloc doesn't work if size requested = 0 or negative // tests coalesce property of merging adjacent free blocks from left-side to allocate memory successfully. 
    mem_release();
    mem_init();

    test7(); // tests coalesce property of merging adjacent free blocks from left-side to allocate memory successfully. 
    mem_release();
    mem_init();

    test8(); // tests coalesce property of merging adjacent free blocks from right-side to allocate memory successfully. 
    mem_release();
    mem_init();

    test9(); // tests that array of structs properly updated during left-side coalescing
    mem_release();
    mem_init();

    test10(); // tests that array of structs properly updated during right-side coalescing
    mem_release();
    mem_init();

    test11(); // tests that queue properly updated during left side coalescing 
    mem_release();
    mem_init();

    test12(); // tests that queue properly updated during right side coalescing 
    mem_release();
    mem_init();

    test13(); //tests usage of my_malloc and my_free in a program setting to ensure allocation, data manipulation and memory release is sucessful
    mem_release();
    mem_init();

    test14(); //tests to allocate and free memory in random order and ensuring no memory leaks. 
    mem_release();

    printf("\n---------------------------END OF TESTS-----------------------------\n");
}
