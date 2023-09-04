#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix

int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    int size = adjMatrixToList(argv[1],&adjacencyList); 
    /* ... */

    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    /* ... */
    //bool isFirst = true; 
    for (size_t source=0; source<size; source++) {

        AdjacencyListNode* dest = adjacencyList[source].next;

        // list iterator
        while (dest) {
            //AdjacencyListNode* temp = dest;
             // iterator moves to next
            if(source == 0)
            {
                printf("%ld %ld\n", source, dest->graphNode); 
            }

            if(source != 0 && source < dest->graphNode)
            {
                printf("%ld %ld\n", source, dest->graphNode);
            }
            
            dest = dest->next;
        }

    }

    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    /* ... */
    freeAdjList(size, adjacencyList); 

    return EXIT_SUCCESS;
}
