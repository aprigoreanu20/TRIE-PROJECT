#ifndef TREE_H
#define TREE_H

// structure for implementing the suffix tree
typedef struct node
{
    // string represents the suffix formed from the root to the node
    char string[30];

    // the character in the node
    char ch;

    // the level of the node
    int level;

    // the number of direct descendants of the node
    int nr_children;

    // pointers to the children of the current node
    struct node *children[27];
}Node;

// structure for the elements of a queue
typedef struct list
{
    Node *nod;
    struct list *next;
}List;

// structure for the queue
typedef struct queue
{
    List *first, *last;
}Queue;

// functions used for adding nodes to the tree
Node* buildNode(char, Node *);
Node* insertNode(Node *, Node *);

// functions for building the tree
Node* createTree(Node *);
Node* buildTree(char *, Node *, Queue *);
Node* buildCompactTree(Node *);

Node* elimNode(Node *, Node *);
Node* initStrings(Node *);
int findIndex(char);
void alphabet(int *, char *);

// functions for processing data in the tree
void getStats(Queue *, Node *, int *, int *,int, int *);
int findString(Node *, char *);

// functions for displaying the tree
void printLevel(Queue *, Node *, FILE *);
void printCompactTree(Queue *, Node *, FILE *);

// function for freeing memory
void freeTree(Node *, Queue *);

// functions for queue implementation
Queue* initQueue(Queue*);
int isEmpty(Queue*);

Queue* enqueue(Node*, Queue*);
Node* dequeue(Queue*);

#endif