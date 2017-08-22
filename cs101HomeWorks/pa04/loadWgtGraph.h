//
// Created by Shane on 6/3/17.
//

#ifndef PA04_LOADGRAPH_H
#define PA04_LOADGRAPH_H

#include "adjWgtVec.h"
/*loadGraph
 * PRE: CORRECT FILE INPUT FROM STDIN
 * POST: RETURNS INTVEC ARRAY LOADED WITH GRAPH STRUCTURE
 */

//AdjWgtVec* is a list of adjWgtVecNodes

AdjWgtVec* loadGraph(int argc, char* argv[],char task);

/* transposeGraph
 *  PRE: vecList is an intVec array that contains the data of the inut file
 *  POST: the original intvec has been remapped to it's transpose
 */
void printAdjList(AdjWgtVec* vecList);
void printLine(int size);



#endif //PA04_LOADGRAPH_H
