#include "bintree.h"

//---------------------------------------------------------------------------
//default constructor
//creates an empty tree: root is set to null
//Preconditions: none
//Postconditions: helps create BinTree object
BinTree::BinTree()
{
    root = nullptr;
}

//---------------------------------------------------------------------------
//copy constructor
//creates a BinTree by copying from an already created BinTree
//Preconditions: BinTree argument must already be defined somewhere
//Postconditions: BinTree copy is created
BinTree::BinTree(const BinTree& source)
{
    *this = source;
}

//---------------------------------------------------------------------------
//destructor
//assists in deallocating the BinTree object and all its elements
//Preconditions: BinTree must be instantiated before calling destructor
//Postconditions: BinTree is deleted
BinTree::~BinTree()
{
    makeEmpty();
}

//---------------------------------------------------------------------------
//operator ==
//overloaded equals operator
//Preconditions: both BinTrees must exist in advance
//Postconditions: returns true if both BinTrees are equal: false otherwise
BinTree& BinTree::operator=(const BinTree& source)
{
    //check whether tree is being assigned to itself
    if (this == &source)
    {
        return *this;
    }

    //delete elements from "this" tree
    makeEmpty();
    
    //check whether source tree is empty
    if (source.isEmpty())
    {
        return *this;
    }

    //start copying from source tree to "this" tree
    root = copy(source.root, this->root);

    return *this;
}

//copy
//helper for overloaded operator ==
//copies from the source node to the destination node including children
BinTree::Node* BinTree::copy(Node* source, Node* dest)
{
    //if source node is empty, dest node should also be empty
    if (source == nullptr)
    {
        dest = nullptr;
    }
    else
    {
        //copy the root node
        dest = new Node;
        
        if (source->data != nullptr)
        {
            NodeData* newData = new NodeData;
            *newData = *source->data;
            dest->data = newData;
        }

        //copy the left subtree
        dest->left = copy(source->left, dest->left);

        //copy the right subtree
        dest->right = copy(source->right, dest->right);
    }

    //return the value of dest node
    return dest;
}

//---------------------------------------------------------------------------
//operator ==
//overloaded equals operator
//Preconditions: both BinTrees must exist in advance
//Postconditions: returns true if both BinTrees are equal: false otherwise
bool BinTree::operator==(const BinTree& other) const
{
    //check whether trees have the same memory location
    if (this == &other)
    {
        return true;
    }
    else
    {
        return compareTrees(this->root, other.root);
    }
}

//compareTrees()
//helper function for overloaded operator ==
//checks whether two nodes and their children are equal
bool BinTree::compareTrees(Node* first, Node* second) const
{
    //check whether both trees are null. This means that they are equal
    if (first == nullptr && second == nullptr)
    {
        return true;
    }

    //one of the two trees is null, not both -> they are not equal
    else if (first == nullptr || second == nullptr)
    {
        return false;
    }

    else //both trees are not null and need to be compared further
    {
        //compare the roots
        bool equalRoots = (*(first->data) == *(second->data));

        //compare the left subtrees
        bool leftSubtreesEqual = compareTrees(first->left, second->left);

        //compare the right subtrees
        bool rightSubtreesEqual = compareTrees(first->right, second->right);

        return equalRoots && leftSubtreesEqual && rightSubtreesEqual;
    }
}

//---------------------------------------------------------------------------
//operator !=
//overloaded not equals operator
//Preconditions: both BinTrees must exist in advance
//Postconditions: returns tree if both BinTrees are not equal
bool BinTree::operator!=(const BinTree& other) const
{
    return !(*this == other);
}

//---------------------------------------------------------------------------
//retrieve()
//retrieves a node from the tree and provides a pointer to it
//Preconditions: two arguments must be provided
//Postconditions: returns true if the node could be retrieved
bool BinTree::retrieve(const NodeData& target, NodeData*& actual) const
{
    return retrieveHelper(target, actual, root);
}

bool BinTree::retrieveHelper(const NodeData& target, NodeData*& actual, BinTree::Node* root) const
{
    if (root != nullptr && root->data != nullptr)
    {
        //check whether target is at the root
        if (target == *(root->data))
        {
            //assign the actual to point to the root's data
            actual = root->data;
            return true;
        }

        //search the left subtree if target is less than root
        if (target < *(root->data))
        {
            return retrieveHelper(target, actual, root->left);
        }

        //search the right subtree if target is greater than root
        if (target > *(root->data))
        {
            return retrieveHelper(target, actual, root->right);
        }
    }

    //root->data is a null pointer
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
bool BinTree::insert(NodeData* ND) {
    bool inserted = false;                    // whether inserted yet

    if (isEmpty()) {
        root = new Node;
        root->data = ND;
        root->left = nullptr;
        root->right = nullptr;
        inserted = true;
    }
    else {
        Node* current = root;                     // walking pointer
        
        // Traverse tree; if item is less than current item, insert in 
        // left subtree, otherwise insert in right subtree
        while ( !inserted &&
                (current != nullptr) &&
                (current->data != nullptr)) {

            if (*ND < *current->data) {
                if (current->left == nullptr) {     // insert left
                    current->left = new Node;
                    current->left->data = ND;
                    current->left->left = nullptr;
                    current->left->right = nullptr;
                    inserted = true;
                }
                else
                    current = current->left;         // one step left
            }
            else if (*ND > *current->data) {
                if (current->right == nullptr) {    // insert right
                    current->right = new Node;
                    current->right->data = ND;
                    current->right->left = nullptr;
                    current->right->right = nullptr;
                    inserted = true;
                }
                else
                {
                    current = current->right;        // one step right
                }
            }
            else if (*ND == *current->data) {
                current = nullptr; // exists
            }
            else {
                current = nullptr; // unknown
            }
        }
    }

    return inserted;
}

//---------------------------------------------------------------------------
//remove()
//removes and fills in a pointer to the desired node
//Preconditions: two arguments must be provided
//Postconditions: returns true if the node was removed successfully
bool BinTree::remove(const NodeData& target, NodeData*& actual)
{
    root = removeHelper(target, actual, root);
    return (actual != nullptr);
}

BinTree::Node* BinTree::removeHelper(const NodeData& target, NodeData*& actual, Node* root)
{
    //cannot delete from an empty tree
    if (root == nullptr)
    {
        actual = nullptr;
        return root;
    }

    //keep track of the current node
    NodeData current = *(root->data);

    //check right subtree if target is greater than current node
    if (target > current)
    {
        root->right = removeHelper(target, actual, root->right);
    }

    //check left subtree if target is less than current node
    else if (target < current)
    {
        root->left = removeHelper(target, actual, root->left);
    }

    //copy node into "actual" and delete it if the target is equal to the current node
    else
    {
        //copying
        actual = new NodeData();
        *actual = *root->data;

        //deleting
        root = removeNode(root);
    }

    return root;
}

//removeNode
//helper function for removeHelper
//removes and returns a particular node and rejoins the tree
BinTree::Node* BinTree::removeNode(Node*& node)
{
    Node* temp;
    
    //node is a leaf
    if (node->left == nullptr && node->right == nullptr)
    {
        temp = nullptr;
    }
    else if (node->left != nullptr && node->right != nullptr)
    {
        //find predecessor
        Node* parent;
        temp = predecessor(node, parent);
        if (node->right != temp)
        {
            temp->right = node->right;
        }
        if (node->left != temp)
        {
            temp->left = node->left;
        }
        parent->right = nullptr;
    }

    //node has a left child
    else if (node->left != nullptr)
    {
        temp = node->left;
    }

    //node has a right child
    else
    {
        temp = node->right;
    }

    delete node->data;
    delete node;
    node = nullptr;
    return temp;
}

//predecessor
//helper function for removeNode
//retrieves the max element in the left child of a particular node 
BinTree::Node* BinTree::predecessor(Node* root, Node*& parent) const
{
    Node* subtreeRoot = root;

    //find the left child of the given node
    if (root != nullptr)
    {
        parent = root;
        subtreeRoot = root->left;

        //find max node in tree with subtreeRoot as the root
        while (subtreeRoot->right != nullptr)
        {
            parent = subtreeRoot;
            subtreeRoot = subtreeRoot->right;
        }
    }

    return subtreeRoot;
}

//---------------------------------------------------------------------------
//getSibling()
//finds the other node that has the same parent as the provided node
//Preconditions: two arguments must be provided
//Postconditions: returns true if the sibling could be found
bool BinTree::getSibling(const NodeData& data, NodeData& copy) const
{
    Node* sibling = getSiblingHelper(root, data);
    if (sibling != nullptr)
    {
        copy = *sibling->data;
    }
    
    return sibling != nullptr;
}

BinTree::Node* BinTree::getSiblingHelper(Node* node, NodeData key) const
{
    //no sibling exists for a null node or the root of a binary tree
    if (node == nullptr || *node->data == key)
    {
        return nullptr;
    }

    //return right node if the left node contains the key
    if (node->left != nullptr && *(node->left)->data == key)
    {
        return node->right;
    }

    //return left node if the right node contains the key
    if (node->right != nullptr && *(node->right)->data == key)
    {
        return node->left;
    }

    else //key does not exist in either children
    {
        //try finding a sibling within the left subtree with the key
        Node* n = getSiblingHelper(node->left, key);

        //check whether key exists there
        if (n != nullptr)
        {
            return n;
        }

        //otherwise, check the right subtree
        n = getSiblingHelper(node->left, key);

        //nothing further can be done -> return even if null
        return n;
    }
}

//---------------------------------------------------------------------------
//getParent()
//finds the parent of a particular node if it exists
//Preconditions: two arguments must be provided
//Postconditions: returns true if the parent could be retrieved
bool BinTree::getParent(const NodeData& data, NodeData& copy) const
{
    Node* parent = getParentHelper(root, data);

    if (parent != nullptr)
    {
        copy = *parent->data;
    }

    return parent != nullptr;
}

BinTree::Node* BinTree::getParentHelper(Node* node, NodeData key) const
{
    //no parent exists for a null node or the root of a binary tree
    if (node == nullptr || *node->data == key)
    {
        return nullptr;
    }

    //return node if either right or left child matches the key
    bool leftMatches = node->left != nullptr && *(node->left)->data == key;
    bool rightMatches = node->right != nullptr && *(node->right)->data == key;
    if (leftMatches || rightMatches)
    {
        return node;
    }

    else //key does not exist in either child node
    {
        //try finding the parent within the left subtree
        Node* n = getParentHelper(node->left, key);

        //check whether key exists there
        if (n != nullptr)
        {
            return n;
        }

        //otherwise, check the right subtree
        n = getParentHelper(node->left, key);

        //nothing further can be done -> return even if null
        return n;
    }
}

//---------------------------------------------------------------------------
//isEmpty()
//determines whether the BinTree is empty
//Preconditions: none
//Postconditions: returns true if the root pointer is null
bool BinTree::isEmpty() const
{
    return (root == nullptr);
}

//---------------------------------------------------------------------------
//bstreeToArray()
//transfers elements from the tree to the provided array (in order)
//Preconditions: array size is at least 100
//Postconditions: BinTree is empty, and array argument contains elements
void BinTree::bstreeToArray(NodeData* arr[])
{
    //determine array size
    int i = 0;
    bstreeToArrayHelper(root, arr, i);

    //empty the tree
    makeEmpty();
}

//arrayToBSTree()
//creates a balanced tree from the provided array
//Preconditions: array must be SORTED
//Postconditions: array contains null pointers, and tree contains elements
void BinTree::bstreeToArrayHelper(Node* node, NodeData* arr[], int& i)
{
    // base case: do not do anything if node is null
    if (node == nullptr) {  
        return;
    }

    //add left subtree data to the array
    bstreeToArrayHelper(node->left, arr, i);   

    //add root node data of tree to the array
    arr[i] = new NodeData;
    *arr[i] = *node->data;
    i++;

    //add right subtree data to the array
    bstreeToArrayHelper(node->right, arr, i);
}


//arrayToBSTree()
//creates a balanced tree from the provided array
//Preconditions: array must be SORTED
//Postconditions: array contains null pointers, and tree contains elements
void BinTree::arrayToBSTree(NodeData* arr[])
{
    //empty current tree
    makeEmpty();

    //determine size of arr
    int size = 0;
    while (arr[size] != nullptr)
    {
        size++;
    }

    //convert array to binary search tree
    root = arrayToBSTreeHelper(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        delete arr[i];
    }
}


BinTree::Node* BinTree::arrayToBSTreeHelper(NodeData* arr[], int left, int right)
{
    //return null value if the left index exceeds the right
    if (left > right) {
        return nullptr;
    }

    // Get the middle element and make it root
    int mid = (left + right) / 2;

    Node* node = new Node();
    node->data = new NodeData;
    *node->data = *arr[mid];
    node->left = nullptr;
    node->right = nullptr;

    // create the left subtree and attach to node
    node->left = arrayToBSTreeHelper(arr, left, mid - 1);

    // create the right subtree and attach to node
    node->right = arrayToBSTreeHelper(arr, mid + 1, right);

    //return the node
    return node;
}

//---------------------------------------------------------------------------
// displaySideways()
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
//makeEmpty()
//deallocates all the nodes and sets the root to null
//Preconditions: none
//Postconditions: tree is empty
void BinTree::makeEmpty()
{
    if (root != nullptr)
    {
        root = makeEmptyHelper(root);
    }
}

BinTree::Node* BinTree::makeEmptyHelper(Node* root) //helper for MakeEmpty()
{
    //empty the left subtree
    if (root->left != nullptr)
    {
        root->left = makeEmptyHelper(root->left);
    }

    //empty the right subtree
    if (root->right != nullptr)
    {
        root->right = makeEmptyHelper(root->right);
    }

    //empty the root
    delete root->data;
    root->data = nullptr;
    delete root;
    root = nullptr;

    return root;
}

//---------------------------------------------------------------------------
//operator <<
//overloaded output stream operator
//Preconditions: BinTree being outputted must exist in advance
//Postconditions: BinTree elements are posted "in order." 
ostream& operator<<(ostream& stream, const BinTree& tree)
{
    //keep track of the root of the tree
    BinTree::Node* root = tree.root;

    //inorder traversal
    tree.inorder(stream, root);

    //end with a blank and endl statement
    stream << " " << endl;

    return stream;
}

void BinTree::inorder(ostream& stream, Node* root) const //helper for <<
{
    //for nodes that are not null
    if (root != nullptr)
    {
        //display left subtree
        inorder(stream, root->left);
        
        //display root node
        stream << *(root->data) << " ";

        //display right subtree
        inorder(stream, root->right);
    }
}


