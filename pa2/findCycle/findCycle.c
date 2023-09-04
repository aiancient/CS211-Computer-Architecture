#include "../graphutils.h"
 
// A program to find a cycle in a directed graph
 
// You may use DFS or BFS as needed
/* ... */
struct element {
   int number;
   struct element* next;
};
 
// Append the new element to the start of the stack
// show what happens on the stack and on the heap
struct element* root = NULL;
 
void push (
   int number
) {
   struct element* newElement = malloc(sizeof(struct element));
   newElement->number = number;
   newElement->next = root;
   root = newElement;
   return;
}
 
// Remove element from the top of the stack
int pop () {
   if(root!=NULL)
   {
       struct element* temp = root;
       int number = temp->number;
       root = temp->next;
       free(temp);
       return number;
   }
   else{
       return -300;
   }
}
 
int peek() {
   if(root!=NULL)
   {
       int num = root->number;
       return num;
   }
 
   else{
       return -200;
   }
}
 
bool didYouPop = false;
int count = 0; 
void dfs(int start, bool* visited,AdjacencyListNode* adjacencyList,int* changeCycle)
{
   visited[start] = true;
   push(start);
   AdjacencyListNode* dest = adjacencyList[start].next;
 
   while(dest)
   {
       if(visited[dest->graphNode] == false)
       {
           dfs(dest->graphNode,visited,adjacencyList,changeCycle);
       }
 
       if(visited[dest->graphNode] == true && didYouPop == false)
       {
           changeCycle[count] = dest->graphNode; 
           do {
               count++; 
               changeCycle[count] = pop(); 
           } while(peek() != dest->graphNode && peek() != -200);
           didYouPop = true;
       }
 
       dest = dest->next;
   }
  
 
   visited[start] = false;
   pop();
}
 
int main ( int argc, char* argv[] ) {
 
   // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
   AdjacencyListNode* adjacencyList;
   /* ... */
   int graphNodeCount = adjMatrixToList(argv[1],&adjacencyList);
 
   bool* visited = calloc ( graphNodeCount, sizeof(bool) );
   int* changeCycle = calloc ( graphNodeCount, sizeof(int) );
   //bool isCyclic = false;
   for (unsigned source=0; source<graphNodeCount; source++) {
       /* ... */
       dfs(source,visited,adjacencyList,changeCycle);
 
       if(didYouPop)
       {
           for(int a = count; a>=0; a--)
           {
               printf("%d ",changeCycle[a]); 
           }
           break;
       }
 
       while(pop()!=-300)
       {
           pop();
       }
   }

   free(visited);
   free(changeCycle);
   freeAdjList ( graphNodeCount, adjacencyList );
   return EXIT_SUCCESS;
}
 
