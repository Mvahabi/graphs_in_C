/*
Mahyar Mike Vahabi
mvahabi
Winter 22 - CSE101 - pa2
pa2 - FindPath.c - File Input/Output
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <ctype.h>
#include "Graph.h"

// Citation: Professor Tantalo's prompt for FileI/O

int main(int argc, char * argv[]) {

    // needed variables
    int n, u, v; // n = #vertices; u, v = vertex of two edges
    FILE *in, *out;  // input output files
    Graph G;
    List L;

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    if (in==NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out==NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // scan the very first digit which gives us the # vertex
    fscanf(in, " %d", &n);

    // create the graph
    G = newGraph(n);

    // initialize to a non 0 value
    u = v = 1;

    // scan till u and v are 0 and add each edges
    while (u != 0 || v != 0) {
        fscanf(in, " %d", &u);
        fscanf(in, " %d", &v);
        if (u == 0 && v == 0) {
            break;
        }
        addEdge(G, u, v);
   }
   
    // print graph and make a new list for the path findings.
    printGraph(out, G);
    L = newList();

    // reset the vertices of the edges
    u = v = 1;

    // continue scanning for the rest of the file
    // while both vertices are not 0, perform BFS, 
    // find distance from one to another and shortest path
    while (u != 0 || v != 0) {
        fscanf(in, " %d", &u);
        fscanf(in, " %d", &v);

        if (u == 0 && v == 0) {
            break;
        }

        BFS(G, u);
        getPath(L, G, v);
        
        if (length(L) == 0 || getDist(G, v) < 0) {
            fprintf(out, "\nThe distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u, v);
        }
        else {
            fprintf(out, "\nThe distance from %d to %d is %d\n", u, v, getDist(G, v));
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, L);
        }
        clear(L);
    }

    // free all graphs, lists, and close all files
    freeGraph(&G);
    freeList(&L);
    fclose(in);
    fclose(out); 

    return 0;
}
