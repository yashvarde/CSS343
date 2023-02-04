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
            //set all values in adjacency list to infinity
            C[i][j] = INF;

            //set all dists to INF initially.
            T[i][j].dist = INF;
            
            //set all visited nodes to unvisited
            T[i][j].visited = false;

            //set all paths to zero
            T[i][j].path = 0;
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
    infile >> size;

    //do not build graph if eof or number of nodes exceeds the max capacity
    if (infile.eof() || size >= MAXNODES)
    {
        return;
    }

    infile.get();       //reads the end of line character

    //next few lines = data labels for the graph
    for (int i = 1; i <= size + 1; i++)
    {
        //try reading in text from file
        if (infile.eof() || !data[i].setData(infile))
        {
            cout << "Couldn't set data from file" << endl;
            break;
        }
    }

    //read file values into the graph
    for (;;)
    {
        //convert file line to an edge
        int start;
        int end; 
        int cost;
        infile >> start;
        infile >> end; 
        infile >> cost;
        
        //end the loop if end of file
        if (infile.eof())
        {
            break;
        }

        bool emptyEdge = (start == 0) && (end == 0) && (cost == 0);

        //end the loop when the file reaches 0 0 0
        if (emptyEdge)
        {
            break;
        }

        //insert the edge into the graph
        insertEdge(start, end, cost); 
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
    for (int source = 1; source <= size; source++) 
    { 
        //visit source node and set distance to zero
        T[source][source].dist = 0;
        T[source][source].visited = true;

        //dijkstra's shortest path for a particular node
        int v = 1;
        for (int i = 1; i <= size; i++) {

            // Find the not yet visited node v with the minimum distance
            int minDist = INF;
            for (int index = 1; index <= size; index++)
            {
                bool shorterDist = minDist > C[source][index];
                bool visited = T[source][index].visited;
                
                //modify v if a shorter distance exists
                if (shorterDist)
                {
                    //set distance to adjacency cost if initially infinity
                    if (T[source][index].dist == INF)
                    {
                        T[source][index].dist = C[source][index];
                    }
                    if (!visited)
                    {
                        minDist = T[source][index].dist;
                    }
                    v = index;
                }
            }

            // mark v as visited
            T[source][v].visited = true;
            T[source][v].path = source;

            // for each w adjacent to v
            for (int w = 1; w <= size; w++)
            {
                //skip nonadjacent nodes
                bool adjacent = (C[v][w] != INF);
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
                    if (newDist != INF && C[v][w] != INF)
                    {
                        newDist += C[v][w];
                    }

                    T[source][w].dist = min(currentDist, newDist);

                    // If going through v is shorter, set .path to v
                    if (T[source][w].dist == newDist)
                    {
                        T[source][w].visited = true;
                        T[source][w].path = v;
                        v = w;
                    }
                }
            }
        }
    } 
}

//---------------------------------------------------------------------------
/// insertEdge()
/// inserts the provided edge into the graph without modifying the parameter
/// Precondition: the edge must contain nonnegative integer values
/// Postcondition: returns true if the edge was successfully inserted
bool GraphM::insertEdge(int start, int end, int cost)
{
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
/// removes the specified edge from the graph without modifying the parameter
/// Precondition: the edge must contain nonnegative integer values
/// Postcondition: returns true if the edge was successfully removed
bool GraphM::removeEdge(int start, int end, int cost)
{
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
    cout << setw(25) << "From node    ";
    cout << setw(10) << "To node   ";
    cout << setw(10) << "Dijkstra's ";
    cout << setw(10) << "Path" << endl;

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
    cout << endl;
}

//---------------------------------------------------------------------------
/// display()
/// displays information about a particular path in the graph
/// Precondition: start and end must be between 1 and the size of the arrays
/// Postcondition: displays details about the given graph
void GraphM::display(int start, int end) const
{
    //display source and destination
    cout << setw(30) << start << setw(10) << end;

    //display the cost (or "---" if it is INF)
    if (T[start][end].dist == INF)
    {
        cout << setw(10) << "---" << endl;
        return;
    }
    else
    {
        cout << setw(10) << T[start][end].dist;
    }

    //display path from start node to end node
    cout << "        ";
    displayPath(start, end);

    //end the line
    cout << endl;
}

//---------------------------------------------------------------------------
/// displayPath()
/// helper function that displays all nodes that form the path from start 
/// to end
void GraphM::displayPath(int start, int end) const
{
    //find node to go through to get shortest path to "end"
    int node = end;

    //display the path from the start to the intermediate node
    if (node != start && start > 0 && end > 0)
    {
        node = T[start][end].path;
        displayPath(start, node);
    }

    //print the last node
    cout << setw(8) << end;
}

//---------------------------------------------------------------------------
/// operator >>
/// overloaded input stream operator for Edge
istream& operator>>(istream& stream, Edge& edge)
{
    //read in start, end, and cost values into edge
    stream >> edge.start >> edge.end >> edge.cost;
    return stream;
}
