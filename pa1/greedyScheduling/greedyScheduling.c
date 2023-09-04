#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct node {
    int start; // The start of the job, this is the index by which we will sort
    int end; 
    char job; // The letter name of the job
    struct node* next;
};

struct node* sorted_list_of_jobs = NULL;
struct node* answer = NULL;

void sorted_insert (
    unsigned int start,
    unsigned int end,
    char job
) {

    if(start == 0)
    {
        return; 
    }
    
    // Allocate node
    // ptr to struct node type called newNode and for that newNode we will malloc some new space and create a ptr for it 
    // malloc returns ptr that has no types aka generic ptr 
    struct node* new_node = (struct node*) malloc (sizeof(struct node));
    // (*new_node).time = time;
    new_node->start = start;
    new_node->end = end; 
    // (*new_node).job = job;
    new_node->job = job;

    // Special case for empty list or if new node should be at front
    if ( sorted_list_of_jobs == NULL || start < sorted_list_of_jobs->start ) {

        new_node->next = sorted_list_of_jobs;
        sorted_list_of_jobs = new_node;

    } else {

        struct node* current_node = sorted_list_of_jobs;

        // Locate the node before the point of insertion
        // Compare values of time
        while ( current_node->next!=NULL && current_node->next->start <= start ) {
            current_node = current_node->next;
        }

        new_node->next = current_node->next;
        current_node->next = new_node;

    }
}

void change_array (
    unsigned int start,
    unsigned int end,
    char job
) {
    struct node* neww_node = (struct node*) malloc (sizeof(struct node));
    // (*new_node).start = start;
    neww_node->start = start;
    neww_node->end = end; 
    // (*new_node).job = job;
    neww_node->job = job;

    // Special case for empty list or if new node should be at front
    if ( answer == NULL || start < answer->start ) {
        //printf("special case accessed"); 
        //printf("Start: %d\n", start); 
        //printf("End: %d\n",end);
        neww_node->next = answer;
        answer = neww_node;

    } else {

        struct node* currentt_node = answer;

        // Locate the node before the point of insertion
        // Compare values of start
        
        //printf("\n");
        if(start == currentt_node->start || start < currentt_node->end)
        {
            //printf("New node start: %d\n",start);
            //printf("New node end: %d\n",end);
            //printf("Current node start: %d\n",currentt_node->start); 
            //printf("Current node end: %d\n",currentt_node->end); 
            if(end<currentt_node->end)
            {
                //printf("first if printed\n"); 
                currentt_node->job = job;
                currentt_node->start = start;  
                currentt_node->end = end; 
            }

            if(start == currentt_node->start && end == currentt_node->end)
            {
                //printf("second if accessed\n"); 
                currentt_node->job = job; 
            }
            free(neww_node);
            return; 
        }

        if(start == currentt_node->start && end != currentt_node->end)
        {
            if(end>currentt_node->end)
            {
                currentt_node->job = job; 
                currentt_node->end = end; 
                free(neww_node);
                return;
            }
            else
            {
                free(neww_node);
                return; 
            }
        }

        while ( currentt_node->next!=NULL && currentt_node->next->start <= start) {
            
            currentt_node = currentt_node->next;

        }

        if(start <= currentt_node->end)
        {
            if(end<currentt_node->end)
            {
                currentt_node->job = job; 
                currentt_node->start = start; 
                currentt_node->end = end; 
                free(neww_node);
                return; 
            }

            else if(start == currentt_node->start && end == currentt_node->end)
            {
                currentt_node->job = job;
                free(neww_node); 
                return; 
            }

            else
            {
                free(neww_node);
                return; 
            }
        }

        if(end < currentt_node->end)
        {
            currentt_node->job = job; 
            currentt_node->start = start; 
            currentt_node->end = end; 
            free(neww_node); 
            return; 
        }


        neww_node->next = currentt_node->next;
        currentt_node->next = neww_node;
        
    }

}
// Driver program to test above functions
int main(int argc, char* argv[])
{
    // First peek at how many jobs and timeslots there are
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of timeslots
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of timeslots failed");
        exit(EXIT_FAILURE);
    }
    // int timeslots = atoi(buf) // unused metadata

    // Now read the rest of the file
    for ( int line=0; line<jobcount; line++ ) {

        if (!fgets(buf, 256, fp)) {
            perror("reading a line for a job failed");
            exit(EXIT_FAILURE);
        }

        char job;
        unsigned int start;
        unsigned int end;
        if (!sscanf(buf, "%c %d %d", &job, &start, &end)) {
            perror("parsing a line for a job failed");
            exit(EXIT_FAILURE);
        }

        // add job and start to sorted linked list
        sorted_insert ( start, end, job );

    }

    fclose(fp);

    struct node* current_node = sorted_list_of_jobs;

    while (current_node!=NULL) {
        struct node* temp = current_node;
        change_array(temp->start, temp->end, temp->job); 
        current_node = temp->next;
        free(temp);
    }

    struct node* current_newnode = answer;

    while (current_newnode!=NULL) {
        struct node* tempp = current_newnode;
        printf( "%c\n", tempp->job );
        current_newnode = tempp->next;
        free(tempp);
    }

    exit(EXIT_SUCCESS);
}

