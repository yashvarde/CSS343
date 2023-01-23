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
    ~BinTree();

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
        NodeData* data;                 //pointer to object of data stored
        Node* left;                     //pointer to left node
        Node* right;                    //pointer to right node
    };
    Node* root = nullptr;

    void sidewaysHelper(Node* current, int level) const;
    Node* copy(Node* source, Node* dest);
    Node* makeEmptyHelper(Node* root);
    void inorder(ostream&, Node*) const;
    bool compareTrees(Node* first, Node* second) const;
    bool retrieveHelper(const NodeData&, NodeData*&, Node*) const;
    Node* removeHelper(const NodeData&, NodeData*&, Node*);
    Node* removeNode(Node*&);
    Node* predecessor(Node*) const;
    void arrayToBSTreeHelper(Node*, NodeData* [], int, int);
    void bstreeToArrayHelper(Node*, NodeData* [], int);
    Node* getSiblingHelper(Node*, NodeData) const;
    Node* getParentHelper(Node*, NodeData) const;
};
#endif
