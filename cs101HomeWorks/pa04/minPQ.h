//
// Created by Shane on 6/3/17.
//
/* minPQ.h (what is the purpose of this file? Replace this question with your comment.)
 */

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* ***************** Access functions */

/** isEmpty PRECONDITIONS: PQ is a struct of type PQ and successfully initialized by createPQ
 *
 */

int isEmptyPQ(MinPQ pq);

/** getMin :pq is a PQ struct as returned by createPQ and it's arrays are initialized to the correct size
 */
int getMin(MinPQ pq);

/** getStatus PRECONDITIONS: pq is initialized and the id is in range[1, numNodes] where numNodes is the number of vertices
 * that are present in the graph being analyzed of pq
 * POSTCONDITONS: returns the FRINGE/UNSEE/INTREE status of a given id
 */
int getStatus(MinPQ pq, int id);

/** getParent PRECONDITIONS: pq is initialized and the id i in range[1, numNodes] where numNodes is the number of vertices
 * that are present in the graph.
 * POSTCONDITIONS: returns the parent of the given id from the PQ struct
 */
int getParent(MinPQ pq, int id);

/** getPriority :PRECONDITIONS pq is initialized and id is in range[1, numNodes] where numNodes is the number of vertices
 */
double getPriority(MinPQ pq, int id);


/* ***************** Manipulation procedures */

/** delMin PRECONDITIONS: pq has been initialized correctly
 */
void delMin(MinPQ pq);

/** insertPQ PRECONDITIONS:
 * pq: initialized correctly
 * int id:  in range[1, numNodes] where numNodes is the number of vertices
 * double priority: priority is the weight/cost of the edge
 * int par: parent is the parent of the item to be inserted into the PQ
 * POSTCONDITIONS: the vertex represented by the given id is inserted into the priority queue
 * and it's weight is stored in the correct index of the pq struct
 */

void insertPQ(MinPQ pq, int id, double priority, int par);

/** decreaseKey Precondtions: all arguments are not garbage
 * POSTCONDITIONS: decreases the key's priority and allows for the changing of a parent
 * if the given id has a lower weight than the current one in the priority queue
 */
void decreaseKey(MinPQ pq, int id, double priority, int par);


/* ***************** Constructors */

/** createPQ
 * Creates an empty minimum priority queue
 * initializes book keeping arrays after they struct and pointers have been initialized
 * int n: the maximum size of the priority queue, equal to the number of vertices in the graph
 * int status[]: array for tracking UNSEEN, FRINGE, INTREE declarations
 * double priority[]: array for keeping track of the weights/costs of the edges in the pq
 * int parent[]: an array that keeps track of the parent of each node, and can be used to reconstruct the MST/DSSP
 */
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif
