//---------------------------------------------------------------------------
// class BinTree
// Developer: Yash Varde
//---------------------------------------------------------------------------
// ADT BinTree: a binary search tree with additional binary tree functions
// -- can determine the parent and the sibling of any node in the tree
// -- can compare two trees to determine whether or not they are equal
// -- BST is displayed sideways (i.e. root is leftmost value in output)
// -- ability to convert from an array to a tree and from a tree to an array
// -- Contains nodes that point to NodeData objects containing a data string
// 
// Implementation and Assumptions:
// -- converting from a tree to an array empties the tree
// -- trees that are equal contain the same elements AND the same shape
// -- converting from an array to a tree nullifies all elements in the tree
// -- in <<, an inorder traversal of the tree is performed (left, root, right)
// -- most functionality is implemented recursively = many helper functions
//---------------------------------------------------------------------------
#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include "nodedata.h"

using namespace std;
class BinTree
{
    //operator <<
    //overloaded output stream operator
    //Preconditions: BinTree being outputted must exist in advance
    //Postconditions: BinTree elements are posted "in order." 
    friend ostream& operator << (ostream&, const BinTree&);

public:
    //default constructor
    //creates an empty tree: root is set to null
    //Preconditions: none
    //Postconditions: helps create BinTree object
    BinTree();

    //copy constructor
    //creates a BinTree by copying from an already created BinTree
    //Preconditions: BinTree argument must already be defined somewhere
    //Postconditions: BinTree copy is created
    BinTree(const BinTree&);

    //destructor
    //assists in deallocating the BinTree object and all its elements
    //Preconditions: BinTree must be instantiated before calling destructor
    //Postconditions: BinTree is deleted
    ~BinTree();

    //operator =
    //overloaded assignment operator
    //Preconditions: BinTree argument must be declared in advance
    //Postconditions: "this" BinTree is a copy of the BinTree argument
    BinTree& operator = (const BinTree&);

    //operator ==
    //overloaded equals operator
    //Preconditions: both BinTrees must exist in advance
    //Postconditions: returns true if both BinTrees are equal: false otherwise
    bool operator == (const BinTree&) const;

    //operator !=
    //overloaded not equals operator
    //Preconditions: both BinTrees must exist in advance
    //Postconditions: returns tree if both BinTrees are not equal
    bool operator != (const BinTree&) const;

    //retrieve()
    //retrieves a node from the tree and provides a pointer to it
    //Preconditions: two arguments must be provided
    //Postconditions: returns true if the node could be retrieved
    bool retrieve(const NodeData&, NodeData*&) const;

    //insert()
    //inserts a particular NodeData into the BinTree
    //Preconditions: NodeData must not have an empty string
    //Postconditions: returns true if the node was inserted successfully
    bool insert(NodeData*);

    //remove()
    //removes and fills in a pointer to the desired node
    //Preconditions: two arguments must be provided
    //Postconditions: returns true if the node was removed successfully
    bool remove(const NodeData&, NodeData*&);

    //getSibling()
    //finds the other node that has the same parent as the provided node
    //Preconditions: two arguments must be provided
    //Postconditions: returns true if the sibling could be found
    bool getSibling(const NodeData&, NodeData&) const;

    //getParent()
    //finds the parent of a particular node if it exists
    //Preconditions: two arguments must be provided
    //Postconditions: returns true if the parent could be retrieved
    bool getParent(const NodeData&, NodeData&) const;

    //isEmpty()
    //determines whether the BinTree is empty
    //Preconditions: none
    //Postconditions: returns true if the root pointer is null
    bool isEmpty() const;

    //bstreeToArray()
    //transfers elements from the tree to the provided array (in order)
    //Preconditions: array size is at least 100
    //Postconditions: BinTree is empty, and array argument contains elements
    void bstreeToArray(NodeData* []);

    //arrayToBSTree()
    //creates a balanced tree from the provided array
    //Preconditions: array must be SORTED
    //Postconditions: array contains null pointers, and tree contains elements
    void arrayToBSTree(NodeData* []);

    //displaySideways()
    //displays the BinTree such that the leftmost nodes are the root nodes
    //Preconditions: all nodes in the BinTree should be readable
    //Postconditions: tree is displayed from left to right
    void displaySideways() const;

    //makeEmpty()
    //deallocates all the nodes and sets the root to null
    //Preconditions: none
    //Postconditions: tree is empty
    void makeEmpty();

private:

    //Node
    //represents a particular node of a BinTree. Contains THREE pointers:
    //1) a data pointer to a NodeData object holding a string of data 
    //2) a left pointer to the left child of the given node
    //3) a right pointer to the right child of the given node
    struct Node
    {
        NodeData* data;                 //pointer to object of data stored
        Node* left;                     //pointer to left node
        Node* right;                    //pointer to right node
    };

    Node* root = nullptr;               //root of the binary search tree

    //Helper functions: used for recursive implementation
    void sidewaysHelper(Node* current, int level) const;
    Node* copy(Node* source, Node* dest);
    Node* makeEmptyHelper(Node* root);
    void inorder(ostream&, Node*) const;
    bool compareTrees(Node* first, Node* second) const;
    bool retrieveHelper(const NodeData&, NodeData*&, Node*) const;
    Node* removeHelper(const NodeData&, NodeData*&, Node*);
    Node* removeNode(Node*&);
    Node* predecessor(Node*, Node*&) const;
    Node* arrayToBSTreeHelper(NodeData* [], int, int);
    void bstreeToArrayHelper(Node*, NodeData* [], int&);
    Node* getSiblingHelper(Node*, NodeData) const;
    Node* getParentHelper(Node*, NodeData) const;
};
#endif
