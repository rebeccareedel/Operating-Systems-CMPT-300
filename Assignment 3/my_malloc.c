// Rebecca Reedel 301454910, Asmita Srivastava 301436340

#include "my_malloc.h"
#include "my_queue.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 256

int first_call = 1; // used to check if first call to program and if should initialize DS
void* ptr; // pointer to start of memory block
int num_free_bytes; // used to check if compaction is necessary

struct block
{
    size_t value; // memory in chunk
    size_t status; // 0 = not set, 1 = busy, 2 = free
};

// acts like an array of structs with (#bytes since starter pointer)key = index and (#bytes in the chunk) value = hashtable[index], isbusy = if currently inUse
struct block blockHeader[MAX_SIZE + 1];

// creates initial memory block, hashtable for showing current memory segments, 2 arrays (inUse & notInUse) for organization
void mem_init() {
    // get initial memory block -- 256 bytes
    ptr = (size_t*)malloc(256 * sizeof(size_t));
    num_free_bytes = 256;
    reset(); // resets circular queue

    enqueue(0); // set first notInUse queue element to 0 since only 1 chunck of 256 bytes at the start

    // initialize first chunk to currently have all the memory
    blockHeader[0].value = 256;
    blockHeader[0].status = 0;
}

// displays key-value pair for all nodes in hashmap
void print_table() {
    printf("\n");
    for (size_t index = 0; index < MAX_SIZE; index++) {
        printf("\t%li\t%li\n", index, blockHeader[index].value);
    }
}


// returns pointer to memory of requested size, adds index to inUse array
void* my_malloc(size_t size) {
    // check if first time calling program -- if yes, initialize values
    if (first_call == 1) {
        mem_init();
        first_call = 0;
    }

    // get first index of notInUse Array -- check in hashtable if enough size -> repeat until finds spot
    size_t key;
    size_t index = 0;
    size_t numberElements = returnNumberElements();
    while (index < numberElements + 1) {

        // get key for available memory chunk
        key = dequeue();
        if (key == -1) {
            if (num_free_bytes > size) {
                // must do compaction --------------------------------------------------
            }
            return NULL; // queue = empty -> no available chunks
        }
        /*
        size_t value1 = blockHeader[key].value; //amount of bytes to shift over.
        if(value1 < size && num_free_bytes >= size){
            key2 = dequeue();
            size_t value2 = blockHeader[key2].value;
            I'm thinking of shifting array indices by value1, so that we can create empty block at value2.
            but shifting array indices/hash keys will involve a function which'll make it O(n2) idk. :((

        }
        */

        // search in arr[key] for # of bytes in current chunk
        size_t old_value = blockHeader[key].value;

        if (old_value != 0 && blockHeader[key + old_value].status == 2) { //colalesce from left side
            blockHeader[key].value += blockHeader[key + old_value].value;
            blockHeader[key + old_value].value = 0;
            dequeue(key + old_value);

            if (blockHeader[key].value >= size) {
                // updates current index to only have allocated size
                blockHeader[key].value = size;
                blockHeader[key].status = 1;

                // creates new index for left over memory chunk
                blockHeader[key + size].value = (blockHeader[key].value) - size; // READ!!!!! shoudlnt it be new value - size??? 
                blockHeader[key + size].status = 2;
                if (blockHeader[key + size].value != 0) {
                    enqueue(key + size); // adds new avail memory chunk header to notInUse queue 
                }
                num_free_bytes -= size; // decrease number of free bytes by amount just allocated
                // returns pointer to start of allocated chunk
                return ptr + key;
            }
            else {
                enqueue(key);
            }
        }
        else if (old_value >= size) { // check if segment size large enough for desired allocation

            // updates current index to only have allocated size
            blockHeader[key].value = size;
            blockHeader[key].status = 1;

            // creates new index for left over memory chunk
            blockHeader[key + size].value = old_value - size;
            blockHeader[key + size].status = 2;
            if (blockHeader[key + size].value != 0) {
                enqueue(key + size); // adds new avail memory chunk header to notInUse queue 
            }
            num_free_bytes -= size; // decrease number of free bytes by amount just allocated

            // returns pointer to start of allocated chunk
            return ptr + key;
        }
        else if (old_value != 0) { // make sure not one that was previously coalesced 
            enqueue(key); // not enough avail memory space in chunk for this allocation -> put back on queue for future smaller allocation
            index += 1;
        }
    }
    printf("\nNot enough memory, consider freeing some space. Cannot allocate more memory. \n");
    return NULL;
}


// makes memory available -- adds to notInUse array, checks if can coalesce with adjacent free memory
void my_free(void* free_ptr) {
    // calculate key for array of structs
    int key = free_ptr - ptr;
    // look up size (value) by the key in struct array
    size_t value = blockHeader[key].value;

    // increase number of bytes free by size
    num_free_bytes += value;

    // check if adjacent rightside blocks free -- combine if yes
    if (blockHeader[key + value].status == 2) {
        blockHeader[key].value += blockHeader[key + value].value;
        blockHeader[key + value].value = 0;
    }
    // set chunk to free
    blockHeader[key].status = 2;

    // add free chunk key to the circular queue
    enqueue(key);
}

size_t checkNumBytesFree() {
    return num_free_bytes;
}
