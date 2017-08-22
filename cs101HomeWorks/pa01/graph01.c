//
// Created by Shane on 4/15/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
//#include "intVec.h"

int main() {
    //open file pointers
    FILE* inFile=NULL;
    FILE* outFile=NULL;
    //data is an array for the edge and its connected node
    int numNodes=0;
    int data[2];
    char *first;
    char *second;
    char *useless;
    //line is a buffer input for the the reading of the lines in the file
    char line[25];
    //instantiate two file pointers
    inFile = fopen("input.txt","r");
    outFile = fopen("output.txt","w");
    if(inFile == NULL || outFile == NULL){
        exit(1);
    }

    char buf[300];

    //don't use fscanf for reading lines in a file it is bad bad
    numNodes = strtol(fgets(line,25,inFile),useless,10);

    //strtol(--CHAR POINTER TO A STRING--,--pointer to remaing string after tokenization,--BASE OF NUMBER SYSTEM--);

    printf("The number of Nodes is: %d\n",numNodes);
    while(fgets(line,25,inFile)!=NULL){
        //printf("word read in is: %s\n",line);
        //fprintf(outFile, "%s",buf);
        first =  strtok(line," ");
        second = strtok(NULL," ");
        data[0] = strtol(first,useless,10);
        data[1] = strtol(second,useless,10);
        //data[1] = strtol(second,useless,10);

        //seperate the ints from the doubles in the string
        printf("First is: %d Second is: %d\n",data[0],data[1]);
        printf("First + second is %d\n",data[0]+data[1]);


    }
    fclose(inFile);
    fclose(outFile);

    //

    return 0;
}