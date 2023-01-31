#include "graphm.h"

//---------------------------------------------------------------------------
/// default constructor
/// initializes the graph and its contents
GraphM::GraphM()
{
    //initialize the size
    size = MAXNODES;

    //initialize array T and array C
    for (int i = 0; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
        {
            //set all dists to INF
            T[i][j].dist = INF;
            
            //set all visited nodes to unvisited
            T[i][j].visited = false;

            //set all paths to zero
            T[i][j].path = 0;

            //set all adjacency costs to INF
            C[i][j] = 0;
        } 
    }
}

//---------------------------------------------------------------------------
/// buildGraph()
/// builds the graph after reading info from the provided input stream
/// Precondition: file data must be formatted such that:
///                - the first value represents the number of nodes
///                - text represents titles for graph locations
///                - integer triplets are ordered: (source, destination, cost)
/// Postcondition: the graph is created according to the file's data
void GraphM::buildGraph(istream& infile)
{
    //first value = number of nodes in graph
    int n;
    infile >> n;

    //do not build graph if the number of nodes exceeds the max capacity
    if (n > MAXNODES || infile.eof())
    {
        return;
    }

    infile.get();       //reads the end of line character
    size = n;

    //next few lines = data labels for the graph
    for (int i = 1; i <= n; i++)
    {
        //try reading in text from file
        if (!data[i].setData(infile))
        {
            cout << "Couldn't set data from file" << endl;
        }
    }

    //read file values into the graph
    for (;;)
    {
        //convert file line to an edge
        Edge edge;
        infile >> edge;
        
        bool emptyEdge = edge.start == 0 && edge.end == 0 && edge.cost == 0;

        //end the loop when the file reaches 0 0 0
        if (emptyEdge)
        {
            break;
        }

        //insert the edge into the graph
        insertEdge(edge);
    }
}

//---------------------------------------------------------------------------
/// findShortestPath()
/// Uses Dijkstra's shortest path algorithm to determine the shortest path
/// from each node to every other node.
/// Precondition: graph must be built before calling this function
/// Postcondition: array T consists of the shortest paths from each node
void GraphM::findShortestPath()
{
    //find shortest path from each of the nodes
    for (int source = 1; source <= size; source++) {

        //initialize the row in T array before filling it
        initializeRow(source);

        //mark source as visited
        visitNode(source, source);

        //dijkstra's shortest path for a particular node
        for (int i = 1; i <= size; i++) {

            // Find the not yet visited node v with the minimum distance
            int v = 1;
            int minDist = INF;
            for (int index = 1; index <= size; index++) 
            {
                bool visited = T[source][index].visited;
                if (!visited && minDist > T[source][index].dist)
                {
                    minDist = T[source][index].dist;
                    v = index;
                }
            }

            // mark v as visited
            visitNode(source, v);
            
            // for each w adjacent to v
            for (int w = 1; w <= size; w++)
            {
                //skip nonadjacent nodes
                bool adjacent = (C[v][w] != 0);
                if (!adjacent)
                {
                    continue;
                }

                // if (w is not visited)
                if (!T[source][w].visited)
                {
                    // Adjust the shortest distance from source to w
                    int currentDist = T[source][w].dist;
                    int newDist = T[source][v].dist;
                    
                    //DO NOT add a positive integer to INF -> causes negative result
                    if (newDist != INF)
                    {
                        newDist += C[v][w];
                    } 

                    T[source][w].dist = min(currentDist, newDist);

                    // If going through v is shorter, set .path to v
                    if (T[source][w].dist == newDist)
                    {
                        T[source][w].path = v;
                        visitNode(source, v);
                    }
                }
            }
        }
    }
}

/// visitNode()
/// sets the given column's node as visited
/// makes all rows beneath, and including the existing row, as visited
void GraphM::visitNode(int r, int c)
{
    for (int i = r; i < size; i++)
    {
        //consider the node as visited after being encountered at row r
        T[i][c].visited = true;
    }
}

/// recoverPath()
/// resets the T array
/// Precondition: none
/// Postcondition: for T[i][j], dist = INF, visited = false, path = 0.
void GraphM::initializeRow(int r)
{
    for (int i = 1; i < size; i++)
    {
        //set all dists to INF
        T[r][i].dist = INF;

        //set all visited nodes to unvisited
        T[r][i].visited = false;

        //set all paths to zero
        T[r][i].path = 0;
    }
    
    //set source to source distance to 0;
    T[r][r].dist = 0;
}

//---------------------------------------------------------------------------
/// insertEdge()
/// inserts the provided edge into the graph
/// Precondition: the edge must contain nonnegative integer values
/// Postcondition: returns true if the edge was successfully inserted
bool GraphM::insertEdge(const Edge& edge)
{
    //extract values from edge structure
    int start = edge.start;
    int end = edge.end;
    int cost = edge.cost;

    //have a variable for checking whether cost has been changed
    bool changed = false;

    //change the cost if the new edge changes the cost
    if (C[start][end] != cost)
    {
        C[start][end] = cost;
        changed = true;
    }

    //return whether or not the value has been changed
    return changed;
}

//---------------------------------------------------------------------------
/// removeEdge()
/// removes the specified edge from the graph
/// Precondition: the edge must contain nonnegative integer values
/// Postcondition: returns true if the edge was successfully removed
bool GraphM::removeEdge(const Edge& edge)
{
    //extract values from edge structure
    int start = edge.start;
    int end = edge.end;
    int cost = edge.cost;

    //have a variable for checking whether cost has been changed
    bool changed = false;

    //change the cost if the edge already contains that cost
    if (C[start][end] == cost)
    {
        C[start][end] = INF;
        changed = true;
    }

    //return whether or not the value has been changed
    return changed;
}

//---------------------------------------------------------------------------
/// displayAll()
/// displays all information about the given graph
/// Precondition: none
/// Postcondition: displays details about the given graph
void GraphM::displayAll() const
{
    //display titles
    cout << "Description ";   
    cout << setw(20) << "From node";  
    cout << setw(15) << "To node";
    cout << setw(15) << "Dijkstra's";
    cout << setw(5) << "Path" << endl;

    //display the dijkstra path for each of the nodes in the graph
    for (int i = 1; i <= size; i++)
    {
        //display graph title
        cout << data[i] << endl;

        //display dijkstra's information for the given node
        for (int j = 1; j <= size; j++)
        {
            //do not print same node twice
            if (i == j)
            {
                continue;
            }
            else
            {
                //display cost and path from source to destination
                display(i, j);
            }
        }
    }
}

//---------------------------------------------------------------------------
/// display()
/// displays information about a particular path in the graph
/// Precondition: start and end must be between 1 and the size of the arrays
/// Postcondition: displays details about the given graph
void GraphM::display(int start, int end) const
{
    //display source and destination
    cout << setw(24) << start << setw(19) << end;

    //display the cost (or "---" if it is INF)
    if (T[start][end].dist == INF)
    {
        cout << setw(15) << "---" << endl;
        return;
    }
    else
    {
        cout << setw(15) << T[start][end].dist;
    }

    //display path from start node to end node
    displayPath(start, end);

    //end the line
    cout << endl;
}

/// displayPath()
/// helper function that displays all nodes that form the path from start 
/// to end
void GraphM::displayPath(int start, int end) const
{
    //find node to go through to get shortest path to "end"
    int node = end;
    
    //display the path from the start to the intermediate node
    if (node != start)
    {
        node = T[start][end].path;
        displayPath(start, node);
    }
    
    //print the last node
    cout << setw(8) << end;
}

/// operator >>
/// overloaded input stream operator for Edge
istream& operator>>(istream& stream, Edge& edge)
{
    //read in start, end, and cost values into edge
    stream >> edge.start >> edge.end >> edge.cost;
    return stream;
}
