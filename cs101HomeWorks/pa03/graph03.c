//
// Created by Shane on 5/11/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "loadGraph.h"
#include "scc03.h"



int main(int argc, char* argv[]) {
    int** tempMatrix;
    IntVec* tempVec = loadGraph(argc,argv);
    printAdjVerts(tempVec);
    printAdjMatrix(makeAdjMatrix(tempVec));
    printf("\n");
    findSccs(tempVec);

    exit(0);
}

