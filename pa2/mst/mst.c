#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to find the minimum spanning tree of a weighted undirected graph using Prim's algorithm

bool areAllVerticesAdded(bool* addedToMST,int graphNodeCount)
{
    for (size_t i=1; i<graphNodeCount; i++) 
    {
        if(addedToMST[i]==false)
        {
            return false; 
        }
    }
    return true; 
}

int main ( int argc, char* argv[] ) {

     
 
    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    // AdjacencyListNode* adjacencyList;
    /* ... */
    AdjacencyListNode* adjacencyList;
    int graphNodeCount = adjMatrixToList(argv[1],&adjacencyList);
 
    // An array that keeps track of who is the parent node of each graph node we visit
    // In Prim's algorithm, this parents array keeps track of what is the edge that connects a node to the MST.
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) 
    {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited; i.e., node not yet connected to MST.
    }

    graphNode_t* pq = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) 
    {
        pq[i] = -1; // -1 indicates that a nodes is not yet visited; i.e., node not yet connected to MST.
    }

    bool* addedToMST = calloc ( graphNodeCount, sizeof(bool) );
    addedToMST[0] = true; 
 
    parents[0] = 0;
 
    while(!(areAllVerticesAdded(addedToMST,graphNodeCount)))
    {
        double minWeight = DBL_MAX; // If we find an edge with weight less than this minWeight, and edge connects a new node to MST, then mark this as the minimum weight to beat.
        graphNode_t minDest = -1;
        graphNode_t minSource = -1; 

        for (size_t i=0; i<graphNodeCount; i++)
        {
            if(parents[i] != -1)
            {
                AdjacencyListNode* dest = adjacencyList[i].next;

                while(dest) { 
                    if(pq[dest->graphNode] == -1 && addedToMST[dest->graphNode] == false)
                    {
                        pq[dest->graphNode] = dest->graphNode; 
                    }
            
                    if(dest->weight < minWeight && i!=dest->graphNode && addedToMST[dest->graphNode] == false)
                    {
                        
                        minWeight = dest->weight;
                        minDest = dest->graphNode;
                        minSource = i; 
                    }
           
                    dest = dest->next;
           
                }


            }
        }
        if(addedToMST[minDest] ==false)
        {
            parents[minDest] = minSource; 
            addedToMST[minDest] = true;
            addedToMST[minSource] = true; 
        }

        for (size_t i=0; i<graphNodeCount; i++) 
        {
            pq[i] = -1; //empty priority queue 
        }
        
    }


    // Using the fully populated parents array, print the edges in the MST.
    /* ... */
    for (size_t i=1; i<graphNodeCount; i++) {
        printf("%ld %ld\n",i,parents[i]); 
    }

    free (parents);
    free(pq); 
    free(addedToMST); 
    freeAdjList ( graphNodeCount, adjacencyList );

    return EXIT_SUCCESS;
}
