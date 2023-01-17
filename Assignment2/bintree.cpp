#include "bintree.h"

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side.
// Turn head 90 degrees counterclockwise (to the left) to see tree structure.
// Hard coded displaying to standard output.
void BinTree::displaySideways() const {
    sidewaysHelper(root, 0);
}

void BinTree::sidewaysHelper(Node* current, int level) const {
    if (current != nullptr) {
        level++;
        sidewaysHelper(current->right, level);

        // indent for readability, same number of spaces per depth level 
        for (int i = level; i >= 0; i--) {
            cout << "        ";
        }

        cout << *current->data << endl;        // display information of object
        sidewaysHelper(current->left, level);
    }
}

//---------------------------------------------------------------------------
void BinTree::makeEmpty()
{
}

//---------------------------------------------------------------------------
ostream& operator<<(ostream& stream, const BinTree&)
{
    return stream;
}

//---------------------------------------------------------------------------
BinTree::BinTree()
{
}

//---------------------------------------------------------------------------
BinTree::BinTree(const BinTree&)
{
}

//---------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree&)
{
    return *this;
}

//---------------------------------------------------------------------------
bool BinTree::operator==(const BinTree&) const
{
    return false;
}

//---------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree&) const
{
    return false;
}

//---------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData&, NodeData*&) const
{
    return false;
}

//---------------------------------------------------------------------------
/*BSTree insert routine

Below is an iterative solution to insert.It traverses one branch.
Note that this assumes "operator<" exists for a NodeData object.
The line of code :
if (*ptr->data < *current->data)
    calls "operator<" for NodeData objects.Both* ptr->dataand* current->data
    are NodeData objects.Without the asterisks, they are pointers.
    Dereferencing, including the asterisks gives the objects.

    If* ptr->data is called A, and* current->data is called B, then the condition
    above is equivalent to : A < B
    which is : A.operator<(B)     for NodeData objects.

    // Note: left is searched for <, right for >=, handle == separately if desired

    // Assumes the NodeData object has been instantiated and passed into insert()
    // Memory is fully allocated and inititalized
 */
bool BinTree::insert(NodeData* dataptr) {
    Node* ptr = new Node;

    if (ptr == nullptr)
    {
        return false;                // out of memory
    }
    
    ptr->data = dataptr;
    ptr->left = ptr->right = nullptr;

    if (isEmpty()) {
        root = ptr;
    }
    else {
        Node* current = root;                     // walking pointer
        bool inserted = false;                    // whether inserted yet

        // Traverse tree; if item is less than current item, insert in 
        // left subtree, otherwise insert in right subtree
        while (!inserted) {
            if (*ptr->data < *current->data) {
                if (current->left == nullptr) {     // insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;         // one step left
            }
            else {   // >=
                if (current->right == nullptr) {    // insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                {
                    current = current->right;        // one step right
                }
            }
        }
    }
    return true;
}

//---------------------------------------------------------------------------
bool BinTree::remove(const NodeData&, NodeData*&)
{
    return false;
}

//---------------------------------------------------------------------------
bool BinTree::getSibling(const NodeData&, NodeData&) const
{
    return false;
}

//---------------------------------------------------------------------------
bool BinTree::getParent(const NodeData&, NodeData&) const
{
    return false;
}

//---------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
    return false;
}

//---------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* [])
{
}

//---------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* [])
{
}
