//
// Created by Shane on 6/3/17.
//

#include "loadWgtGraph.h"
#include "adjWgtVec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PRE: argv[1] contains the filename of input graph or a flag -U
 * POST: intVec structure is returned to caller
 */
AdjWgtVec* loadGraph(int argc, char* argv[], char task){
    //loadGraph will read the file in the folder with specified name

    FILE* inFile=NULL;
    if(argc != 4 ){
        printf("\n");
        printf("\nUsage: %s<flag> <input file>\n ", argv[0]);
        exit(EXIT_FAILURE);
    }else{
        printf("Undirected mode not set\n");
        inFile = fopen(argv[3],"r");
    }

    if((strcmp(argv[1],"-U")==0)) {
    }


    //necessary vars for file processing
    //inFile = fopen("input.txt","r");
    int numNodes=0;
    int edges =0;
    char line[150];
    int first=0;
    int second=0;
    float weight=0;

    if(inFile==NULL){
        printf("input file is showing null");
        exit(2);
    }

    fgets(line,150,inFile);
    sscanf(line,"%d",&numNodes);
    numNodes++;

    //Make a pointer for the list of adjacency lists
    AdjWgtVec* vecList = calloc(numNodes,(sizeof(AdjWgtVec)));
    //fil lthe list with empty nodes
    for(int i=0; i<numNodes;i++){
        vecList[i] = adjWgtMakeEmptyVec();
    }

    AdjWgt edge;
    edge.to = numNodes-1;
    //printf("edge.to: %d ",edge.to);
    edge.wgt = -1;
    adjWgtVecPush(vecList[0],edge);

    //printf("Number of nodes is %d\n",adjWgtData(vecList[0],0).to);
    edge.to =0;
    edge.wgt =0;
    while(fgets(line,150,inFile)!=NULL){
        sscanf(line,"%d %d %lf",&first,&edge.to,&edge.wgt);
        if(task == 'D') {
            adjWgtVecPush(vecList[first], edge);
        }else if(task == 'P'){
            adjWgtVecPush(vecList[first], edge);
            int destVertex = edge.to;
            edge.to = first;
            adjWgtVecPush(vecList[destVertex],edge);
        }
            edges++;
    }

    fclose(inFile);
    return vecList;
}

void printAdjList(AdjWgtVec* vecList){
    //get the size from position zero
    if(vecList == NULL){
        printf("Veclist is null");
    }
    int size = adjWgtData(vecList[0],0).to;
    printf("Size is %d\n", size);
    AdjWgt edge;
    AdjWgtVec currentVec;
    for(int i=1; i< size+1; i++){
        currentVec = vecList[i];
        for(int j=0; j< adjWgtSize(currentVec);j++){
            edge = adjWgtData(currentVec,j);
            printf("edge # %d: to: %d, wgt: %lf\n",i,edge.to,edge.wgt);
        }
    }
}
