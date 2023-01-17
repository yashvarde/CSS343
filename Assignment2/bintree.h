//---------------------------------------------------------------------------
// class BinTree
// Developer: Yash Varde
//---------------------------------------------------------------------------
// ADT BinTree:
// 
// Implementation and Assumptions:
//---------------------------------------------------------------------------
#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include "nodedata.h"

using namespace std;
class BinTree
{
    friend ostream& operator << (ostream&, const BinTree&);
public:
    BinTree();
    BinTree(const BinTree&);

    BinTree& operator = (const BinTree&);
    bool operator == (const BinTree&) const;
    bool operator != (const BinTree&) const;

    bool retrieve(const NodeData&, NodeData*&) const;
    bool insert(NodeData*);
    bool remove(const NodeData&, NodeData*&);
    bool getSibling(const NodeData&, NodeData&) const;
    bool getParent(const NodeData&, NodeData&) const;
    bool isEmpty() const;
    void bstreeToArray(NodeData* []);
    void arrayToBSTree(NodeData* []);
    void displaySideways() const;
    void makeEmpty();

private:
    struct Node
    {
        NodeData* data;
        Node* left;
        Node* right;
    };
    Node* root = nullptr;

    void sidewaysHelper(Node* current, int level) const;
};
#endif
