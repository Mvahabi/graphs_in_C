/*
Mahyar Mike Vahabi
mvahabi
Winter 22 - CSE101 - pa3
pa2 - FindComponent.c - File Input/Output
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
    Graph G, Trans;
    List Stack = newList();

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

    // scan till u and v are 0 and add each Arcs
    while (u != 0 || v != 0) {
        fscanf(in, " %d", &u);
        fscanf(in, " %d", &v);
        if (u == 0 && v == 0) {
            break;
        }
        addArc(G, u, v);
    }
   
    // print graph and make a new list for the path findings.
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // append adj verticies in stack
    for(int i = 1; i < getOrder(G) + 1; i++){
        append(Stack, i);
    }

    // call dfs
    DFS(G, Stack);
    fprintf(out, "\n");

    // call the transpose of dfs
    Trans = transpose(G);
    //clear(Stack);
    DFS(Trans, Stack);

    int i = 0;
    moveFront(Stack);
    while(index(Stack) != -1) {
	if(getParent(Trans, get(Stack)) == NIL) {
	    i++;
        }
	moveNext(Stack);
    }

    fprintf(out, "\nG contains %d strongly connected components:", i);
    
    i = 0;
    moveBack(Stack);
    while(index(Stack) != -1) {
	i++;
	fprintf(out, "\nComponent %d:", i);

	int j = 0;
	while(1) {
	    j++;	
            if(getParent(Trans, get(Stack)) == NIL) {
		break;
	    }
	    movePrev(Stack);	
	    if(index(Stack) == -1) {
	        moveFront(Stack);
		break;
	    }
	}

	fprintf(out, " %d", get(Stack));
        int k;
	for(k = 0; k < j - 1; k++) {
	    moveNext(Stack);
	    fprintf(out, " %d", get(Stack));
	}

	for(k = 0; k < j; k++) {
	    movePrev(Stack);
	}
    }
    fprintf(out, "\n");

    // free all graphs, lists
    // close all files
    freeGraph(&G);
    freeGraph(&Trans);
    freeList(&Stack);
    freeGraph(&G);
    fclose(in);
    fclose(out); 

    return 0;
}
