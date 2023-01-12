#include "intset.h"

//---------------------------------------------------------------------------

IntSet::IntSet(int a, int b, int c, int d, int e)
{
    //find maximum value of all arguments
    int max = 0;
    max = std::max(a, b);
    max = std::max(max, c);
    max = std::max(max, d);
    max = std::max(max, e);
    
    //create a new array with a size of (max + 1)
    size = max + 1;
    arraySet = new bool[size];

    //initialize all values to false (empty set)
    for (int i = 0; i < size; i++)
    {
        arraySet[i] = false;
    }

    //attempt to insert each of the arguments
    insert(a);
    insert(b);
    insert(c);
    insert(d);
    insert(e);
}

//---------------------------------------------------------------------------
IntSet::IntSet(const IntSet& source)
{
    //create a new array with same size as the source
    int size = source.getSize();
    arraySet = new bool[size];

    //initialize all values to false (empty set)
    for (int i = 0; i < size; i++)
    {
        arraySet[i] = false;
    }

    //call the assignment operator
    *this = source;
}

IntSet::~IntSet()
{
    delete[] arraySet;
    arraySet = nullptr;
    size = 0;
}

//---------------------------------------------------------------------------

IntSet& IntSet::operator=(const IntSet& source)
{
    //check whether source is being assigned to itself
    if (this == &source)
    {
        return *this;
    }

    //nullify the array set pointer
    if (arraySet != nullptr)
    {
        //delete current array set if it contains elements
        if (size > 0)
        {
            delete[] arraySet;
        }
        arraySet = nullptr;
    }
    
    //allocate array to be equal size of source 
    int sourceSize = source.getSize();
    size = sourceSize;
    arraySet = new bool[size];

    //copy element by element
    for (int i = 0; i < sourceSize; i++)
    {
        arraySet[i] = source[i];
    }

    //return this int set
    return *this;
}

//---------------------------------------------------------------------------

IntSet& IntSet::operator+=(const IntSet& other)
{
    *this = *this + other;
    return *this;
}

//---------------------------------------------------------------------------

IntSet& IntSet::operator*=(const IntSet& other)
{
    *this = (*this) * other;
    return *this;
}

//---------------------------------------------------------------------------

IntSet& IntSet::operator-=(const IntSet& other)
{
    *this = (*this) - other;
    return *this;
}

//---------------------------------------------------------------------------

bool IntSet::operator==(const IntSet& other)
{
    //check whether the memory locations are equal
    if (this == &other)
    {
        return true;
    }

    //check whether both intsets contain each other. Contents are equal then
    if (this->containsSet(other) && other.containsSet(*this))
    {
        return true;
    }

    //anything else means that the sets are not equal
    return false;
}

//---------------------------------------------------------------------------

bool IntSet::operator!=(const IntSet& other)
{
    return !(*this == other);
}

//---------------------------------------------------------------------------

bool IntSet::insert(int x)
{
    //check whether int is within range
    if (isWithinRange(x))          
    {
        //set given index to true
        arraySet[x] = true;
        return true;
    }

    //check whether int exceeds limits
    else if (x >= size)      
    {
        //create a new array with size (x + 1)
        bool* newArraySet = new bool[x + 1];

        //copy values from existing array into new array 
        for (int i = 0; i < size; i++)
        {
            newArraySet[i] = arraySet[i];
        }

        //copy new int into new array 
        newArraySet[x] = true;

        //deallocate memory; reassign array pointer and size
        delete[] arraySet;
        arraySet = newArraySet;
        size += (x + 1 - size);
        return true;
    }

    //int argument might be negative or invalid
    return false;   
}

//---------------------------------------------------------------------------

bool IntSet::remove(int x)
{
    //check whether array contains elements and given index is in set
    if (!isEmpty() && isInSet(x))
    {
        //check whether x is the maximum value
        if (x == size - 1)
        {
            //search for second largest int in array
            int newMax = 0;
            for (int i = size - 1; i >= 0; i--)
            {
                if (i != x && arraySet[i])
                {
                    newMax = i;
                    break;
                }
            }

            //create a new array with size (newMax + 1)
            size = newMax + 1;
            bool* newArraySet = new bool[size];
            

            //copy values from existing array into new array 
            for (int i = 0; i < size; i++)
            {
                newArraySet[i] = arraySet[i];
            }

            //deallocate memory and reassign array pointer
            delete[] arraySet;
            arraySet = newArraySet;
            return true;
        }

        //x can be easily removed without changing the size of the set
        arraySet[x] = false;
        return true;
    }

    //array is empty, or the value does not exist within set
    return false;
}

//---------------------------------------------------------------------------

bool IntSet::isEmpty() const
{
    return size == 0;
}

//---------------------------------------------------------------------------

bool IntSet::isInSet(int x) const
{
    //must be within the range of the set, and the given index must be true
    return isWithinRange(x) && arraySet[x];
}

//---------------------------------------------------------------------------

bool IntSet::containsSet(const IntSet& subset) const
{
    //set cannot contain a larger set
    if (size < subset.getSize())
    {
        return false;
    }
    
    //iterate through this set
    for (int i = 0; i < size; i++)
    {
        //not contained: an element in the subset is not within the superset
        if (!arraySet[i] && subset[i])
        {
            return false;
        }
    }

    //contains subset: all elements in the subset are within the superset
    return true;
}

//---------------------------------------------------------------------------

bool IntSet::operator[] (int x) const
{
    //return element if it is in the set.
    if (isWithinRange(x))
    {
        return arraySet[x];
    }
    
    //element is not in the set
    return false;
}

//---------------------------------------------------------------------------

int IntSet::getSize() const
{
    return size;
}

//---------------------------------------------------------------------------

IntSet& IntSet::copy(const IntSet& source, IntSet* dest)
{
    //have a variable for the source size
    int sourceSize = source.getSize();

    //copy elements one by one from source to dest
    for (int i = 0; i < sourceSize; i++)
    {
        // only copy if value is not already present in dest
        if (!dest->arraySet[i] && source[i])
        {
            dest->insert(i);
        }
    }

    //return reference to modified int set
    return *dest;
}

//---------------------------------------------------------------------------

bool IntSet::isWithinRange(int x) const
{
    //value must be an integer between 0 (included) and the size (excluded)
    return x >= 0 && x < size;
}

//---------------------------------------------------------------------------

IntSet operator+(const IntSet& first, const IntSet& second)
{
    //create a pointer to a new int set
    IntSet* retVal = new IntSet();

    //copy elements from first into retVal
    retVal->copy(first, retVal);

    //copy elements from second into retVal
    retVal->copy(second, retVal);
    
    //return IntSet
    return *retVal;
}

//---------------------------------------------------------------------------

IntSet operator*(const IntSet& first, const IntSet& second)
{
    //determine minimum of both IntSet sizes
    int firstSize = first.getSize();
    int secondSize = second.getSize();
    int minSize = std::min(firstSize, secondSize);

    //create a pointer to a new int set
    IntSet* retVal = new IntSet();

    //iterate up until minSize; both will contain values up until this size
    for (int i = 0; i < minSize; i++)
    {
        //add element only if it exists in both int sets
        if (first.isInSet(i) && second.isInSet(i))
        {
            retVal->insert(i);
        }
    }

    //return IntSet 
    return *retVal;
}

//---------------------------------------------------------------------------

IntSet operator-(const IntSet& first, const IntSet& second)
{
    //create a pointer to a new int set
    IntSet* retVal = new IntSet();

    //determine size of first and second array
    int firstSize = first.getSize();
    int secondSize = second.getSize();

    //iterate through first array 
    int i;
    for (i = 0; i < firstSize; i++)
    {
        //skip elements that do occur in the second
        if (i < secondSize && second[i])
        {
            continue;
        }

        //insert elements that do not occur in second
        retVal->insert(i);
    }
    retVal->size = i;
    //return IntSet
    return *retVal;
}

//---------------------------------------------------------------------------

istream& operator>>(istream& stream, IntSet& intSet)
{
    //keep inserting into int set as long as the stream contains input
    int x = 0;
    do
    {
        stream >> x;
        if (x != -1)
        {
            intSet.insert(x);
        }
    } 
    while (x != -1);

    return stream;
}

//---------------------------------------------------------------------------

ostream& operator<<(ostream& stream, const IntSet& intSet)
{
    //opening curly bracket
    int size = intSet.getSize();
    stream << "{";

    //space followed by each element of the set
    for (int i = 0; i < size; i++)
    {   
        //only true indexes will be added to stream
        if (intSet[i])
        {
            stream << " " << i;
        }
    }

    //closing curly bracket
    stream << "}" << "\n";

    return stream;
}

//---------------------------------------------------------------------------
