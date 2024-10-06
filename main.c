#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TREE_H
#include "tree.h"
#endif

int main(int argc, char **argv)
{
    Node *root = (Node *)malloc(sizeof(Node));
    root = createTree(root);
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q = initQueue(q);
    int k, maxDescent, nrLeaves, nrStrings;
    int N, M, i, len;
    char text[30], suf[30];
    FILE *in, *out;

    if (strcmp(argv[1], "-1") == 0)
    {
        // create the tree using the words from the input file
        in = fopen(argv[2], "r");
        out = fopen(argv[3], "w");

        // read data from input file
        fscanf(in, "%d", &N);
        for (i = 0; i < N; i++)
        {
            fscanf(in, "%s", text);
            len = strlen(text);
            text[len] = '$';
            text[len + 1] = '\0';
            // every word in the input file is added to the tree
            root = buildTree(text, root, q);
        }

        // print the tree (level order) in the output file
        printLevel(q, root, out);

        fclose(in);
    }
    if (strcmp(argv[1], "-2") == 0)
    {
        // create a tree based on the words from the input file
        // and determine some statistics
        in = fopen(argv[3], "r");
        out = fopen(argv[4], "w");

        // build the tree based on the words in the input file
        fscanf(in, "%d", &N);
        for (i = 0; i < N; i++)
        {
            fscanf(in, "%s", text);
            len = strlen(text);
            text[len] = '$';
            text[len + 1] = '\0';
            // every word in the input file is added to the tree
            root = buildTree(text, root, q);
        }
        k = atoi(argv[2]);

        // process the tree and calculate some statistics
        getStats(q, root, &maxDescent, &nrLeaves, k, &nrStrings);

        // print the information in the output file
        fprintf(out, "Number of leaf nodes: %d\n", nrLeaves);
        fprintf(out, "Number of suffixes of length %d: %d\n", k, nrStrings);
        fprintf(out, "Max number of children: %d\n", maxDescent);

        fclose(in);
        fclose(out);
    }
    if (strcmp(argv[1], "-3") == 0)
    {
        // build the tree based on the words in the input file
        // and determine whether the suffixes in the input file
        // can be found in the tree
        in = fopen(argv[2], "r");
        out = fopen(argv[3], "w");

        // build the tree based on the words in the input file
        fscanf(in, "%d%d", &N, &M);
        for (i = 0; i < N; i++)
        {
            fscanf(in, "%s", text);
            len = strlen(text);
            text[len] = '$';
            text[len + 1] = '\0';
            // every word in the input file is added to the tree
            root = buildTree(text, root, q);
        }
        
        for (i = 0; i < M; i++)
        {
            // each suffix read from the input file is searched in the tree
            fscanf(in, "%s", suf);
            fprintf(out, "%d\n", findString(root, suf));
        }
        fclose(in);
        fclose(out);
    }
    if (strcmp(argv[1], "-4") == 0)
    {
        // build a compact tree
        in = fopen(argv[2], "r");
        out = fopen(argv[3], "w");

        // build the tree based on the words in the input file
        fscanf(in, "%d", &N);
        for (i = 0; i < N; i++)
        {
            fscanf(in, "%s", text);
            len = strlen(text);
            text[len] = '$';
            text[len + 1] = '\0';
            // each word read from the input file is added to the tree
            // initially, the tree built is not compact
            root = buildTree(text, root, q);
        }

        // transforme the tree into a compact one
        root = initStrings(root);
        root = buildCompactTree(root);
        
        // display the tree in the output file
        printCompactTree(q, root, out);

        fclose(in);
        fclose(out);
    }

    // free memory for the tree and for the queue
    freeTree(root, q);
    free(q);
    return 0;
}