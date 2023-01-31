#include "graphl.h"

// Uses getline from string class, included in nodedata.h .
// Be sure to include nodedata.h which includes <string> .

void GraphL::buildGraph(istream& infile) {
    int fromNode, toNode;          // from and to node ends of edge

    makeEmpty();                   // include if dynamic memory anywhere

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
        //    graphNodeList[i].data.setData(infile);
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode;
        if (fromNode == 0 && toNode == 0) return;     // end of edge data

        // insert a valid edge into the adjacency edge STL list for fromNode
    }
}
