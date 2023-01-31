//---------------------------------------------------------------------------
#ifndef GRAPHM_H
#define GRAPHM_H

#define MAXNODES 100

#include <iostream>
#include <limits>
#include <iomanip>
#include "nodedata.h"

using namespace std;

//struct Edge
//represents a directed edge from one node to another
//consists of a start, an end, and a cost
struct Edge {
    //variables
    int start;         //the node where the edge starts from
    int end;           //the node that the edge ends at
    int cost;          //the cost of going from the start to the end

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

    /// displayPath()
    /// helper function that displays all nodes that form the path from start 
    /// to end
    void displayPath(int, int) const;   

    /// visitNode()
    /// sets the given column's node as visited
    /// Precondition: inputs must be valid row and column indexes
    /// Postcondition: sets all rows beneath given row of given column to true
    void visitNode(int, int);

    /// initializeRow()
    /// resets a row of the T array
    /// Precondition: none
    /// Postcondition: for T[i][j], dist = infinity, visited = false, path = 0.
    void initializeRow(int);
};

#endif

