//
// Created by Shane on 5/6/17.
//

#ifndef UNTITLED8_LOADGRAPH_H
#define UNTITLED8_LOADGRAPH_H

#include "intVec.h"
/*loadGraph
 * PRE: CORRECT FILE INPUT FROM STDIN
 * POST: RETURNS INTVEC ARRAY LOADED WITH GRAPH STRUCTURE
 */
IntVec* loadGraph(int argc, char* argv[]);

/* transposeGraph
 *  PRE: vecList is an intVec array that contains the data of the inut file
 *  POST: the original intvec has been remapped to it's transpose
 */

IntVec* transposeGraph(IntVec* vecList, int n);

void printAdjMatrix(int **input);

int** makeAdjMatrix(IntVec *nodes);

int** allocateGraph(int n);

int** transpose(int** matrix);

void printLine(int size);


void printAdjVerts(IntVec *nodes);
#endif //UNTITLED8_LOADGRAPH_H
