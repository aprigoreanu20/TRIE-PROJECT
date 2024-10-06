#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TREE_H
#include "tree.h"
#endif

// function for building a new node in the tree
// (memory allocation + filling in data)
Node* buildNode(char new_ch, Node *new_node)
{
    // 
    int i;
    new_node = (Node *)malloc(sizeof(Node));

    // the character sent as parameter is added in the new node
    new_node->ch = new_ch;

    // the string in the new node is considered empty
    strcpy(new_node->string,"");

    // fill in other data fields in the node
    new_node->level = 0;
    new_node->nr_children = 0;

    // all of the children of the new node are set to NULL
    for (i = 0; i < 27; i++)
    {
        new_node->children[i] = NULL;
    }

    // the function returns the new node
    return new_node;
}

// function for inserting a new node in the tree
Node* insertNode(Node *new_node, Node *root)
{
    // updating the string in the node
    // the new string is formed by adding the character in the new node at the
    //  end of the string of its parent
    int len = strlen(root->string);
    char new_string[30];
    strcpy(new_string, root->string);
    new_string[len] = new_node->ch;
    new_string[len + 1] = '\0';
    strcpy(new_node->string, new_string);

    // calculating the level of the new node based on the level of its parent
    new_node->level = root->level + 1;

    // updating the number of direct descendants of the parent node
    root->nr_children++;

    // inserting the node by linking it to its parent node
    int index = findIndex(new_node->ch);
    root->children[index] = new_node;

    return new_node;
}

// function for initialising the tree
Node* createTree(Node *root)
{
    int i;

    // initialising the tree by creating the root
    strcpy(root->string, "");
    root->ch  = '\0';
    root->level = 0;
    root->nr_children = 0;

    for (i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }
    return root;
}

// function for finding the position of a character in the alphabet
// by convention, '$' has the index of 0
int findIndex(char ch)
{
    if (ch == '$')
        return 0;
    return (ch - 'a' + 1);
}

// function for finding all of the letters that form a string
void alphabet(int alpha[], char text[])
{
    int i, len = strlen(text);
    int index;

    for (i = 0; i < 27; i++)
        alpha[i] = 0;
    
    // the elements of alpha array are either 0 or 1
    // for each letter of the string, the corresponding element in the array
    // are set to 1; all of the other elements in alpha are set to 0
    for (i = 0; i < len; i++)
    {
        index = findIndex(text[i]);
        alpha[index] = 1;
    }
}

// function for adding a word to the tree by doing a level order
// traversal, using a queue
Node* buildTree(char text[], Node *root, Queue *node_queue)
{
    int i, j;
    int alpha[30];
    char ch;
    int index;
    char cpy_text[30];
    const char *pos;
    Node *new_node, *root_node;

    // adding the root to the queue
    node_queue = enqueue(root, node_queue);

    while (isEmpty(node_queue) != 1)
    {
        // visiting each node in the queue, level order
        root_node = dequeue(node_queue);

        // adding nodes in the tree depends on the characters
        // in the string of the parent node
        if (root_node->string[0] == '\0')
        {
            alphabet(alpha, text);
        }
        else
        {
            // checking the characters in the parent node string
            alphabet(alpha, root_node->string);
            alpha[0] = 1;
        }

        for (i = 0; i < 27; i++)
        {
            // checking each character in the word
            if (alpha[i] == 1)
            {
                if (root_node->string[0] == '\0')
                {
                    if (i == 0)
                        ch = '$';
                    else
                        ch = 'a' + i - 1;
                    if (root_node->children[i] == NULL)
                    {
                        // inserting a new node that has the current character
                        // the new node is then added to the queue
                        new_node = buildNode(ch, new_node);
                        new_node = insertNode(new_node, root_node);
                        node_queue = enqueue(new_node, node_queue);
                    }
                    else
                    {
                        // otherwise, the node is added to the queue
                        if (node_queue->last == NULL || node_queue->last->nod
                            != root_node->children[i])
                        {
                            node_queue = enqueue(root_node->children[i], node_queue);
                        }
                    }
                }
                else
                {
                    // if the parent node is not the root, each occurence of
                    // parent node string is searched in the new word
                    strcpy(cpy_text, text);
                    pos = cpy_text;
                    while (pos)
                    {            
                        pos = strstr(pos, root_node->string);

                        if (pos != NULL)
                        {
                            // the next character in the word after each
                            // occurence is added to the tree
                            index = pos - cpy_text + strlen(root_node->string);
                            pos++;
                            ch = text[index];

                            if (ch != '\0')
                            {
                                j = findIndex(ch);
                                if (root_node->children[j] == NULL)
                                {
                                    // creating and inserting a new node to the tree 
                                    new_node = buildNode(ch, new_node);
                                    new_node = insertNode(new_node, root_node);
                                    node_queue = enqueue(new_node, node_queue);
                                }
                                else
                                {
                                    // adding the new node to the queue
                                    if (node_queue->last == NULL || node_queue->last->nod != root_node->children[j])
                                    {
                                        node_queue = enqueue(root_node->children[j], node_queue);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // return the root of the tree
    return root;
}

// helper function for transforming the tree into a compact tree
// the function applies path compression between two nodes
// the compression eliminates redundant nodes by updating the data
// contained by the first node and deleting the seconde node
Node* elimNode(Node* n1, Node *n2)
{
    n1->ch = n2->ch;

    // updating the string in the first node by adding the character
    // in the second string
    int len = strlen(n1->string);
    n1->string[len] = n2->ch;
    n1->string[len + 1] = '\0';

    // the second node is eliminated from the children of the first node
    int index, i;
    index = findIndex(n2->ch);
    n1->children[index] = NULL;

    // the first node takes over the children of the second node
    n1->nr_children = n2->nr_children;
    for (i = 0; i < 27; i++)
    {
        if (n2->children[i] != NULL)
        {
            n2->children[i]->level = n1->level + 1;
            n1->children[i] = n2->children[i];
        }
    }

    // freeing memory allocated for the second node
    free(n2);
    return n1;
}

// recursive function that updates all of the strings in a tree
// used for turning a tree into a compact one
Node* initStrings(Node *root)
{
    // each string contains only the character in the node
    root->string[0] = root->ch;
    root->string[1] = '\0';
    int i;

    for (i = 0; i < 27; i++)
    {
        if (root->children[i] != NULL)
        {
            root->children[i] = initStrings(root->children[i]);
        }
    }
    return root;
}

// function for transforming an atomic tree into a compact tree
Node* buildCompactTree(Node *root)
{
    int i;
    
    // the tree is transformed by doing a recursive depth first search
    // and updating the nodes that have only one child
    if (root->nr_children == 1)
    {
        for (i = 0; i < 27; i++)
        {
            if (root->children[i] != NULL && root->children[i]->ch != '$')
            {
                // applying path compression for nodes with a single descendant
                root = elimNode(root, root->children[i]);
                root = buildCompactTree(root);
                break;
            }
        }
    }

    for (i = 0; i < 27; i++)
    {
        if (root->children[i] != NULL)
        {
            root->children[i] = buildCompactTree(root->children[i]);
        }
    }
    return root;
}

// functia getStats returneaza statistici despre arbore (pentru cerinta 2)
// arborele este parcurs pe nivel
// function for calculating stats for the tree
void getStats(Queue *node_queue, Node *root, int *maxDescent, int *nrLeaves,
                int k, int *nrStrings)
{
    Node *current;
    int i; 

    // the breadth first traversal of the tree is done using a queue
    node_queue = enqueue(root, node_queue);

    *maxDescent = -1;
    *nrLeaves = 0;
    *nrStrings = 0;

    while (isEmpty(node_queue) != 1)
    {
        current = dequeue(node_queue);
        
        if (strlen(current->string) == k + 1 && current->ch == '$')
        {
            // checking if the string in the node has k characters
            (*nrStrings)++;
        }
        
        // computing the number of terminal (leaf) nodes
        // and the maximum number of descendants
        for (i = 0; i < 27; i++)
        {
            if (current->children[i] != NULL)
            {
                // adding the children of the current node to the queue
                node_queue = enqueue(current->children[i], node_queue);
            }
        }
        if (current->nr_children == 0)
        {
            (*nrLeaves)++;
        }
        if (current->nr_children > *maxDescent)
        {
            *maxDescent = current->nr_children;
        }
    }
}

// function that searches for a string among the suffixes in the tree
int findString(Node *root, char str[])
{
    Node *current;
    int i;
    current = root;
    int len = strlen(str), index;

    for (i = 0; i < len; i++)
    {
        index = findIndex(str[i]);
        if (current->children[index] != NULL)
        {
            current = current->children[index];
        }
        else
            return 0;
    }

    if (current->children[0] != NULL)
        return 1;
    return 0;
}

// function for printing the tree (level order)
void printLevel(Queue *node_queue, Node *root, FILE *out)
{
    Node *current;
    int i, lev;

    // traversing the tree using a queue
    node_queue = enqueue(root, node_queue);

    lev = 1;

    while (isEmpty(node_queue) != 1)
    {
        current = dequeue(node_queue);

        if(current->level != lev && current->level !=0)
        {
            lev = current->level;
            fprintf(out, "\n");
        }
        
        if (current->ch != '\0')
            fprintf(out, "%c ", current->ch);

        for (i = 0; i < 27; i++)
        {
            if (current->children[i] != NULL)
            {
                // adding the descendants of the current node to the queue
                node_queue = enqueue(current->children[i], node_queue);
            }
        }
    }
    fprintf(out, "\n");
    fclose(out);
}

// printing the compact tree (level order)
// each string in the tree is printed
void printCompactTree(Queue *node_queue, Node *root, FILE *out)
{
    Node *current;
    int i, lev;

    // traversing the tree using a queue
    node_queue = enqueue(root, node_queue);
    lev = 1;

    while (isEmpty(node_queue) != 1)
    {
        current = dequeue(node_queue);

        if(current->level != lev && current->level !=0)
        {
            lev = current->level;
            fprintf(out, "\n");
        }
        if (current->ch != '\0')
            fprintf(out, "%s ", current->string);
        for (i = 0; i < 27; i++)
        {
            if (current->children[i] != NULL)
            {
                // adding the descendants of the current node to the queue
                node_queue = enqueue(current->children[i], node_queue);
            }
        }
    }
    fprintf(out, "\n");
}

// freeing the memory allocated for the tree
void freeTree(Node *root, Queue *node_queue)
{
    int i;
    Node *current;
    node_queue = enqueue(root, node_queue);

    // traversing the tree and freeing the memory allocated for each node
    while (isEmpty(node_queue) != 1)
    {
        current = dequeue(node_queue);
        for (i = 0; i < 27; i++)
        {
            if (current->children[i] != NULL)
                node_queue = enqueue(current->children[i], node_queue);
        }
        free(current);
    }
}
