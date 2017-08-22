//
// Created by Shane on 5/11/17.
//

//
// Created by Shane on 4/18/17.
//
#include <stdio.h>
#include <stdlib.h>
#include "intVec.h"

static void resize(IntVec vecNode);

static void kill(char* message);
/* PRE: myVec exists
*  POST: returns an integer does not mutate the data
*/
//get the top most recent added value
int intTop(IntVec myVec){
    int size = intSize(myVec);
    return myVec->data[size-1];
}

//get an index access
int intData(IntVec myVec, int i){
    return myVec->data[i];
}

//get the size of an entry
int intSize(IntVec myVec){
    return myVec->sz;
}
//get the capacity
int intCapacity(IntVec myVec){
    return myVec->capacity;
}

//constructor
IntVec intMakeEmptyVec(void){
    IntVec vecNode = calloc(1, sizeof(IntVec));
    if(vecNode == NULL){
        kill("calloc constructor fail");
    }else{
        vecNode->data = calloc(intInitCap,sizeof(int));
        vecNode->capacity = intInitCap;
        vecNode->sz = 0;
    }
    return vecNode;
}

//pusher
void intVecPush(IntVec myVec, int newE){
    if(myVec->capacity == myVec->sz){
        resize(myVec);
    }
    myVec->data[myVec->sz] = newE;
    myVec->sz++;
}

void intVecPop(IntVec myVec){
    myVec->sz--;
}

static void resize(IntVec vecNode) {
    int* newData = realloc(vecNode->data,vecNode->capacity*2*sizeof(int));
    if(newData!=NULL){
        vecNode->capacity *=2;
        vecNode->data = newData;
    }else{
        kill("resize fail");
    }
}

static void kill(char *message) {
    printf("ERROR %s", message);
    exit(1);
}


