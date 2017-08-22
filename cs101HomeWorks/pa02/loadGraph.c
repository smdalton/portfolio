//
// Created by Shane on 5/6/17.
//

//loadGraphTester function
#include "loadGraph.h"
#include "intVec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



IntVec* loadGraph(int argc, char* argv[]){
    //loadGraph will read the file in the folder with specified name

    /*
    if( !(argc> 2) ){
        printf("\n");
        printf("\nUsage: %s <input file> <flag>\n ", argv[0]);
        exit(EXIT_FAILURE);
    }
    */
    FILE* inFile=NULL;
    int UflagSet = strcmp(argv[1],"-U");
    if(UflagSet == 0){
        printf("-U undirected mode set\n");
        inFile = fopen(argv[2],"r");

    }else{
        printf("Undirected mode not set\n");
        inFile = fopen(argv[1],"r");
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

    //IntVec vecNodes[numNodes];
    IntVec* vecNodes = calloc(numNodes,(sizeof(IntVec)));
    for(int i=0; i<numNodes;i++){
        vecNodes[i] = intMakeEmptyVec();
    }

    intVecPush(vecNodes[0],numNodes);
    printf("Number of nodes is %d\n",vecNodes[0]->data[0]-1);
    //int** graph = allocateGraph(numNodes);
    //return the number of nodes in the first element of the 2-d array
    //graph[0][0] = numNodes;


    while(fgets(line,150,inFile)!=NULL){

        sscanf(line,"%d %d %f",&first,&second,&weight);
        if(UflagSet==0){
            //push two edges, one for each direction if -U is set
            intVecPush(vecNodes[first],second);
            intVecPush(vecNodes[second],first);
        }else{
            intVecPush(vecNodes[first],second);
        }
        edges++;
    }
    printf("Number of edges is %d",edges);
    //printAdjVerts(vecNodes);
    fclose(inFile);
    return vecNodes;
}
