//
// Created by Shane on 5/13/17.
//
// here is where dfs and dfsTrace will go
#include "intVec.h"
#include <stdlib.h>
#include <stdio.h>
#include "loadGraph.h"


#define white 0
#define gray 1
#define black 2

int time;
//input is List of IntVecs
int* dfsSweep(IntVec* adjVertices, IntVec* finishStack, int* sTime, int* fTime, int* roots);
void dfsTsweep(IntVec* adjTrans, int* color, IntVec* finishStack, int* scc,int* dTime2, int* fTime2, int* roots2);
int dfs(IntVec* adjVertices, int* color, int v, IntVec* fStack,int* sTime, int* fTime);
int dfsT(IntVec* adjTrans,int* color, int v, int leader, int* scc,int* dTime2, int* fTime2);
void printInfoDfs1(int graphSize, int *color, int *dTime, int *fTime, int *dfsRoots, IntVec *fStack);
void printInfoDfs2(int graphSize, int *color, int *dTime2, int *fTime2, int *dfsRoots);
void findSccs(IntVec* graph);

//PRE:all of the arguments of type int* have been initialized and adjTrans is initialized correctly
//POST: the entire adjacency list has been swept
int* dfsSweep(IntVec* adjVertices, IntVec* finishStack, int* sTime, int* fTime, int* roots){
    int size = adjVertices[0]->data[0];
    //init the color array to the size of IntVec
    int*color = calloc(size+1,sizeof(int));
    //white =0, grey = 1, black = 2
    for(int i =1; i <size;i++){
        if(color[i]==white){
            //printf("calling dfs on node %d\n",i);
            roots[i] = -1;
            dfs(adjVertices,color,i,finishStack, sTime, fTime);
        }
    }
    return color;
}

//PRE: Same as dfsweep
//POST: same as dfsweep
void dfsTsweep(IntVec* adjTrans, int* color, IntVec* finishStack, int* scc,int* dTime2, int* fTime2, int* roots2){
    //set color to white
    for(int i = 0; i < adjTrans[0]->data[0];i++){
        color[i] = 0;
    }
    while(intSize(finishStack)){
        int v = intTop(finishStack);
        intVecPop(finishStack);
        if(color[v]==white){//v must be a leader so explore it's dfs tree
            roots2[v] = -1;
            dfsT(adjTrans, color,v,v,scc,dTime2,fTime2);
        }
    }

    return;
}

//PRE: adjVerticies is initialized and all pointers are valid
//POST:dfs will have completed one depth first tree search
int dfs(IntVec* adjVertices, int* color, int v, IntVec* fStack,int* sTime, int* fTime){
    int edgeW;
    IntVec remAdj;
    int ans;
    color[v] = gray;
    sTime[v] = time;
    time++;
    //preorder here:
    //get the adjacency list associated with vertex v
    remAdj = adjVertices[v];
    int listIndex=0;

    while(listIndex<remAdj->sz){
        //get the next destination vertex store it in edgeW
        edgeW = remAdj->data[listIndex];
        if(color[edgeW]==white){
            //starting time update

            //sTime[edgeW] = time;
            //time++;
            dfs(adjVertices,color,edgeW,fStack, sTime, fTime);
        }
        listIndex++;
    }
    fTime[v] = time;
    time++;
    intVecPush(fStack,v);
    color[v] = black;
    return 0;
}

//PRE: same as DFS
//POST: same as DFS
int dfsT(IntVec* adjTrans,int* color, int v, int leader, int* scc,int* dTime2, int* fTime2){
    int edgeW;
    IntVec remAdj;
    int ans;
    color[v] = gray;
    //re-init time;
    dTime2[v] = time;
    time++;
    //pre-order processign here
    scc[v] = leader;
    remAdj = adjTrans[v];
    int listIndex =0;
    while(listIndex < remAdj->sz){
        edgeW = remAdj->data[listIndex];
        if(color[edgeW]==white){
            dfsT(adjTrans,color,edgeW,leader,scc,dTime2,fTime2);
        }
        listIndex++;
    }
    fTime2[v] = time;
    time++;
    color[v] = black;
    return 0;
}

//PRE: all of the arguments have been initialized correctly
//POST:output is printed to the screen
void printInfoDfs1(int graphSize, int *color, int *dTime, int *fTime, int *dfsRoots, IntVec *fStack){
    /*---------PRINT FUNCTIONS HERE---------*/

    printf("%s %6s %6s %6s %9s\n", "vertex", "Color", "dTime", "fTime", "parent");
    printf("==============================================\n");
    for (int i = 1; i < (graphSize); i++) {
        printf("%d",i);
        if(color[i]==0){
            printf("%9s","B");
        }else if(color[i]==1){
            printf("%9s","G");
        }else if(color[i]==2){
            printf("%9s","B");
        }
        printf("%6d %6d %9d\n", dTime[i], fTime[i], dfsRoots[i]);
    }printf("\n");
    //for dfsPhase2
    if(fStack!=NULL) {
        int j = 1;
        printf("FSTK: ");
        //print the vec stack in reverse order to print out the data
        for (int i = 0; i < intSize(fStack); i++) {
            printf("%d ", intData(fStack, i));
        }printf("\n\n");
    }
}

//PRE: same as printInfoDfs1
//POST: same as printInfoDfs1
void printInfoDfs2(int graphSize, int *color, int *dTime2, int *fTime2, int *dfsRoots) {
    printf("%s %6s %6s %6s %12s\n", "vertex", "Color", "dTime", "fTime", "dfsLeader");
    printf("==============================================\n");
    for (int i = 1; i < (graphSize); i++) {
        printf("%d",i);
        if(color[i]==0){
            printf("%9s","B");
        }else if(color[i]==1){
            printf("%9s","G");
        }else if(color[i]==2){
            printf("%9s","B");
        }
        printf("%6d %6d %9d\n", dTime2[i], fTime2[i], dfsRoots[i]);
    }printf("\n");

}

//PRE: graph has been loaded correctly and the size of the graph is stored in element 0 of graph vec
//POST: scc's of the graph have been found successfully
void findSccs(IntVec* graph) {
    time = 1;
    int graphSize = graph[0]->data[0];
    int* dTime = calloc(graphSize + 1, sizeof(int));
    int* fTime = calloc(graphSize + 1, sizeof(int));
    int* dTime2 = calloc(graphSize + 1, sizeof(int));
    int* fTime2 = calloc(graphSize + 1, sizeof(int));
    int* dfsRoots = calloc(graphSize + 1, sizeof(int));
    int* dfsRoots2 = calloc(graphSize + 1, sizeof(int));
    int* scc = calloc(graphSize + 1, sizeof(int));
    IntVec* fStack = intMakeEmptyVec();
    int* color;
    //init dfs roots
    for (int i = 0; i < graphSize + 1; i++) {
        dfsRoots[i] = 1;
    }
    IntVec* graphT = transposeGraph(graph, graphSize);
    if(graphT == NULL){
        printf("null");
    }
    //get the color array from dfs sweep
    color = dfsSweep(graph, fStack, dTime, fTime, dfsRoots);
    //print the info for the first dfs
    printInfoDfs1(graphSize, color, dTime, fTime, dfsRoots, fStack);
    //reset time for 2nd round
    time =1;

    dfsTsweep(graphT,color,fStack,scc,dTime2,fTime2,dfsRoots2);
    printInfoDfs2(graphSize,color, dTime2, fTime2, scc);
}
