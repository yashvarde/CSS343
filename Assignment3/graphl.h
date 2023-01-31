#ifndef GRAPHL_H
#define GRAPHL_H

#include <iostream>
using namespace std;

struct GraphNode {          // structs for simplicity (no fns), use class if desired 
    //STL list of ints         // list of edges (edge nodes), the adjacent graph node 
     //   NodeData or NodeData *    // information on the graph node 
       // etc.
};

class GraphL
{
public:
    void buildGraph(istream& infile);

private:
    //array of GraphNodes, static array is fine, assume at most 100 nodes
};
#endif

