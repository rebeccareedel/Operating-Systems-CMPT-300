// Rebecca Reedel, 301454910 Asmita Srivastava,

#include "my_malloc.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 256

int num_free_bytes = 0; // used to check if compaction is necessary
int first_call = 1; // used to check if first call to program and if should initialize DS
int *ptr;

// create inUse Array -- should be empty but initialized to be size of 256 bytes
int * inUse[MAX_SIZE] = {NULL};

// create notInUse Array -- should be initialized to have 0 index
int * notInUse[MAX_SIZE] = {NULL};

// each node in hashtable has key and value, 
// key = number of bytes from base ptr, value = number of bytes allocated in segment
typedef struct {
    int key;
    int value;
} bytes;

bytes * hash_table[MAX_SIZE];

void hash_table_insert(bytes *b) {
    int index = b->key;
    hash_table[index] = b;
}
bytes *hash_table_search(int *key){
    int index = key;
    if (hash_table[index] != NULL && hash_table[index]->key == key){
        return hash_table[index];
    } else{
        return NULL;
    }
    
}
// creates initial memory block, hashtable for showing current memory segments, 2 arrays (inUse & notInUse) for organization
void mem_init(){
    // get initial memory block -- 256 bytes
    ptr = (int*)malloc(32 * sizeof(int));
    
    notInUse[0] = 0; // 0 since currently only 1 big block with 256 bytes

    // create and initialize hashtable for each 256 byte
    bytes init = {.key = 0, .value = 256};
    hash_table_insert(&init);
}
/*
void print_table(){
    for (int i=0; i< MAX_SIZE; i++){
        if(hash_table[i] == NULL) {
            printf("\t%i\t--\n", i);
        } else{
            printf("\t%i\t%i\n", i, hash_table[i]->value);
        }
    }
}
*/
// returns pointer to memory of requested size, adds index to inUse array
void *my_malloc(size_t size){
    // check if first time calling program -- if yes, initialize values
    if(first_call == 1){
        mem_init();
        first_call = 0;
    }
    print_table();
    
    // get first index of notInUse Array -- check in hashtable if enough size -> repeat until finds spot
    int key;
    int index = 0;
    int foundSpot = 0;
    while(foundSpot == 0 && index < 256){
        key = notInUse[index];
        // search in hashmap[key] for value 
        int old_value = hash_table_search(key);
        // check if segment size large enough for desired allocation
        if (old_value >= size){
            hash_table[key] = size;
            bytes user = {.key = key+old_value, .value = old_value - size};
            hash_table_insert(&user);
            foundSpot = 1;
            return ptr + key;
        }

        index += 1;
    }
    
    return 0;
}


// makes memory available -- adds to notInUse array, checks if can coalesce with adjacent free memory
void my_free(void *ptr){
    // calculate key for hashtable
    
    // remove from inUse Array
    
    // look up size (value) by the key in hashtable 

    // check if adjacent blocks in notInUse array by doing key+size and key-1 -- combine if yes

    // update lower address to have both sizes and set bigger index size to 0
    
    // remove bigger index from notInUse Array
    
}
