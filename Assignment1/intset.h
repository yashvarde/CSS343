#ifndef INTSET_H
#define INTSET_H

#include <iostream>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
// class IntSet
// ADT IntSet:
// 
// Implementation and Assumptions:
//---------------------------------------------------------------------------
class IntSet
{ 
    //arithmetic operators
    friend IntSet operator + (const IntSet&, const IntSet&);
    friend IntSet operator * (const IntSet&, const IntSet&);
    friend IntSet operator - (const IntSet&, const IntSet&);

    //stream operators
    friend istream& operator >> (istream&, IntSet&);
    friend ostream& operator << (ostream&, const IntSet&);

public:
    //constuctors
    IntSet(int = -1, int = -1, int = -1, int = -1, int = -1);
    IntSet(const IntSet&);

    //destructor
    ~IntSet();

    //assignment operator
    IntSet& operator = (const IntSet&);

    //arithmetic operators
    IntSet& operator += (const IntSet&);
    IntSet& operator *= (const IntSet&);
    IntSet& operator -= (const IntSet&);

    //comparison operators
    bool operator == (const IntSet&);
    bool operator != (const IntSet&);

    //modifier methods
    bool insert(int);
    bool remove(int);

    //informational methods/operators
    bool isEmpty() const;
    bool isInSet(int) const;
    bool containsSet(const IntSet&) const;
    bool operator [] (int) const;

    //getters
    int getSize() const;

private:
    //data members
    bool* arraySet;
    int size;

    //helper methods
    IntSet& copy(const IntSet&, IntSet&);
};
#endif
