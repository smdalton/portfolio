written by: Shane Dalton
cs101 UCSC Spring2017 smdalton

“I have read and understood the Academic Misconduct Policy for Undergraduates, the related sections 102.01-102.016 and 105.15 of the UC Santa Cruz Student Policies and Regulations Handbook, and the related sections of the class Syllabus”

-Shane Dalton 5/09/2017
“I wrote this assignment using only permitted sources that do not require citation, according to the syllabus.”


ABOUT graph02.c:

        graph02.c Expands on the features of grap01.c and adds new capability for matrix output. It prints a series of matrix operations on the intVec adjacency list array. 
The program will compile when make is invoked in the current directory in which the source files reside. The expected input is a file with a list of -NODE- -EDGE- format inputs such as: 
1 3
2 4
3 2
etc…


REGARDING THE TRANSPOSE OF THE MATRIX:
The twice transposed matrix is the exact same as the original matrix, this was verified observationally and theoretically based on concepts of matrices.


FROM pa01:
After processing input the program will produce output that, for each node, lists all edges that emanate from that node to other nodes int the format of:
[source node]   [edge1 destination node, edge2 destination node… edgeN destination node].

new features graph02: 

Support for undirected edges:
	 -U flag enables undirected edges for all read adjacency lists


makeAdjMatrix()
	This function will produce an adjacency matrix given an input of intVec adjacency lists.
 
transposeGraph()
	This function when given as its input an intvec array of adjacency lists will produce and output that is the transpose of the list of adjacency lists.


