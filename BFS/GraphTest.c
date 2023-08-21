/*
 * Mahyar Mike Vahabi
 * mvahabi
 * Winter 22 - CSE101 - pa2
 * GraphTest.c - Personal Test for the graph ADTs
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"   

int main(){
    
    Graph G = newGraph(6);
    
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    
    printGraph(stdout, G);

    List L = newList();
    
    printf("\n");

    printf("get source %d.\n", getSource(G));

    printf("get parent (1) %d.\n", getParent(G, 1));
    printf("get parent (2) %d.\n", getParent(G, 2));
    printf("get parent (3) %d.\n", getParent(G, 3));
    printf("get parent (4) %d.\n", getParent(G, 4));
    printf("get parent (5) %d.\n", getParent(G, 5));
    printf("get parent (6) %d.\n", getParent(G, 6));

    printf("\n");

    printf("get distance (1) %d.\n", getDist(G, 1));
    printf("get distance (2) %d.\n", getDist(G, 2));
    printf("get distance (3) %d.\n", getDist(G, 3));
    printf("get distance (4) %d.\n", getDist(G, 4));
    printf("get distance (5) %d.\n", getDist(G, 5));
    printf("get distance (6) %d.\n", getDist(G, 6));
 
    BFS(G, 3);
    
    printf("\nThe distance from 3 to 6 is %d\n", getDist(G, 6));
    printf("The shortest path from 3 to 6 is: ");

    getPath(L,G, 6);
    printList(stdout, L);

    printf("\n"); 

    printf("get source %d.\n", getSource(G)); 

    printf("get parent _ %d.\n", getParent(G, 1)); 
    printf("get parent _ %d.\n", getParent(G, 2)); 
    printf("get parent _ %d.\n", getParent(G, 3)); 
    printf("get parent _ %d.\n", getParent(G, 4)); 
    printf("get parent _ %d.\n", getParent(G, 5)); 
    printf("get parent _ %d.\n", getParent(G, 6)); 

    printf("\n");

    printf("get distance _ %d.\n", getDist(G, 1)); 
    printf("get distance _ %d.\n", getDist(G, 2)); 
    printf("get distance _ %d.\n", getDist(G, 3)); 
    printf("get distance _ %d.\n", getDist(G, 4)); 
    printf("get distance _ %d.\n", getDist(G, 5)); 
    printf("get distance _ %d.\n", getDist(G, 6)); 

    clear(L); 
    freeGraph(&G);
    freeList(&L);
    return 0;
}
