
//
// Created by Shane on 4/15/17.
//
#include <stdio.h>
#include <stdlib.h>

#ifndef INTVEC_INTVEC_H
#define INTVEC_INTVEC_H
//Struct for vecNode
struct IntVecNode{
    //this is a pointer to the data array that will be resized by realloc
    int * data;
    int sz;
    int capacity;
};

typedef struct IntVecNode IntVecNode;

//default constructor for a single vector Object
IntVecNode* newVecNode(int cap);

//method to reallocate the memory when the vector fills up
void resize(IntVecNode *pNode);

//debug error method to output a kill message and exit with 1 to signal error
void kill(char* message);

//push method to add an element to the vector
void push(IntVecNode* vecNode, int x);

#endif //INTVEC_INTVEC_H

