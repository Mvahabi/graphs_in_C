# Assignment pa3 : Graph ADTs and DFS

The purpose of this assignment is to implement a Graph ADT and associated algorithms in C. This project will utilize 
a List ADT (List.h and List.c), in order to find and track information about pathings of a vertices in a graph.
The main program for this project is called FindPath.c. The Graph ADT module will be contained in files called
Graph.h and Graph.c, and will export its services to the client module FindComponenets.c and GraphTest.c.

## Build
    
    $ make

## Running

### ./FindComponenets "in1" "out1"
### ./GraphTest

For the FindComponents program, you need a in = name of a pre-written file; the first line it reads the 
number of vertices to make for a graph (followed by a new line), series of vertices (each pair on a new line) 
to be added as an arc (typed as "x y") and followed by a "0 0" to end the file reading. It explores as fall as 
graph connection goes and finds all strong connections by iterating through a graph and its transpose. The second 
command could be any names, which would write the output of the FindComponents program into that file. 
