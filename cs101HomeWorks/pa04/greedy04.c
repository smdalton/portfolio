#include <stdio.h>
#include <stdlib.h>
#include "adjWgtVec.h"
#include "loadWgtGraph.h"
#include "minPQ.h"


void printArrays(char task, int* status, int* parent, double* fringeWgt, int numberOfVertices);
void updateFringeD(char type, MinPQ pq, AdjWgtVec edgesOfV, int v);

void greedyTree(AdjWgtVec* vecList, int numberOfVertices, int startVertex, int * parent, double *priority, int* status, char task){
    //TODO: Determine task here
    int v=0;
    MinPQ pq = createPQ(numberOfVertices, status, priority, parent);
    insertPQ(pq, startVertex, 0,-1);
    int i= 1;
    while(isEmptyPQ(pq) == 0){
        //run DijkStras
        //printf("In the while loop: %d\n", i);
        int v = getMin(pq);
        //printf("min is %d\n", v);
        delMin(pq);
        //printf("Accessing edgeList of vertex: %d", i);
        updateFringeD(task,pq,vecList[v], v);
        i++;
    }
};

void updateFringeD(char type, MinPQ pq, AdjWgtVec edgesOfV, int v){
    int i =0;
    
    
    if(type == 'D') {
        
        double myDist = getPriority(pq,v);
        //double myDist = pq->fringeWgt[v];
        AdjWgt wInfo;
        for (int i = 0; i < adjWgtSize(edgesOfV); i++) {
            wInfo = adjWgtData(edgesOfV, i);
            int w = wInfo.to;
            double newDist = myDist + wInfo.wgt;
            //if (pq->status[w] == UNSEEN) {
            if(getStatus(pq, w)==UNSEEN) {
                insertPQ(pq, w, newDist, v);
                //} else if (pq->status[w] == FRINGE) {
            }else if(getStatus(pq,w) == FRINGE){
                if (newDist < getPriority(pq, w)) {
                    decreaseKey(pq, w, newDist, v);
                }
            }
        }
        /* FOR PRIM'S MST*/
    }else if(type =='P'){
        AdjWgt wInfo;
        for(int i=0; i< adjWgtSize(edgesOfV);i++){
            wInfo = adjWgtData(edgesOfV, i);
            int w = wInfo.to;
            double newWgt = wInfo.wgt;
            if(getStatus(pq,w)== UNSEEN) {
                //if(pq->status[w] == UNSEEN){
                insertPQ(pq, w, newWgt, v);
                //}else if(pq->status[w] == FRINGE){
            }else if(getStatus(pq, w)== FRINGE){
                if(newWgt < getPriority(pq,w)){
                    decreaseKey(pq, w, newWgt, v);
                }
            }
            
        }
    }
    
};

int main(int argc, char* argv[]) {
    
    //this will hold the task value
    AdjWgtVec* vecList;
    char task = argv[1][1];
    printf("Input file is %s ", argv[1]);
    
    
    vecList = loadGraph(argc, argv, task);
    int startVertex = atoi(argv[2]);
    int numberOfVertices = adjWgtData(vecList[0],0).to;
    
    
    int* status = calloc((numberOfVertices+1), sizeof(int));
    int* parent = calloc((numberOfVertices+1), sizeof(int));
    double* fringeWgt = calloc((numberOfVertices+1), sizeof(double));
    
    //void greedyTree(EdgeList *adjInfo, int numberOfVertices, int s, int *parent, double *fringeWgt, int *status, char task)
    printf("number of nodes is:%d\n", numberOfVertices);
    
    //printAdjList(vecList);
    printf("\n\n");
    
    //printArrays(status, parent, fringeWgt, numberOfVertices);
    greedyTree(vecList,numberOfVertices,startVertex,parent,fringeWgt,status,task);
    printArrays(task, status, parent, fringeWgt, numberOfVertices);
    
    
    return 0;
}

void printArrays(char task, int* status, int* parent, double* fringeWgt, int numberOfVertices){
    if(task == 'D') {
        
        
        for (int i = 1; i < (numberOfVertices + 1); i++) {
            printf("Node:  %i\t status:  %c\t parent:  %i\t Weight:  %f\n", i, status[i], parent[i], fringeWgt[i]);
        };
    }else{
        for (int i = 1; i < (numberOfVertices + 1); i++) {
            printf("Node:  %i\t status:  %c\t parent:  %i\t Weight:  %f\n", i, status[i], parent[i], fringeWgt[i]);
        };
        
    }
}
