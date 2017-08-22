//
// Created by Shane on 6/3/17.
//

#include <stdlib.h>
#include <printf.h>
#include "minPQ.h"

//Implementation as described in the text
struct MinPQNode{
    int numVertices;
    int numPQ;
    int minVertex;
    double oo;
    
    int* status;
    int* parent;
    double* fringeWgt;
};
void insertPQ(MinPQ pq, int id, double priority, int par){
    pq->parent[id]= par;
    pq->fringeWgt[id] = priority;
    pq->status[id] = FRINGE;
    pq->minVertex = -1;
    pq->numPQ++;
}

int isEmptyPQ(MinPQ pq){
    return pq->numPQ == 0;
}

int getMin(MinPQ pq){
    //based on the current fringe, then returns the min after updating
    if(pq->minVertex == -1) {
        
        double minWgt = pq->oo;
        for (int id = 1; id <= pq->numVertices; id++) {
            if ((pq->status[id] == FRINGE) && (pq->fringeWgt[id] < minWgt)) {
                //if there is a fringe element with fringeWgt less than minWgt
                //Then update PQ's minWgt
                pq->minVertex = id;
                minWgt = pq->fringeWgt[id];
            }
        }
    }
    return pq->minVertex;
}

int getStatus(MinPQ pq, int id){
    return pq->status[id];
}

int getParent(MinPQ pq, int id){
    return pq->parent[id];
}

double getPriority(MinPQ pq, int id){
    return pq->fringeWgt[id];
}

/* ***************** Manipulation procedures */

void delMin(MinPQ pq){
    int oldMin = getMin(pq);
    pq->status[oldMin]= INTREE;
    pq->minVertex = -1;
    pq->numPQ --;
}

void decreaseKey(MinPQ pq, int id, double priority, int par){
    pq->parent[id] = par;
    pq->fringeWgt[id] = priority;
    pq->minVertex = -1;
}

MinPQ createPQ(int n, int status[], double priority[], int parent[]){
    //int n is the size of the priority queue
    MinPQ pq = calloc(1,sizeof(struct MinPQNode));
    pq->parent = parent;
    pq->fringeWgt = priority;
    pq->status = status;
    //init the PQ on the size of the vertices, set all to unseen at start time
    for(int i=1; i<(n+1);i++){
        pq->fringeWgt[i]=0;
        pq->status[i] = UNSEEN;
        //pq->parent[i] = -1;
    }
    pq->numVertices = n;
    pq->numPQ = 0;
    pq->minVertex = -1;
    pq->oo = 100000000;
    return pq;
}
/* ***************** Constructors */


