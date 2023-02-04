#include "graphl.h"

// Uses getline from string class, included in nodedata.h .
// Be sure to include nodedata.h which includes <string> .

//-----------------------------------------------------------------------------
//default constructor
//initially sets the size to MAXNODES and marks each node as unvisited
GraphL::GraphL()
{
    //set size to MAXNODES
    size = MAXNODES;
    
    //mark nodes as unvisited
    for (int i = 0; i <= size; i++)
    {
        graphNodeList[i].visited = false;
    }
}

//-----------------------------------------------------------------------------
//destructor
//sets the graphNodeList back to its default value
GraphL::~GraphL()
{
    for (int i = 1; i < size; i++)
    {
        GraphNode n = graphNodeList[i];

        //set all nodes to unvisited
        n.visited = false;
        
        //clear adjacency lists for each node
        list<int> adjacencyList = n.adjacentNodes;
        if (!adjacencyList.empty())
        {
            //clear the adjacency lists
            adjacencyList.clear();
        }
    }
    
    //set the size back to 0
    size = 0;
}

//-----------------------------------------------------------------------------
//buildGraph()
//builds the graph by reading from the input file stream
//Precondition: the file is formatted according to the following sequence:
//         1. number of nodes
//         2. title for each graph
//         3. start node precedes end node in a line
//Postcondition: titles and edges are added to the graph
void GraphL::buildGraph(istream& infile) {
    int fromNode, toNode;          // from and to node ends of edge

    //makeEmpty();                   // include if dynamic memory anywhere

    infile >> size;                // read the number of nodes
    if (infile.eof()) return;      // stop reading if no more data

    // explanation to student: when you want to read a string after an int, 
    // you must purge the rest of the int line or the end-of-line char will
    // be the string read
    string s;                      // used to read to end of line holding size
    getline(infile, s);

    // read graph node information
    for (int i = 1; i <= size; i++) {
        // read using setData of the NodeData class, where graphNodeList is the
        // array of GraphNodes and data is the NodeData object of GraphNode
        graphNodeList[i].data.setData(infile);
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode;
        if (fromNode == 0 && toNode == 0) return;     // end of edge data

        // insert a valid edge into the adjacency edge STL list for fromNode
        graphNodeList[fromNode].adjacentNodes.push_back(toNode);
    }
}

//-----------------------------------------------------------------------------
//displayGraph()
//visits each node and prints out the edges in ascending order
//Precondition: graph contains edges before calling this function
//Postcondition: nodes and edges are printed in ascending order
void GraphL::displayGraph()
{
    cout << "Graph:" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << setw(2) << "Node " << i;
        cout << "      " << graphNodeList[i].data << endl;

        list<int> adjacencyList = graphNodeList[i].adjacentNodes;
        list<int>::iterator it = adjacencyList.begin();
        
        while (it != adjacencyList.end())
        {
            cout << setw(2) << "  edge " << i << " ";
            cout << *it << endl;
            advance(it, 1);
        }
        cout << endl;
    }
}

//-----------------------------------------------------------------------------
//depthFirstSearch()
//prints out each of the nodes in the graph by performing a depth-first search
//Precondition: assumes that the graph contains edges
//Postcondition: nodes are printed out in depth-first search
void GraphL::depthFirstSearch()
{
    cout << "Depth first ordering: ";

    //initially, all vertices are not visited
    for (int v = 1; v <= size; v++)
    {
        if (!graphNodeList[v].visited)
        {
            dfs(v);
        }
    }
    cout << endl;
}

//-----------------------------------------------------------------------------
//dfs()
//helper function for depthFirstSearch() and takes in a starting node
void GraphL::dfs(int v)
{
    //mark v as visited
    graphNodeList[v].visited = true;

    //output v
    cout << v << " ";

    //set up an iterator to run through adjacency list
    list<int> adjacencyList = graphNodeList[v].adjacentNodes;
    list<int>::iterator it = adjacencyList.begin();

    if (it != adjacencyList.end())
    {
        //for each vertex w adjacent to v
        while (it != adjacencyList.end())
        {
            //depth first search if w is not visited
            int w = *it;
            if (!graphNodeList[w].visited)
            {
                dfs(w);
                w++;
            }

            //move iterator to the next adjacent node
            advance(it, 1);
        }
    }
}


