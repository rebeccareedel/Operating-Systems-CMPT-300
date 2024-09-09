// Rebecca Reedel
#include "list.h"
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

// used to see if first time calling list_create function
static int isFirstTime = 1;

static int numberHeads = 0;

// creates empty Arrays for nodes and list heads
static Node nodeArray[100];
static List listArray[10];

// pointers to first free and last free so can keep track of unused
static Node *firstFreeNode = &nodeArray[0];
static Node *lastFreeNode = &nodeArray[99];

static List *firstFreeHead = &listArray[0];
static List *lastFreeHead = &listArray[9];

// initializes two arrays, to have nodes point to one next to it
void initializeArrays(){
    for(int i = 0; i<99; i++){
        nodeArray[i].nextItem = &nodeArray[i+1];
        nodeArray[i+1].prevItem = &nodeArray[i];
    }
    nodeArray[99].nextItem = NULL;

    for(int i = 0; i < 9; i++){
        listArray[i].nextHead = &listArray[i+1];
    }
    listArray[9].nextHead = NULL;

    numberHeads = 0;

    firstFreeNode = &nodeArray[0];
    lastFreeNode = &nodeArray[99];

    firstFreeHead = &listArray[0];
    lastFreeHead = &listArray[9];
}

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){
    if(numberHeads >= 10){
        return NULL;
    }
    // if first time creating a list head, initializes empty arrays with pointers
    if(isFirstTime == 1){
        initializeArrays();
        isFirstTime = 0;
    }
    // checks if no more space for new list head
    if(firstFreeHead == NULL){
        return NULL;
    }
    // sets first free head pointer to next head in the list
    List *newList = firstFreeHead;
    List *nextFreeHead = firstFreeHead->nextHead;
    firstFreeHead = nextFreeHead;
    
    // initalize values of list head to NULL and 0
    newList->currentItem = NULL;
    newList->firstItem = NULL;
    newList->lastItem = NULL;
    newList->nextHead = NULL;
    newList->numberItems = 0;
    newList->currentItemStatus = LIST_OOB_START;
    
    numberHeads += 1;
    return newList;
}

// Returns the number of items in pList.
int List_count(List* pList){
    return pList->numberItems;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if(pList->firstItem == NULL){
        pList->currentItem = NULL;
        return NULL;
    }
    pList->currentItem = pList->firstItem;
    return pList->firstItem;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
    if(pList->lastItem == NULL){
        pList->currentItem = NULL;
        return NULL;
    }
    pList->currentItem = pList->lastItem;
    return pList->lastItem;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
    if(pList->currentItem == pList->lastItem){
        pList->currentItemStatus = LIST_OOB_END;
        pList->currentItem = NULL;
        return NULL;
    }
    pList->currentItem = pList->currentItem->nextItem;
    return pList->currentItem;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    if(pList->currentItem == pList->firstItem){
        pList->currentItemStatus = LIST_OOB_START;
        pList->currentItem = NULL;
        return NULL;
    }
    pList->currentItem = pList->currentItem->prevItem;
    return pList->currentItem;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
    return pList->currentItem;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem){
    if(firstFreeNode !=  NULL){
        // get free node to put item into
        Node* nextFree = firstFreeNode->nextItem;
        firstFreeNode->item = pItem;
        
        if(pList->currentItem == NULL){
            // inserts at the start
            if(pList->numberItems == 0){
                pList->firstItem = firstFreeNode;
                pList->lastItem = firstFreeNode;
            }
            else if (pList->currentItemStatus == LIST_OOB_START){
                firstFreeNode->nextItem = pList->firstItem;
                pList->firstItem->prevItem = firstFreeNode;
                pList->firstItem = firstFreeNode;
            }
            // inserts at the end
            else {
                firstFreeNode->prevItem = pList->lastItem;
                pList->lastItem->nextItem = firstFreeNode;
                pList->lastItem = firstFreeNode;
            }
        }
        else{
            //save pointer to next item after inserting new item
            Node* pNextItem = pList->currentItem->nextItem;
            pList->currentItem->nextItem = firstFreeNode;

            // set next and previous node pointers for inserted item
            firstFreeNode->nextItem = pNextItem;
            firstFreeNode->prevItem = pList->currentItem;
        }

        //set current item to new item and move free node pointer to next free
        pList->currentItem = firstFreeNode;
        firstFreeNode = nextFree;

        // increase number of nodes
        int newNumberNodes = pList->numberItems +1;
        pList->numberItems = newNumberNodes;

        return 0;
    }
    return -1;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem){
    if(firstFreeNode !=  NULL){
        // get free node to put item into
        Node* nextFree = firstFreeNode->nextItem;
        firstFreeNode->item = pItem;
        
        if(pList->currentItem == NULL){
            // inserts at the start
            if(pList->numberItems == 0){
                pList->firstItem = firstFreeNode;
                pList->lastItem = firstFreeNode;
            }
            else if (pList->currentItemStatus == LIST_OOB_START){
                firstFreeNode->nextItem = pList->firstItem;
                pList->firstItem->prevItem = firstFreeNode;
                pList->firstItem = firstFreeNode;
            }
            // inserts at the end
            else {
                firstFreeNode->prevItem = pList->lastItem;
                pList->lastItem->nextItem = firstFreeNode;
                pList->lastItem = firstFreeNode;
            }
        }
        else{
            //save pointer to prev item after inserting new item
            Node* pPrevItem = pList->currentItem->prevItem;
            pList->currentItem->prevItem = firstFreeNode;

            // set next and previous node pointers for inserted item
            firstFreeNode->prevItem = pPrevItem;
            firstFreeNode->nextItem = pList->currentItem;
        }

        //set current item to new item and move free node pointer to next free
        pList->currentItem = firstFreeNode;
        firstFreeNode = nextFree;

        // increase number of nodes
        int newNumberNodes = pList->numberItems +1;
        pList->numberItems = newNumberNodes;

        return 0;
    }
    return -1;
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    if(firstFreeNode !=  NULL){
        // get free node to put item into
        Node* nextFree = firstFreeNode->nextItem;
        firstFreeNode->item = pItem;
        // if not empty list 
        if(pList->numberItems >= 1){
            //put new node as new last node
            firstFreeNode->prevItem = pList->lastItem;
            pList->lastItem->nextItem = firstFreeNode;  
            firstFreeNode->nextItem = NULL;
        }
        else{ // if empty
            pList->firstItem = firstFreeNode;
        }
                
        //set current item to new item and move free node pointer to next free
        pList->currentItem = firstFreeNode;
        pList->lastItem = firstFreeNode;
        firstFreeNode = nextFree;
        
        // increase number of nodes
        int newNumberNodes = pList->numberItems +1;
        pList->numberItems = newNumberNodes;
        
        return 0;
    }
    return -1;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
     if(firstFreeNode !=  NULL){
        // get free node to put item into
        Node* nextFree = firstFreeNode->nextItem;
        firstFreeNode->item = pItem;
        // if not empty list 
        if(pList->numberItems >= 1){
            //put new node as new last node
            firstFreeNode->nextItem = pList->firstItem;
            pList->firstItem->prevItem = firstFreeNode;  
            firstFreeNode->prevItem = NULL;
        }
        else{ // if empty
            pList->lastItem = firstFreeNode;
        }
        //set current item to new item and move free node pointer to next free
        pList->currentItem = firstFreeNode;
        pList->firstItem = firstFreeNode;
        firstFreeNode = nextFree;

        // increase number of nodes
        int newNumberNodes = pList->numberItems +1;
        pList->numberItems = newNumberNodes;

        return 0;
    }
    return -1;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    if(pList->currentItem == NULL){
        return NULL;
    }
    // remove curent and set last free node next to it
    lastFreeNode->nextItem = pList->currentItem;
    lastFreeNode->nextItem->prevItem = lastFreeNode;

    // fix gap of pointers left after removing current 
    Node* nextCurrent = pList->currentItem->nextItem;
    Node* prevCurrent = pList->currentItem->prevItem;
    pList->currentItem = nextCurrent;
    pList->currentItem->prevItem = prevCurrent;

    //make last free node = new current removed
    lastFreeNode = lastFreeNode->nextItem;
    lastFreeNode->nextItem = NULL;

    // decrease number of nodes
    int newNumberNodes = pList->numberItems -1;
    pList->numberItems = newNumberNodes;

    return lastFreeNode;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    if(pList->firstItem == NULL){
        return NULL;
    }
    // puts last node at end of free nodes list
    lastFreeNode->nextItem = pList->lastItem;
    lastFreeNode->nextItem->prevItem = lastFreeNode;
    
    // set last item to current
    pList->lastItem = pList->lastItem->prevItem;
    pList->currentItem = pList->lastItem;
    
    // decrease number of nodes
    int newNumberNodes = pList->numberItems -1;
    pList->numberItems = newNumberNodes;

    // set removed node as last free node
    lastFreeNode = lastFreeNode->nextItem;
    lastFreeNode->nextItem = NULL;
    
    return lastFreeNode;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    pList1->lastItem->nextItem = pList2->firstItem;
    pList2->firstItem->prevItem = pList1-> lastItem;
    pList1->lastItem = pList2->lastItem;
    
    // calculate new number of nodes from both lists
    int newNumberNodes = pList2->numberItems + pList1->numberItems;
    pList1->numberItems = newNumberNodes;
    
    // set the last free head to plist2
    lastFreeHead->nextHead = pList2;
    lastFreeHead = pList2;
    pList2->numberItems = 0;

    numberHeads -= 1;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn){
    // add nodes to end of list of free nodes
    lastFreeNode->nextItem = pList->firstItem;
    pList->firstItem->prevItem = lastFreeNode;
    lastFreeNode = pList->lastItem;

    // add pList to list of free heads
    lastFreeHead->nextHead = pList;
    pList->currentItem = NULL;
    pList->firstItem = NULL;
    pList->lastItem = NULL;
    pList->numberItems = 0;
    lastFreeHead = pList;
    
    numberHeads -= 1;
    // free all nodes
    (*pItemFreeFn)(pList);
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);


void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    
    // start at currentItem
    Node* node = pList->currentItem;
    //start at first node
    if(pList->currentItemStatus == LIST_OOB_START){
        node = pList->firstItem;
    }

    while(node != NULL){
        void* value = node->item;
        int result = (*pComparator)(value, pComparisonArg);
        node = node->nextItem;
        if(result == 1){
            pList->currentItem = node;
            return pList;
        }
    }
    pList->currentItem = NULL;
    pList->currentItemStatus = LIST_OOB_END;
    return NULL;
}
