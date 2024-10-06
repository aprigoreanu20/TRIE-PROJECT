/* PRIGOREANU Alexandra - 314CC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TREE_H
#include "tree.h"
#endif

// initialise queue
Queue* initQueue(Queue *q)
{
    q->first = NULL;
    q->last = NULL;

    return q;
}

// function that checks if the queue is empty
int isEmpty(Queue *q)
{
    if (q->first == NULL && q->last == NULL)
    {
        // the queue is empty if the first and last pointers are both NULL
        return 1;
    }
    return 0;
}

// function for adding a new node in the queue
Queue* enqueue(Node *new_node, Queue *q)
{
    List *new = (List *)malloc(sizeof(List));

    // setarea noului nod
    new->nod = new_node;
    new->next = NULL;

    if (q->first == NULL)
    {
        // when adding the first node in the queue, the first and last
        // pointers of the queue must be set
        q->first = new;
        q->last = new;
    }
    else
    {
        // adding a new node right after the current last node of the queue
        q->last->next = new;
        q->last = new;
    }

    return q;
}

// function for eliminating the first node in the queue
// the function returns the eliminated node
Node* dequeue(Queue *q)
{
    List *temp = q->first;
    Node *temp_node = q->first->nod;
    
    if (q->first == q->last)
    {
        // if the queue only has one node, the first and last pointers must pe
        // set to NULL
        q->first = NULL;
        q->last = NULL;
    }
    else
    {
        // for eliminating the first node, the first pointer 
        // in the queue must be updated
        q->first = q->first->next;
    }
    
    // the node is returned and its memory is freed
    free(temp);
    return temp_node;
}
