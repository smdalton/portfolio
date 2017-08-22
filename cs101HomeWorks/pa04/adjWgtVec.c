//
// Created by Shane on 6/3/17.
//

#include <stdlib.h>
#include "adjWgtVec.h"
#include <stdio.h>


struct AdjWgtVecNode{
    //each node will have a data element that contains a pointer to an array of AdjWgt objects
    AdjWgt* data;
    //The size of the array
    int sz;
    int capacity;
};


AdjWgt adjWgtTop(AdjWgtVec myVec){
    int size = adjWgtSize(myVec);
    return myVec->data[size-1];
};

//returns that data at position i in the AdjWgtVec
AdjWgt adjWgtData(AdjWgtVec myVec, int i){
    return myVec->data[i];
}

/** adjWgtSize()
 * precondition: myVec has been constructed.
 */
int adjWgtSize(AdjWgtVec myVec){
    return myVec->sz;
}


int adjWgtCapacity(AdjWgtVec myVec){
    return myVec->capacity;
}

/* Constructors
 */
 //AdjWgtVec is already a pointer by typedef
AdjWgtVec adjWgtMakeEmptyVec(void){
    // allocate memory for a vector of AdjWgt strcuts
    AdjWgtVec edgeVec = calloc(1,sizeof(AdjWgtVec));
    //check if it is null and print a message if so
    if(edgeVec == NULL){
        printf("Pointer in make empty adjwgt is broken");
        return(-1);
    }else{
        //init data to be a list of adjWgt objects
        edgeVec->data = calloc(adjWgtInitCap,sizeof(AdjWgt));
        edgeVec->capacity = adjWgtInitCap;
        edgeVec->sz = 0;
    }
    return edgeVec;
 }


static void resize(AdjWgtVec vecNode){
    AdjWgt* newData = realloc(vecNode->data, vecNode->capacity*2*sizeof(AdjWgt));
    if(newData!=NULL){
        vecNode->capacity *=2;
        vecNode->data = newData;
    }else{
        printf("resize failure");
    }
}
void adjWgtVecPush(AdjWgtVec myVec, AdjWgt newE){
    //push a new edge onto the array
    if(myVec->capacity == myVec->sz){
        resize(myVec);
    }
    myVec->data[myVec->sz] = newE;
    myVec->sz++;
    //printf("Size is %d", myVec->sz);
}
void adjWgtVecPop(AdjWgtVec myVec){
    myVec->sz--;
}



