//---------------------------------------------------------------------------
// class IntSet
// Developer: Yash Varde
//---------------------------------------------------------------------------
// ADT IntSet: a set of positive integers (zero inclusive)
// -- can calculate intersection (*), union (+), and difference (-) of sets
// -- is able to manage memory when assigning one int set to another
// -- allows for users to input values from console to create IntSet.
// 
// 
// Implementation and Assumptions:
// -- inputs are only integers
// -- int set is dynamically allocated
// -- in <<, integers are preceded by a space and followed by a comma
// -- in >>, integers are expected (but gives output for chars as well)
// -- user can input a maximum of 5 integers for instantiating the int set
// -- using -1 at the end closes an input stream and instantiates the intset
// -- size is the number of elements in the int set array
//---------------------------------------------------------------------------
#ifndef INTSET_H
#define INTSET_H

#include <iostream>
#include <cmath>
using namespace std;

class IntSet
{ 
    // operator +
    // Overloaded adding operator. Returns the union of two IntSets.
    // Preconditions: the IntSets' array pointers must not be null or dangling
    // Postconditions: the IntSet parameters remain unchanged
    friend IntSet operator + (const IntSet&, const IntSet&);  

    // operator *
    // Overloaded multiply operator. Returns the intersection of two IntSets.
    // Preconditions: the IntSets' array pointers must not be null or dangling
    // Postconditions: the IntSet parameters remain unchanged
    friend IntSet operator * (const IntSet&, const IntSet&);    

    // operator -
    // Overloaded minus operator. Returns elements in first and not in second
    // Preconditions: the IntSets' array pointers must not be null or dangling
    // Postconditions: the IntSet parameters remain unchanged
    friend IntSet operator - (const IntSet&, const IntSet&);

    // operator >>
    // Overloaded input operator for IntSet. Inputs values into the int set.
    // Preconditions: the IntSet reference must already be declared.
    // Postconditions: the IntSet contains the ints that were input
    friend istream& operator >> (istream&, IntSet&);

    // operator <<
    // Overloaded output operator for IntSet. Outputs values within int set.
    // Preconditions: the IntSet's array pointer must not be null or dangling.
    // Postconditions: the IntSet parameter remains unchanged
    friend ostream& operator << (ostream&, const IntSet&);

public:
    // Constructor with int parameters
    // Allows for up to five int arguments to be inserted by user.
    // Preconditions: only integers should be entered to work properly.
    // Postconditions: an IntSet object containing the ints is instantiated.
    IntSet(int = -1, int = -1, int = -1, int = -1, int = -1);

    // Copy constructor
    // Deep copy of the IntSet object
    // Preconditions: IntSet object must be declared elsewhere in advance.
    // Postconditions: IntSet argument remains unchanged
    IntSet(const IntSet&);

    // Destructor
    // Preconditions: IntSet exists on the heap
    // Postconditions: Ints are cleared, size is set to 0
    ~IntSet();

    // operator =
    // Overloaded assignment operator
    // Assigns one IntSet to another by doing a deep copy
    // Preconditions: IntSet exists on the heap
    // Postconditions: "this" obtains the values of the IntSet parameter
    IntSet& operator = (const IntSet&);

    // operator +=
    // modifies current object to be the union of itself and the other
    // Preconditions: both IntSets do not have null array pointers
    // Postconditions: "this" IntSet becomes the union set of the two
    IntSet& operator += (const IntSet&);

    // operator *=
    // modifies current object to be the intersection of itself and the other
    // Preconditions: both IntSets do not have null array pointers
    // Postconditions: "this" IntSet becomes the intersection set of the two
    IntSet& operator *= (const IntSet&);

    // operator -=
    // modifies current object to be the difference of itself and the other
    // Preconditions: both IntSets do not have null array pointers
    // Postconditions: "this" IntSet becomes the difference set of the two
    IntSet& operator -= (const IntSet&);

    // operator ==
    // Checks whether two IntSets are equal
    // Preconditions: both IntSets do not have null array pointers
    // Postconditions: both IntSets remain unchanged
    bool operator == (const IntSet&) const;

    // operator !=
    // Checks whether two IntSets are not equal
    // Preconditions: both IntSets do not have null array pointers
    // Postconditions: both IntSets remain unchanged
    bool operator != (const IntSet&) const;

    // insert()
    // inserts the supplied integer into the set
    // Preconditions: IntSet arraySet must not be null
    // Postconditions: int value is added to the IntSet
    bool insert(int);

    // removes()
    // removes the supplied integer from the set
    // Preconditions: IntSet arraySet must not be null
    // Postconditions: int value is removed from the IntSet
    bool remove(int);

    // isEmpty()
    // checks whether the current IntSet is empty
    // Preconditions: IntSet must be initialized before usage
    // Postconditions: does not modify IntSet
    bool isEmpty() const;

    // isInSet()
    // Checks whether the given int is within the set
    // Preconditions: integer must be provided
    // Postconditions: does not modify IntSet
    bool isInSet(int) const;

    // isInSet()
    // Checks whether the given IntSet exists within the other set
    // Preconditions: both IntSets must already be instantiated
    // Postconditions: both IntSets remain unchanged
    bool containsSet(const IntSet&) const;

    // operator []
    // Retrieves an array element by using the IntSet interface
    // Preconditions: element is within bounds of the array set
    // Postconditions: does not modify the array set
    bool operator [] (int) const;

    // getSize()
    // Returns the size of the int set array
    // Preconditions: none
    // Postconditions: does not modify any data members
    int getSize() const;

private:
    bool* arraySet;                         //pointer to access the array set
    int size;                               //size of the array set

    // copy()
    // Copies all elements from the source IntSet to the dest IntSet
    // Preconditions: Destination IntSet pointer cannot be null
    // Postconditions: dest IntSet contains source IntSet elements
    IntSet& copy(const IntSet&, IntSet*);

    // isWithinRange()
    // Checks whether the provided integer is within range
    // Preconditions: IntSet array must not be null
    // Postconditions: returns true if the variable is within range
    bool isWithinRange(int) const;
};
#endif
