//
// Created by Shane on 4/15/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "intVec.h"

void kill(char* message){
    printf("%s", message);
    exit(1);
}

void printVecList(IntVecNode *pNode[]);

//Implement a push function
void push(IntVecNode* vecNode, int x){
    if(vecNode->capacity == vecNode->sz) {
        resize(vecNode);
    }
    vecNode->data[vecNode->sz] = x;
    vecNode->sz++;
}


//function to change the dataSize in a vecNode
void resize(IntVecNode *vecNode) {
    //make a new array for the data
    int* newData = realloc(vecNode->data,vecNode->capacity*2*sizeof(int));
    if(newData!=NULL){
        vecNode->capacity*=2;
        vecNode->data = newData;
    }else{
        kill("resize fail");
    }
}

//Implement a Constructor to return a IntVecNode
IntVecNode*  newVecNode(/*parameters here*/int cap){
    IntVecNode* vecNode;
    vecNode = calloc(1, sizeof(IntVecNode));
    if(vecNode == NULL){
        kill("Calloc vecNode allocation fail");
    }else{
        vecNode->data = calloc(cap, sizeof(int));
        vecNode->capacity = cap;
        vecNode->sz = 0;
    }
    return vecNode;
}
//
//void printVecNodes(IntVecNode* vecList, int size){
//    for(int i = 0; i < size ;i++){
//        vecList[i].sz = 3*i;
//        printf("VecNode # %d has value %d\n",i,vecList[i].sz);
//    }
//}