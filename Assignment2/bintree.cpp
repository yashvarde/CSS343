#include "bintree.h"

//---------------------------------------------------------------------------
BinTree::BinTree()
{
    root = nullptr;
}

//---------------------------------------------------------------------------
BinTree::BinTree(const BinTree& source)
{
    *this = source;
}

//---------------------------------------------------------------------------
BinTree::~BinTree()
{
    makeEmpty();
}

//---------------------------------------------------------------------------
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
    copy(source.root, this->root);

    return *this;
}

//---------------------------------------------------------------------------
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
        bool equalRoots = (first->data == second->data);

        //compare the left subtrees
        bool leftSubtreesEqual = compareTrees(first->left, second->left);

        //compare the right subtrees
        bool rightSubtreesEqual = compareTrees(first->right, second->right);

        return equalRoots && leftSubtreesEqual && rightSubtreesEqual;
    }
}

//---------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree& other) const
{
    return !(*this == other);
}

//---------------------------------------------------------------------------
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
bool BinTree::insert(NodeData* dataptr) {
    Node* ptr = new Node;
    NodeData invalid("");

    if (ptr == nullptr)
    {
        delete ptr;
        ptr = nullptr;
        return false;                // out of memory
    }
    
    ptr->data = dataptr;
    ptr->left = ptr->right = nullptr;

    if (isEmpty()) {
        root = ptr;
    }
    else {
        if (root->data == nullptr)
        {
            delete ptr;
            ptr = nullptr;
            return false;                //empty node invalid
        }

        Node* current = root;                     // walking pointer
        bool inserted = false;                    // whether inserted yet

        // Traverse tree; if item is less than current item, insert in 
        // left subtree, otherwise insert in right subtree
        bool nodeCheck = current != nullptr && ptr != nullptr;
        bool nodeDataCheck = current->data != nullptr && ptr->data != nullptr;

        while (!inserted && nodeCheck && nodeDataCheck) {
            if (*ptr->data < *current->data) {
                if (current->left == nullptr) {     // insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;         // one step left
            }
            else if (*ptr->data > *current->data) { 
                if (current->right == nullptr) {    // insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                {
                    current = current->right;        // one step right
                }
            }
            else //*ptr->data == *current->data
            {
                return false;
            }

            //update whether the new pointers are valid for the while loop
            nodeCheck = current != nullptr && ptr != nullptr;
            nodeDataCheck = current->data != nullptr && ptr->data != nullptr;
        }
    }
    return true;
}

//---------------------------------------------------------------------------
bool BinTree::remove(const NodeData& target, NodeData*& actual)
{
    return removeHelper(target, actual, root);
}

BinTree::Node* BinTree::removeHelper(const NodeData& target, NodeData*& actual, Node* root)
{
    //cannot delete from an empty tree
    if (root == nullptr)
    {
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
        return removeNode(root);
    }

    return root;
}

BinTree::Node* BinTree::removeNode(Node*& node)
{
    Node* temp;

    //node is a leaf
    if (node->left == nullptr && node->right == nullptr)
    {
        temp = nullptr;
    }

    //node has a left child
    else if (node->left != nullptr)
    {
        temp = node->left;
    }

    //node has a right child
    else if (node->right != nullptr)
    {
        temp = node->right;
    }
    
    //node has two children
    else
    {
        //find predecessor
        temp = predecessor(root);
    }

    delete node->data;
    delete node;
    node = nullptr;
    return temp;
}

BinTree::Node* BinTree::predecessor(Node* root) const
{
    Node* subtreeRoot = root;

    //find the left child of the given node
    if (root != nullptr)
    {
        subtreeRoot = root->left;

        //find max node in tree with subtreeRoot as the root
        while (subtreeRoot->right != nullptr)
        {
            subtreeRoot = subtreeRoot->right;
        }
    }

    return subtreeRoot;
}

//---------------------------------------------------------------------------
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
bool BinTree::isEmpty() const
{
    return (root == nullptr);
}

//---------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arr[])
{
    //determine array size
    bstreeToArrayHelper(root, arr, 0);
}

void BinTree::bstreeToArrayHelper(Node* node, NodeData* arr[], int i)
{
    // base case: do not do anything if node is null
    if (node == nullptr) {  
        return;
    }

    //add left subtree data to the array
    bstreeToArrayHelper(node->left, arr, i);   

    //add root node data of tree to the array
    arr[i++] = node->data;          

    //add right subtree data to the array
    bstreeToArrayHelper(node->right, arr, i);  
}

//---------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[])
{
    //determine size of arr
    int size = sizeof(*arr) / sizeof(NodeData*);

    //convert array to binary search tree
    arrayToBSTreeHelper(root, arr, 0, size - 1);
}

void BinTree::arrayToBSTreeHelper(Node* node, NodeData* arr[], int left, int right)
{
    //find mid value of array
    int midIndex = (left + right) / 2;
    NodeData* midValue = arr[midIndex];

    if (midValue != nullptr)
    {
        //null node -> insert midValue
        if (node == nullptr)
        {
            node = new Node;
            node->data = new NodeData(*midValue);
            return;
        }

        //keep track of current node data in tree
        NodeData current = *(node->data);

        //make midValue the left subtree of current, and set right as midIndex - 1 
        if (*midValue < current)
        {
            node->left = new Node;
            node->left->data = new NodeData(*midValue);
            arrayToBSTreeHelper(node->left, arr, left, midIndex - 1);
            return;
        }

        //make midValue the right subtree of current, and set left as midIndex + 1 
        if (*midValue > current)
        {
            node->right = new Node;
            node->right->data = new NodeData(*midValue);
            arrayToBSTreeHelper(node->left, arr, midIndex + 1, right);
            return;
        }
    }
}

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
        dest = new Node();
        dest->data = new NodeData;

        if (source != nullptr)
        {
            if (source->data != nullptr)
            {
                *(dest->data) = *(source->data);
            }
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
void BinTree::makeEmpty()
{
    makeEmptyHelper(root);
    root = nullptr;
}

BinTree::Node* BinTree::makeEmptyHelper(Node* root)
{
    //return root if it is already null
    if (root == nullptr)
    {
        return root;
    }
    else
    {
        //empty the left subtree
        root->left = makeEmptyHelper(root->left);

        //empty the right subtree
        root->right = makeEmptyHelper(root->right);

        //empty the root
        delete root->data;
        delete root;
        root = nullptr;
        return root;
    }
}

//---------------------------------------------------------------------------
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

void BinTree::inorder(ostream& stream, Node* root) const
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


