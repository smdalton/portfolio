//
// Created by Shane on 5/6/17.
//

//loadGraphTester function
#include "loadGraph.h"
#include "intVec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PRE: argv[1] contains the filename of input graph or a flag -U
 * POST: intVec structure is returned to caller
 */
IntVec* loadGraph(int argc, char* argv[]){
    //loadGraph will read the file in the folder with specified name


    if(argc > 3 || argc <2){
        printf("\n");
        printf("\nUsage: %s<flag> <input file>\n ", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(argc == 2 && (strcmp(argv[1],"-U")==0)) {
        printf("\n");
        printf("NO INPUT FILE GIVEN\n");
        printf("\nUsage: %s<flag> <input file>\n ", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* inFile=NULL;
    int UflagSet = strcmp(argv[1],"-U");
    if(UflagSet == 0){
        printf("\n-U undirected mode set\n");
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
    //use the zero index of the vecList to hold the size, it will be immune to
    //transpose
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
    //printf("Number of edges is %d",edges);
    //printAdjVerts(vecNodes);
    fclose(inFile);
    return vecNodes;
}

/* PRE: vecList exists, n is an integer
 * POST: returns newVeclist, the transposed version of vecList
 *
 */

IntVec* transposeGraph(IntVec* vecList, int n){
    IntVec* newVecList = calloc(n,(sizeof(IntVec)));
    int numNodes = vecList[0]->data[0];

    //allocate space for the new array of transposed adjacency lists
    for(int i=0;i<numNodes;i++){
        newVecList[i] = intMakeEmptyVec();
    }

    intVecPush(newVecList[0],numNodes);
    //for each node i in vecList we need to look at all of it's connected nodes
    // and for each connected node, in newVeclist[connected node] we need
    //to push i to that node

    for(int i = 1; i <numNodes /*-1?*/; i++){
        //iterate through all of the connections of node = vecList[i]
        //and then push i into each of them individually in the new vecList
        for(int j =0;j<vecList[i]->sz;j++){
            //printf("\n%d\n",vecList[i]->sz);
            //push node #i ---> newVec[oldNode[data i...j]
            //printf("pushing %d into node # %d\n",i,vecList[i]->data[j]);
            intVecPush(newVecList[vecList[i]->data[j]],i);
        }
    }
    return newVecList;
}