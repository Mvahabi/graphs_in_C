# Assignment pa2 : Graph ADTs

The purpose of this assignment is to implement a Graph ADT and associated algorithms in C. This project will utilize 
a List ADT (List.h and List.c), in order to find and track information about pathings of a vertices in a graph.
The main program for this project is called FindPath.c. The Graph ADT module will be contained in files called
Graph.h and Graph.c, and will export its services to the client module FindPath.c GraphTest.c and GraphClient.c.

## Build
    
    $ make

## Running

### ./FindPath "in1" "out1"
### ./GraphClient 
### ./GraphTest

For the GraphClient program, there is no need to give it any arguments/commands.
For the FindPath program, you need a in1 = name of a pre-written file; this file
contains 3 parts: number of vertices to make for a graph (followed by a new line), 
series of vertices (each pair on a new line) to be added as an edge (typed as "x y") 
and followed by a "0 0", and lastly, series of paired up vertices (each pairs on a new line) 
to find the pathing and shortes distance between the two points, eneded with another "0 0". 
The second command could be any names, which would write the output of the FindPath program into that file. 
