//----------------------------------------------------------------------------
// class GraphL
// Developer: Yash Varde
//----------------------------------------------------------------------------
// ADT GraphL: A graph class that allows up to 100 nodes
// -- can display the graph by doing a depth-first search.
// -- can build a graph by reading a properly formatted input text file
// -- displays nodes and edges for each node in ascending order
// 
// Implementation and Assumptions:
// -- not more than 100 nodes will be provided.
// -- Each node in the graph will have a list of adjacent nodes
// -- **make sure enter has been pressed after the last line of the input file
//----------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H

#define MAXNODES 100

#include <iostream>
#include <list>
#include <iomanip>
#include <climits>
#include "nodedata.h"


using namespace std;

//-----------------------------------------------------------------------------
//struct GraphNode
//represents a node within the graph.
//contains details about its adjacent nodes, the data titles within, and 
//whether or not the node has already been visited.
struct GraphNode {    
    list<int> adjacentNodes;         // list of edges (edge nodes) 
    NodeData data;                   // information on the graph node
    bool visited;                    // whether or not node has been visited
};

class GraphL
{
public:
    //-------------------------------------------------------------------------
    //default constructor
    //initially sets the size to MAXNODES and marks each node as unvisited
    GraphL();

    //-------------------------------------------------------------------------
    //destructor
    //sets the graphNodeList back to its default value
    ~GraphL();

    //-------------------------------------------------------------------------
    //buildGraph()
    //builds the graph by reading from the input file stream
    //Precondition: the file is formatted according to the following sequence:
    //         1. number of nodes
    //         2. title for each graph
    //         3. start node precedes end node in a line
    //Postcondition: titles and edges are added to the graph
    void buildGraph(istream& infile);

    //-------------------------------------------------------------------------
    //displayGraph()
    //visits each node and prints out the edges in ascending order
    //Precondition: graph contains edges before calling this function
    //Postcondition: nodes and edges are printed in ascending order
    void displayGraph();

    //-------------------------------------------------------------------------
    //depthFirstSearch()
    //prints out each of the nodes in the graph via depth-first search
    //Precondition: assumes that the graph contains edges
    //Postcondition: nodes are printed out in depth-first search
    void depthFirstSearch();

private:
    int size;                               // number of nodes in the graph 
    GraphNode graphNodeList[MAXNODES];      // array of graph nodes 
    const unsigned int INF = INT_MAX;       // infinity: least minimum value

    //-------------------------------------------------------------------------
    //dfs()
    //helper function for depthFirstSearch() and takes in a starting node
    void dfs(int);                       // helper function of depthFirstSearch
};
#endif
