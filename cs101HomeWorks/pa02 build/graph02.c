#include <stdio.h>
#include <stdlib.h>
#include "loadGraph.h"

//PRE: 2-D array is initialized, array[0][0]= size of array
//POST: none
void printAdjMatrix(int **input){
    int n = (input[0][0]-1);
    if(n>20){
        printf("Not printing: n>20\n");
        return;
    }
    printf("");
    n++;
    printf("    ");
    for(int i = 1;i<n;i++){
        printf("%3d",(i));
    }
    printf("\n     ");
    for(int i = 0;i<(3*n)-3;i++){
        printf("-");
    }
    printf("\n");

    for(int i=1;i<n;i++){
        //below is row label print
        printf("%3d:",i);
        for(int j=1;j<n;j++){
            printf("%3d",input[i][j]);
        }
        printf("\n");
    }
}
/*
 *  PRE: n is an integer >0
 *  POST: adjMatrix is an empty 2d array of size (n+1)x(n+1)
 *  array[0][0] is SET TO MATRIX SIZE +1
*/
int** allocateGraph(int n){
    n++;
    int** adjMatrix = calloc(n,sizeof(int*));
    for(int i =0 ; i< n;i++){
        adjMatrix[i] = calloc(n,sizeof(int));
    }
    adjMatrix[0][0]=(n-1);
    return adjMatrix;
}

/*
 * PRE: matrix is initialized and contains data from adjList
 * POST: matrix is transposed and returned to caller
*/

int** transpose(int** matrix){
    int size = matrix[0][0];
    int** newMatrix = allocateGraph(size);
    for(int i=0;i<size; i++){
        for(int j=0;j<size;j++){
            newMatrix[i][j]=matrix[j][i];
        }
    }
    return newMatrix;
}
/*
*PRE:*nodes is  InteVec array and initialized from loadGraph.c
*POST: contents are printed
*/
void printAdjVerts(IntVec *nodes){
    //store the number of nodes in the first element of the IntVec array

    int numNodes = nodes[0]->data[0];
    //numNodes = 3;
    //printf("%d",numNodes);
    if(numNodes >20){
        printf("Not Printing reason: input is larger than 20\n");
        return;
    }
    for(int i = 1; i<numNodes;i++) {
        printf("%d\t", i);

        if(nodes[i]->sz == 0){
            printf("null\n");
            continue;
        }

        printf("[");
        for(int j=0;j<nodes[i]->sz;j++){

            if(j!= nodes[i]->sz-1){
                printf("%d,",nodes[i]->data[j]);
            }else{
                printf("%d",nodes[i]->data[j]);
            }
        }
        printf("]\n");
    }
    printf("\n");
}
void printLine(int size){
    for(int i=0; i<size;i++){
        printf("==");
    }
    printf("\n");
}

int** makeAdjMatrix(IntVec *nodes){
    int size = nodes[0]->data[0];
    int** matrix = allocateGraph(nodes[0]->data[0]);
    matrix[0][0]=size;

    //iterate over each vecnode in the array of vecnodes
    for(int i = 1; i<size;i++){
        //iterate over each item in the array of the above vecnode
        for(int j =0; j<nodes[i]->sz;j++){
            matrix[i][nodes[i]->data[j]]++;
        }
    }
    return matrix;
}

int main(int argc, char* argv[]) {
    int** tempMatrix;
    int graphSize=0;
    IntVec* intVecGraph;
    IntVec* tempVec;
    //call pa01 routine stored in loadGraph
    //intVecGraph holds the adjList

    //******BASIC INPUT VERIFICATION******//
    printLine(15);
    //read input
    intVecGraph = loadGraph(argc,argv);
    //print input
    printf("\nPRINTING ADJACENCY LIST:\n");
    printAdjVerts(intVecGraph);
    //makeadjMatrix
    tempMatrix = makeAdjMatrix(intVecGraph);
    //print adjMatrix
    printf("\nPRINTING ADJACENCY MATRIX:\n");
    printAdjMatrix(tempMatrix);
    printLine(15);
    //******FIRST TRANPOSITION******//


    //transposeGraph on original intVec
    tempVec = transposeGraph(intVecGraph,intVecGraph[0]->data[0]);
    //print the transposed intVec
    printf("\nPRINTING TRANSPOSED ADJACENCY LIST:\n");
    printAdjVerts(tempVec);
    //make adjacency matrix from transposed list
    tempMatrix = makeAdjMatrix(tempVec);
    //print transposed matrix
    printf("\nPRINTING TRANSPOSED ADJACENCY MATRIX:\n");
    printAdjMatrix(tempMatrix);
    printLine(15);


    //******SECOND TRANSPOSITION******//

    //transpose the transposed intVec
    tempVec = transposeGraph(tempVec, tempVec[0]->data[0]);
    //print the twice transposed  vecList
    printf("\nPRINTING TWICE TRANSPOSED ADJACENCY LIST:\n");
    printAdjVerts(tempVec);
    //make the adjmatrix from the twice transposed intVec
    tempMatrix = makeAdjMatrix(tempVec);
    //print the adjMatrix
    printf("\nPRINTING TWICE TRANSPOSED ADJACENCY MATRIX:\n");
    printAdjMatrix(tempMatrix);
    printLine(15);
    exit(0);




}