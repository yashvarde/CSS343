//----------------------------------------------------------------------------
// class GraphM
// Developer: Yash Varde
//----------------------------------------------------------------------------
// ADT GraphM: A class consisting of up to 100 nodes
// -- Determines the shortest path from the start node to each of the others.
// -- Reads from the text file and generates a graph based on the input.
// -- size represents the number of nodes in the graph, not the capacity (100)
// 
// Implementation and Assumptions:
// -- Dijkstra's shortest algorithm is used to determine the shortest paths.
// -- Uses an adjacency matrix C[][] for representing the cost between nodes.
// -- TableType stores key information necessary for Dijstra's algorithm.
// -- **make sure enter has been pressed after the last line of the input file
//----------------------------------------------------------------------------
#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include <climits>
#include <iomanip>
#include "nodedata.h"

#define MAXNODES 100

using namespace std;

//---------------------------------------------------------------------------
//struct Edge
//represents a directed edge from one node to another
//consists of a start, an end, and a cost
struct Edge {
    //variables
    int start = -1;         //the node where the edge starts from
    int end = -1;           //the node that the edge ends at
    int cost = -1;          //the cost of going from the start to the end

    //overloaded input stream operator
    friend istream& operator >> (istream&, Edge&);
};

class GraphM
{
public:
    //---------------------------------------------------------------------------
    /// default constructor
    /// initializes the graph and its contents
    GraphM();

    //---------------------------------------------------------------------------
    /// buildGraph()
    /// builds the graph after reading info from the provided input stream
    /// Precondition: file data must be formatted such that:
    ///                - the first value represents the number of nodes
    ///                - text represents titles for graph locations
    ///                - integer triplets are ordered: (source, destination, cost)
    /// Postcondition: the graph is created according to the file's data
    void buildGraph(istream& infile);

    //---------------------------------------------------------------------------
    /// findShortestPath()
    /// Uses Dijkstra's shortest path algorithm to determine the shortest path
    /// from each node to every other node.
    /// Precondition: graph must be built before calling this function
    /// Postcondition: array T consists of the shortest paths from each node
    void findShortestPath();

    //-------------------------------------------------------------------------
    /// insertEdge()
    /// inserts the provided edge into the graph
    /// Precondition: the edge must contain nonnegative integer values
    /// Postcondition: returns true if the edge was successfully inserted
    bool insertEdge(const Edge& edge);

    //-------------------------------------------------------------------------
    /// removeEdge()
    /// removes the specified edge from the graph
    /// Precondition: the edge must contain nonnegative integer values
    /// Postcondition: returns true if the edge was successfully removed
    bool removeEdge(const Edge& edge);
   
    //-------------------------------------------------------------------------
    /// displayAll()
    /// displays all information about the given graph
    /// Precondition: none
    /// Postcondition: displays details about the given graph
    void displayAll() const;

    //-------------------------------------------------------------------------
    /// display()
    /// displays information about a particular path in the graph
    /// Precondition: start & end must be between 1 and the size of the arrays
    /// Postcondition: displays details about the given graph
    void display(int start, int end) const;

private:
    //struct Tabletype
    //represents data about a particular node in the cost array C[][]
    struct TableType {
        bool visited;       // whether node has been visited 
        int dist;           // currently known shortest distance from source 
        int path;           // previous node in path of min dist
    };

    NodeData data[MAXNODES];            // data for graph nodes information 
    int C[MAXNODES][MAXNODES];          // Cost array, the adjacency matrix 
    int size;                           // number of nodes in the graph 
    TableType T[MAXNODES][MAXNODES];    // stores Dijkstra information 
    const unsigned int INF = INT_MAX;   //infinity: least minimum int value

    //-------------------------------------------------------------------------
    /// displayPath()
    /// helper function that displays all nodes that form the path from start 
    /// to end
    void displayPath(int, int) const;   

    //-------------------------------------------------------------------------
    /// visitNode()
    /// sets the given column's node as visited
    /// Precondition: inputs must be valid row and column indexes
    /// Postcondition: sets all rows beneath given row of given column to true
    void visitNode(int, int);

    //-------------------------------------------------------------------------
    /// initializeRow()
    /// resets a row of the T array
    /// Precondition: none
    /// Postcondition: for T[i][j], dist = infinity, visited = false, path = 0.
    void initializeRow(int);
    
    //-------------------------------------------------------------------------
    /// findMinNode()
    /// returns the closest adjacent node from a given source node
    /// Precondition: source node must exist
    /// Postcondition: returns an integer corresponding to the closest node
    int findMinNode(int);
    
    //-------------------------------------------------------------------------
    /// exploreAdjacentNodes()
    /// explores and visits different nodes to find the closest node (w)
    /// Precondition: source node and intermediate node (v) must exist
    /// Postcondition: finds a shorter route to get from the source to w
    void exploreAdjacentNodes(int, int);
};

#endif

