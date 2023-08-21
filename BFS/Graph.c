/*
Mahyar Mike Vahabi
mvahabi
Winter 22 - CSE101 - pa2
Graph.c - Graph ADT
*/

// Citation: Professor Tantalo's PsudoCode, notes, and queue.c implementation

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

// private Graph object type 
typedef struct GraphObj {
    List* list;
    char* color;  // array of color of vertex "i"
    int* parent; // array of parent of vertex "i"
    int* dist;   // array of distance from source to vertex "i"
    int order;   // stores #vertices = n
    int size;    // # of edges
    int source;  // label for recent vertex used as source
}GraphObj;

// constructor for graph
Graph newGraph(int n) {
    if (n<0) {
        fprintf(stderr, "Error in newGraph(). Can't graph 0 or negative vertices.\n");
        exit(EXIT_FAILURE);
    }
    Graph G = malloc(sizeof(GraphObj));
    if (G) {
        G->order = n;
        G->size = 0;
        G->source = NIL;
        G->list = malloc(sizeof(List) * n+1);
        G->color = malloc(sizeof(char) * n+1);
        G->parent = malloc(sizeof(int) * n+1);
        G->dist = malloc(sizeof(int) * n+1);
        for (int i = 1; i < n+1; i++) {
            G->list[i] = newList();
            G->color[i] = 'w';
            G->parent[i] = NIL;
            G->dist[i] = INF;
        }
    }
    return G;
}

// destructor for graph
void freeGraph(Graph* pG) {
    if (!pG){
        fprintf(stderr, "Error in FreeGraph(). Can not free an empty graph.\n");
        exit(EXIT_FAILURE);
    }
    if (pG && *pG) {
        for (int i = 1; i < (*pG)->order + 1; i++) {
            freeList(&(*pG)->list[i]);
        }
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->dist);
        free(*pG);
        *pG = NULL;
    }
}

// returns number of vertices
int getOrder(Graph G){
    if (!G) { 
        fprintf(stderr, "Error in getOrder(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// returns number of edges
int getSize(Graph G){
    if (!G) {
        fprintf(stderr, "Error in getSize(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// returns the source vertex used in BFS() or nil if BFS() wasn't called
int getSource(Graph G){
    if (!G) {
        fprintf(stderr, "Error in getSource(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

// return the parent of vertex u in BFS() or nul if BFS() wasn't called
int getParent(Graph G, int u){
    if (!G) {
        fprintf(stderr, "Error in getParent(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 0 || u > getOrder(G)) {
        fprintf(stderr, "Error in getParent(). U is out of range.\n");
        exit(EXIT_FAILURE);
    } else {
        return G->parent[u];
    }
}

// returns the distance from the most recent BFS source to vertex u, or INF if BFS()
int getDist(Graph G, int u){
    if (!G) {
        fprintf(stderr, "Error in getDist(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
     if(G->source < 0){
        return INF;
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Error in getDist(). U is out of range.\n");
        exit(EXIT_FAILURE);
    } else {
        return G->dist[u];
    }
}

// appends to the List L the vertices of a shortest path in G from source to u, or 
// appends to L the value NIL if no such path exists
void getPath(List L, Graph G, int u) {
    if (!G || !L) {
        fprintf(stderr, "Error in getPath(). Empty graph or empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Error in getPath(). BFS was not called/no source given or found.\n");
        exit(EXIT_FAILURE);
    } 
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Error in getPath(). Invalid 'u'.\n");
        exit(EXIT_FAILURE);
    }
    if (u == G->source) {
        append(L, G->source);
    } else if (G->parent[u] == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

// deletes all edges of G
void makeNull(Graph G) {
    if (!G) {
        fprintf(stderr, "Error in makeNull(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    freeGraph(&G);
    newGraph(G->order);
}

//nserts a new edge joining u to v, i.e. u is added to the adjacency List of v, 
//and v to the adjacency List of u. 
void addEdge(Graph G, int u, int v) {
    if (!G) {
        fprintf(stderr, "Error in addEdge(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 0 || v < 0) {
        fprintf(stderr, "Error in addEdge(). Invalid u or v.\n");
        exit(EXIT_FAILURE);
    }

    // connect u, v
    moveFront(G->list[u]);
    bool bool_flag = true;
    if (length(G->list[u]) == 0) {
        append(G->list[u], v);
        bool_flag = false;
    }
    while (bool_flag && index(G->list[u]) >= 0 && index(G->list[u]) < length(G->list[u])) {
        if (get(G->list[u]) >= v) {
            insertBefore(G->list[u], v);
            bool_flag = false;
        }
        else if (index(G->list[u]) == (length(G->list[u]) - 1)) {
            append(G->list[u], v);
            bool_flag = false;
        } else {
            moveNext(G->list[u]);
        }
    }

    // connect v, u
    moveFront(G->list[v]);
    bool_flag = true;
    if (length(G->list[v]) == 0) {
            append(G->list[v], u);
            bool_flag = false;
    }
    while (bool_flag && index(G->list[v]) >= 0 && index(G->list[v]) < length(G->list[v])) {
        if (get(G->list[v]) >= u) {
            insertBefore(G->list[v], u);
            bool_flag = false;
        }
        else if (index(G->list[v]) == (length(G->list[v]) - 1)) {
            append(G->list[v], u);
            bool_flag = false;
        } else {
            moveNext(G->list[v]);
        }
    }
    G->size++;
}

// adds a directed edge
void addArc(Graph G, int u, int v) {
    if (!G) {
        fprintf(stderr, "Error in addArc(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 0 || v < 0) {
        fprintf(stderr, "Error in addArc(). Invalid u or v.\n");
        exit(EXIT_FAILURE);
    }

    // connect u, v but not other way around
    moveFront(G->list[u]);
    bool bool_flag = true;
    if (length(G->list[u]) == 0) {
        append(G->list[u], v);
        bool_flag = false;
    }
    while (bool_flag && index(G->list[u]) >= 0 && index(G->list[u]) < length(G->list[u])) {
        if (get(G->list[u]) >= v) {
            insertBefore(G->list[u], v);
            bool_flag = false;
        }
        else if (index(G->list[u]) == (length(G->list[u]) - 1)) {
            append(G->list[u], v);
            bool_flag = false;
            } else {
            moveNext(G->list[u]);
        }
    }
    G->size++;
}

// perform Breadth First Search
void BFS(Graph G, int s) {
    if (!G) {
        fprintf(stderr, "Error in addArc(). Empty graph.\n");
        exit(EXIT_FAILURE);
    }
    if (s <= 0) {
        fprintf(stderr, "Error in BFS(). Invalid 's' input.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < G->order + 1; i++) {
        G->color[i] = 'w';
        G->dist[i] = INF; 
        G->parent[i] = NIL;
    }
    
    G->source = s;
    G->color[s] = 'g';
    G->dist[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    moveFront(G->list[s]);
    append(Q, s);
    while (length(Q) != 0) {
        moveFront(Q);
        int x = get(Q);
        moveFront(G->list[x]);
        for (int iter = 1; iter <= length(G->list[x]); iter++){
            int y = get(G->list[x]);
            if (G->color[y] == 'w') {
                G->color[y] = 'g';
                G->dist[y] = G->dist[x]+1;
                G->parent[y] = x;
                append(Q, y);
            }
            moveNext(G->list[x]);
        }
        G->color[x] = 'b';
        deleteFront(Q);
    }
    freeList(&Q);
}

//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){
    if (!G) {
        fprintf(stderr, "Error in pringGraph(). empty graph.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i <= G->order; i++){
        moveFront(G->list[i]);
        fprintf(out, "%d: ",i );
        while(index(G->list[i]) >  -1){
            fprintf(out, "%d ", get(G->list[i]));
            moveNext(G->list[i]);
        }
        fprintf(out, "\n");
    }
}
