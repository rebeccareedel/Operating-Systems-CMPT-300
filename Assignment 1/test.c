// Rebecca Reedel, 301454910 -- Test Program for list.c

#include "list.h"
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void free_list(List* list){
    return;
}
// should return a new empty list
void test_list_create(){
    // test1 create empty list, item number == 0
    List *list1 = List_create();
    int numberItem = list1->numberItems;
    if(numberItem == 0){
        printf("\nList_Create Test1: Create Empty List, number of items = 0 --> Success");
    }

    // test 2 create a list and append something to check its there
    List *list2 = List_create();
    int six = 6;
    void *item = &six;
    int add_val = List_append(list2, item);
    if(add_val == 0){
        printf("\nList_Create Test2: Create Empty List and add item --> Success");
    }

    // test 3 and 4 try to create 11 lists, should return NULL on 11th
    List *list3 = List_create();
    List *list4 = List_create();
    List *list5 = List_create();
    List *list6 = List_create();
    List *list7 = List_create();
    List *list8 = List_create();
    List *list9 = List_create();
    List *list10 = List_create();
    List *list11 = List_create();
    if(list10 != NULL){
        printf("\nList_Create Test3: Create 10 Lists, 10th should NOT be NULL --> Success");
    }
    if(list11 == NULL){
        printf("\nList_Create Test4: Create 11 Lists, 11th should be NULL --> Success\n\n");
    }
}

// should return the numbers of items in a list
void test_list_count(){
    // test 1 empty list, should return 0
    List *list1 = List_create();
    int numberItem = List_count(list1);
    if(numberItem == 0){
        printf("\nList_Count Test1: Create Empty List, number of items = 0 --> Success");
    }
    // test 2 list with 4 nodes
    List *list2 = List_create();
    int six = 6;
    void *item = &six;
    int add_val = List_append(list2, item);
    int add_val2 = List_append(list2, item);
    int add_val3 = List_append(list2, item);
    int add_val4 = List_append(list2, item);
    int number = List_count(list2);
    if(number == 4){
        printf("\nList_Count Test2: Add 4 items to List, number of items = 4 --> Success\n\n");
    }
}

// should return pointer to first item in list and set to curItem, or null if empty
void test_list_first(){
    // test1 empty list 
    List *list1 = List_create();
    void* firstItem = List_first(list1);
    if(firstItem == NULL){
        printf("\nList_first Test1: Create Empty List, first item == NULL --> Success");
    }
    
    // test2 list with two items
    List *list2 = List_create();
    int three = 3;
    void *item = &three;
    int six = 6;
    void *item2 = &six;
    
    int add_val = List_append(list2, item);
    int add_val2 = List_append(list2, item2);
    void* firstItem2 = List_first(list2);
    if(firstItem2 != NULL){
        printf("\nList_first Test2: Create List with 2 Items, first item != NULL --> Success\n\n");
    }
    
}

// should return pointer to last item in list and set to curItem, or null if empty
void test_list_last(){
    // test1 empty list 
    List *list1 = List_create();
    void* lastItem = List_last(list1);
    if(lastItem == NULL){
        printf("\nList_last Test1: Create Empty List, last item == NULL --> Success");
    }
    
    // test2 list with two items
    List *list2 = List_create();
    int three = 3;
    void *item = &three;
    int six = 6;
    void *item2 = &six;
    
    int add_val = List_append(list2, item);
    int add_val2 = List_append(list2, item2);
    void* lastItem2 = List_last(list2);
    if(lastItem2 != NULL){
        printf("\nList_last Test2: Create List with 2 Items, last item != NULL --> Success\n\n");
    }
    
}

// should return pointer to currentItem->nextItem. if OOB at the end, returns NULL and currentItemStatus = OOB END
void test_list_next(){
    // test1 empty list
    List *list1 = List_create();
    void *newCurrentItem = List_next(list1);
    if(newCurrentItem == NULL){
        printf("\nList_next Test1: Create Empty List, next item == NULL --> Success");
    }
    
    // test 2 only 1 node status = end
    List *list3 = List_create();
    int three = 3;
    void *item = &three;
    int add_val = List_append(list3, item);
    void *newCurrentItem2 = List_next(list3);
    if(newCurrentItem2 == NULL){
        printf("\nList_next Test2: Create List with 1 Items, next item == NULL --> Success\n\n");
    }
    
}

// should return pointer to currentItem->prevItem. if OOB at the start, returns NULL and currentItemStatus = OOB START
void test_list_prev(){
    // test1 empty list
    List *list1 = List_create();
    void *newCurrentItem = List_prev(list1);
    if(newCurrentItem == NULL){
        printf("\nList_next Test1: Create Empty List, next item == NULL --> Success");
    }
    
    // test 2 only 1 node status = end
    List *list3 = List_create();
    int three = 3;
    void *item = &three;
    int add_val = List_append(list3, item);
    void *newCurrentItem2 = List_prev(list3);
    if(newCurrentItem2 == NULL){
        printf("\nList_next Test2: Create List with 1 Items, next item == NULL --> Success\n\n");
    }
}

// should return pointer to current item in list
void test_list_curr(){
    // test1 empty list
    List *list1 = List_create();
    void* result =List_curr(list1);
    if(result == NULL){
        printf("\nList_curr Test1: Create Empty List, current item == NULL --> Success");
    }
    
    // test2 list with 2 nodes
    List *list2 = List_create();
    int three = 3;
    void *item = &three;
    int six = 6;
    void *item2 = &six;
    
    int add_val = List_append(list2, item);
    int add_val2 = List_append(list2, item2);
    void* result2 =List_curr(list2);
    if(result2 != NULL){
        printf("\nList_curr Test2: Create List with 2 Items, current item != NULL --> Success\n\n");
    }

}

// should return 0=success, -1=fail. add new item after currentItem, pList->currentItem= newItem
// if currentItemStatus == OOB and START = added at start, if OOB and end = add at end
void test_list_insert_after(){
    
    int three = 3;
    void *item = &three;
    int six = 6;
    void *item2 = &six;
    
    //test 3 nodes 
    List *list2 = List_create();
    
    int add_val = List_append(list2, item2);
    int add_val2 = List_append(list2, item2);
    int add_val3 = List_insert_before(list2, item2);
    int result2 =List_insert_after(list2, item);
    if(list2->currentItem->item == item){
        printf("\nList_insert_after Test1: Check if current item = new item inserted --> Success");
    }
    
    //test empty list oob-> start
    List *list1 = List_create();
    int result =List_insert_after(list1, item);
    if(list1->firstItem != NULL){
        printf("\nList_insert_after Test1: Empty List LIST_OOB_START, inserts at start --> Success\n\n");
    }
    
}

// should return 0=success, -1=fail. add new item before currentItem, pList->currentItem= newItem
// if currentItemStatus == OOB and START = added at start, if OOB and end = add at end
void test_list_insert_before(){
    //int result = List_before_after(list1, item);

    int three = 3;
    void *item = &three;
    int six = 6;
    void *item2 = &six;
    
    //test 3 nodes 
    List *list2 = List_create();
    
    int add_val = List_append(list2, item2);
    int add_val2 = List_append(list2, item2);
    int result2 =List_insert_before(list2, item);
    if(list2->currentItem->item == item){
        printf("\nList_insert_before Test1: Check if current item = new item inserted --> Success");
    }
    
    //test empty list oob-> start
    List *list1 = List_create();
    int result =List_insert_before(list1, item);
    if(list1->firstItem != NULL){
        printf("\nList_insert_before Test1: Empty List LIST_OOB_START, inserts at start --> Success\n\n");
    }
}

// should return 0=success, -1=fail. adds to end of list, pList->currentItem = newItem
void test_list_append(){
    // test 1 empty list, should have first item not null
    List *list1 = List_create();
    int six = 6;
    void *item = &six;
    int add_val = List_append(list1, item);
    void* firstItem = List_first(list1);
    if(firstItem != NULL){
        printf("\nList_append Test1: Create List with 1 Items, first item != NULL --> Success");
    }
    // test 2 list with 3 nodes
    List *list2 = List_create();
    int add_val2 = List_append(list2, item);
    int add_val3 = List_append(list2, item);
    int add_val4 = List_append(list2, item);
    int number = List_count(list2);
    if(number == 3){
        printf("\nList_append Test2: Append 3 items to List, number of items = 3 --> Success\n\n");
    }
}

// should return 0=success, -1=fail. adds to FRONT of list, pList->currentItem = newItem
void test_list_prepend(){
    // test 1 empty list, should have first item not null
    List *list1 = List_create();
    int six = 6;
    void *item = &six;
    int add_val = List_prepend(list1, item);
    void* firstItem = List_first(list1);
    if(firstItem != NULL && add_val == 0){
        printf("\nList_prepend Test1: Create List with 1 Items, first item != NULL --> Success");
    }
    // test 2 list with 3 nodes
    List *list2 = List_create();
    int add_val2 = List_prepend(list2, item);
    int add_val3 = List_prepend(list2, item);
    int add_val4 = List_prepend(list2, item);
    int number = List_count(list2);
    if(number == 3){
        printf("\nList_prepend Test2: Prepend 3 items to List, number of items = 3 --> Success\n\n");
    }
}

// should return and remove pList->currentItem. make nextItem the current. 
// if currentItemStatus = OOB, do not change and return NULL
void test_list_remove(){
    //test empty list
    List *list1 = List_create();
    void* removeItem = List_remove(list1);
    if(removeItem == NULL){
        printf("\nList_remove Test1: Create Empty List, return pointer == NULL --> Success");
    }
    
    //test list with 3 nodes
    int six = 6;
    void *item = &six;
    List *list2 = List_create();
    int add_val2 = List_prepend(list2, item);
    int add_val3 = List_prepend(list2, item);
    int add_val4 = List_prepend(list2, item);
    void* removeItem2 = List_remove(list2);
    if(removeItem2 != NULL){
        printf("\nList_remove Test2: Create List w/ current at start, pointer != NULL --> Success\n\n");
    }
}

// should return and remove pList->lastItem. make newLast the current. 
// if numberItem == 0, return NULL
void test_list_trim(){
    //test empty list
    List *list1 = List_create();
    void* lastItem = List_trim(list1);
    if(lastItem == NULL){
        printf("\nList_trim Test1: Create Empty List, return pointer == NULL --> Success");
    }
    
    //test list with 3 nodes
    int six = 6;
    void *item = &six;
    List *list2 = List_create();
    int add_val2 = List_prepend(list2, item);
    int add_val3 = List_prepend(list2, item);
    int add_val4 = List_prepend(list2, item);
    
    void* trimItem2 = List_trim(list2);
    if(trimItem2 != NULL){
        printf("\nList_trim Test2: Create List w/ current at start, pointer != NULL --> Success\n\n");
    }
    
}

// adds 2 lists together, list2 does not exist, list1 should have x2 nodes
void test_list_concat(){
   
    int six = 6;
    void *item = &six;
    List *list1 = List_create();
    int add_val = List_append(list1, item);

    List *list2 = List_create();
    int add_val2 = List_append(list2, item);
    int add_val3 = List_append(list2, item);
    int add_val4 = List_append(list2, item);
    //check if number of items in list2 = 0
    List_concat(list1, list2);
    if(list2 -> numberItems == 0){
        printf("\nList_concat Test1: check if number of items in list2 = 0 --> Success\n");
    }
    // check number of nodes in list1, should be x2
    if(list1->numberItems == 4){
        printf("List_concat Test2: check if list1 numberItems contains list2 --> Success\n\n");
    }
}



// list should be in freeheads and nodes in free nodes, free using FREE_FN
void test_list_free(){
    int six = 6;
    void *item = &six;  
    List *list2 = List_create();
    int add_val2 = List_append(list2, item);
    int add_val3 = List_append(list2, item);
    int add_val4 = List_append(list2, item);
    
    void* (*functionPtr)(list);
    functionPtr = &free_list;
    List_free(list2, functionPtr);

    //test frees up list 
    if(list2->currentItem == NULL){
        printf("List_free Test2: check if list free for future use --> Success\n\n");
    }
}

int main() {
    printf("-------------------------START OF TESTS---------------------------\n");
    test_list_create();
    initializeArrays();
    test_list_count();
    test_list_first();
    test_list_last();
    initializeArrays();
    test_list_next();
    test_list_prev();
    test_list_curr();
    initializeArrays();
    test_list_insert_after();
    test_list_insert_before();
    test_list_append();
    initializeArrays();
    test_list_prepend();
    test_list_remove();
    initializeArrays();
    test_list_trim();
    test_list_concat();
    test_list_free();
    printf("---------------------------END OF TESTS-----------------------------\n");
}
