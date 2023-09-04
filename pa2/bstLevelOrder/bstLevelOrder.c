#include <stdlib.h>
#include <stdio.h>

// A program to perform a LEVEL ORDER (BREADTH-FIRST) TRAVERSAL of a binary search tree

// BINARY SEARCH TREE

typedef struct BSTNode BSTNode;
struct BSTNode {
    int key;
    struct BSTNode* l_child; // nodes with smaller key will be in left subtree
    struct BSTNode* r_child; // nodes with larger key will be in right subtree
};

// Add new data to the BST using recursion
/* ... */
struct BSTNode* insert ( struct BSTNode* root, int key ) {

    // Base case: If the BSTNode here doesn't yet exist
    if (root==NULL) {
        root = malloc(sizeof(BSTNode));
        root->l_child = NULL;
        root->r_child = NULL;
        root->key = key;
    }

    // If the BSTNode already exists, then insert key in correct subtree
    if ( key<root->key ) {
        root->l_child = insert( root->l_child, key );
    } else if ( key==root->key ) {
        // duplicates are ignored
    } else { // key>root->key
        root->r_child = insert( root->r_child, key );
    }
    return root;
}

// Delete the BST using recursion
/* ... */
void delete_bst ( BSTNode* root ) {
    if ( root->r_child!=NULL ) {
        delete_bst (root->r_child);
    }
    if ( root->l_child!=NULL ) {
        delete_bst (root->l_child);
    }
    free (root);
}


// LINKED LIST IMPLEMENTATION OF QUEUE

// queue needed for level order traversal
/* ... */
typedef struct QueueNode QueueNode;
struct QueueNode {
    unsigned int data;
    struct QueueNode* next; // pointer to next node in linked list
};

struct Queue {
    struct QueueNode* front; // front (head) of the queue
    struct QueueNode* back; // back (tail) of the queue
};

typedef struct Queue Queue;

// Append a new QueueNode to the back of the Queue
void enqueue ( Queue* queue, BSTNode* bst) {
  /* ... */
    QueueNode* queueNode = malloc(sizeof(QueueNode)); 
    queueNode -> data = bst->key;
    queueNode -> next = NULL; // At back of the queue, there is no next node.

    if (queue->back==NULL) { // If the Queue is currently empty
        queue->front = queueNode;
        queue->back = queueNode;
    } else {
        queue->back->next = queueNode;
        queue->back = queueNode;
    }

    return;
}

unsigned int dequeue ( Queue* queue ) {

    if (queue->front==NULL) { // If the Queue is currently empty
        return '\0';
    } else {

        // The QueueNode at front of the queue to be removed
        QueueNode* temp = queue->front;
        unsigned int data = temp->data;

        queue->front = temp->next;
        if (queue->back==temp) { // If the Queue will become empty
            queue->back = NULL;
        }

        free(temp);
        return data;
    }
}

int getHeight(BSTNode* root)
{
    if(root == NULL)
    {
        return 0; 
    }
    else{
        int left = getHeight(root->l_child);
        int right = getHeight(root->r_child); 

        if(left>right)
        {
            return left +1; 
        } 
        else{
            return right+1; 
        }
    }
}
int count = 0; 
void enqueueLevel(BSTNode* root, int level,Queue* queue)
{
    if(!root)
    {
        return; 
    }
    if(level == 0)
    {
        count++; 
        enqueue(queue, root); 
    }

    else{
        enqueueLevel(root->l_child, level - 1, queue); 
        enqueueLevel(root->r_child, level - 1, queue); 
    }

}
int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    BSTNode* root = NULL;
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {
        root = insert (root, key);
    }
    fclose(fp);

    // USE A QUEUE TO PERFORM LEVEL ORDER TRAVERSAL
    Queue queue = { .front=NULL, .back=NULL };
    BSTNode* currBSTNode = root;
    
    int height = getHeight(root);
    for(int i = 0; i<height; i++)
    {
        enqueueLevel(currBSTNode, i, &queue); 
    }

    for(int i = 1; i<=count; i++)
    {
        printf("%d ", dequeue(&queue)); 
    }

    delete_bst(root);
    return EXIT_SUCCESS;
}
