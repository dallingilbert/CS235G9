/***********************************************************************
 * Header:
 *    set
 * Summary:
 *    This class contains the notion of a set: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the set, set, set, set, set, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       setue             : similar to std::set
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef SET_H
#define SET_H
#include <iostream>
#include <cstddef>
#include <cassert> // because I am paranoid

 // a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG
using namespace std;

namespace custom
{

    /************************************************
    * set
    * A class that holds stuff
    ***********************************************/
    template <class T>
    class set
    {
    private:
        // member variables
        T* data;
        int numElements;
        int numCapacity;

        // setters
        void setSize(int numElements) { this->numElements = numElements; }
        void setCapacity(int numCapacity) { this->numCapacity = numCapacity; }

        // private member methods
        void resize(int newCap);
        void addToEnd(const T& t);
        int findIndex(const T& t) const;


    public:
        // default constructor and non-default constructors
        set()
        {
            setCapacity(0);
            setSize(0);
            this->data = NULL;
        }
        set(int numCapacity);
        set(const set& rhs);

        // destructor
        ~set()
        {
             if (data != NULL)
              {
                  delete[] data;
              }
        }

        // overloaded operators
        set& operator=(const set<T>& rhs);
        set<T> operator && ( set<T>& rhs);
        set<T> operator || ( set<T>& rhs);
        set<T> operator - (set<T>& rhs);

        // getters
        int size() const { return numElements; }
        int capacity() const { return numCapacity; }
        
        // public member methods
        bool empty() const { return size() == 0; }
        void clear();
        void insert(const T& t);
        
        // the various iterator interfaces
        class iterator;
        iterator find(const T& t);
        void erase(iterator& it);

        // iterators
        iterator begin();
        iterator end();

        class const_iterator;
        const_iterator Cbegin() const;
        const_iterator Cend() const;
    };

    /**************************************************
    * SET :: ITERATOR
    * An iterator through a set
    *************************************************/
    template <class T>
    class set<T>::iterator
    {
    public:
        // constructors, destructors, and assignment operator
        iterator() : p(NULL) {}
        iterator(T* p) : p(p) {}
        iterator(const iterator& rhs) { *this = rhs; }
        iterator& operator=(const iterator& rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const iterator& rhs) const { return rhs.p != this->p; }
        bool operator==(const iterator& rhs) const { return rhs.p == this->p; }

        // dereference operator
        T& operator*() { return *p; }
        const T& operator*() const { return *p; }

        // prefix increment
        iterator& operator++()
        {
            p++;
            return *this;
        }

        // postfix increment
        iterator operator++(int postfix)
        {
            iterator tmp(*this);
            p++;
            return tmp;
        }

    private:
        T* p;
    };

    /**************************************************
    * SET :: CONST_ITERATOR
    * An iterator through array
    *************************************************/
    template <class T>
    class set<T>::const_iterator
    {
    public:
        // constructors, destructors, and assignment operator
        const_iterator() : p(NULL) {}
        const_iterator(T* p) : p(p) {}
        const_iterator(const const_iterator& rhs) { *this = rhs; }
        const_iterator& operator=(const const_iterator& rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const const_iterator& rhs) const { return rhs.p != this->p; }
        bool operator==(const const_iterator& rhs) const { return rhs.p == this->p; }

        // dereference operator
        const T& operator*() { return *p; }
        const T& operator*() const { return *p; }

        // prefix increment
        const_iterator& operator++()
        {
            p++;
            return *this;
        }

        // postfix increment
        const_iterator operator++(int postfix)
        {
            iterator tmp(*this);
            p++;
            return tmp;
        }

    private:
        T* p;
    };

    /********************************************
    * SET :: BEGIN
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename set<T>::iterator set<T>::begin()
    {
        return iterator(data);
    }

    /********************************************
    * SET :: END
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename set<T>::iterator set<T>::end()
    {
        return iterator(data + numElements);
    }

    /********************************************
    * SET :: CBEGIN
    * Returns the beginning of our array
    ********************************************/
    template <class T>
    typename set<T>::const_iterator set<T>::Cbegin() const
    {
        return const_iterator(data);
    }

    /********************************************
    * SET :: CEND
    * Returns the end of our array
    ********************************************/
    template <class T>
    typename set<T>::const_iterator set<T>::Cend() const
    {
        return const_iterator(data + numElements);
    }

    /*******************************************
     * SET :: RESIZE
     * Dynamically allocates new space for the 
     * additional items created for our set
     *******************************************/
    template <class T>
    void set<T>::resize(int newCap)
    {
        try
        {
            T* temp = new T[newCap];
            
            // copy data from old array to new array
            for (int i = 0; i < numElements; i++)
                temp[i] = data[i];

            delete[] data; // clear memory
            this-> data = temp;
            setCapacity(newCap); // increase capacity
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer a new buffer for set";
        }
    };

    /********************************************
   * SET :: ERASE
   * Note that you have to use "typename" before
   * the return value type
   ********************************************/
    template <class T>
    void set<T>::erase(set<T>::iterator& it)
    {
        int Eraser = findIndex(*it);
        if (data[Eraser] == *it)
        {
            for (int x = Eraser; x < size() - 1; x++)
                data[x] = data[x + 1];
                
            numElements--;
        }
    }

    /**********************************************
     * SET : FIND
     * Determines if a value is found within our 
     * set, if it is not found, return the end
     * iterator
     **********************************************/
    template <class T>
    typename set<T>::iterator set<T>::find(const T& t)
    {
        int index = findIndex(t);
        if (data[index] == t)
        {
           return iterator(data + index);
        }
        return end();
    }

    /********************************************
     * SET :: Clear
     * Empty our set and reset the size and
     * capacity
     ********************************************/
    template <class T>
    void set<T>::clear()
    {
        setSize(0);
        setCapacity(0);
        data = NULL;
    };

    /*******************************************
     * SET :: Assignment operator
     * Copies the data from one object to the
     * other
     *******************************************/
    template <class T>
    set<T>& set<T>::operator=(const set<T>& rhs)
    {
        if (numCapacity < rhs.numCapacity)
        {
            resize(rhs.numCapacity);
        }

        if (data == NULL)
        {
            try
            {
                setSize(rhs.size());
                setCapacity(rhs.capacity());
                data = new T[numCapacity];
            }
            catch (std::bad_alloc)
            {
                throw "ERROR: Unable to allocate buffer a new buffer for set";
            }
        }
        for (int i = 0; i < rhs.numElements; i++)
            data[i] = rhs.data[i];

        numElements = rhs.numElements;
        numCapacity = rhs.numCapacity;
        return *this;
    }

    /*******************************************
     * SET :: INTERSECT
     * Determine where values between two sets 
     * are intersecting
     *******************************************/
    template <class T>
    set<T> set<T>::operator && ( set<T>& rhs)
    {
        // initialize all member variables
        set<T> returnSet;
        int LHS = 0;
        int RHS = 0;
        
        while (LHS < size() && RHS < rhs.size())
        {
            if (data[LHS] == rhs.data[RHS])
            {
                returnSet.addToEnd(data[LHS]);
                LHS++, RHS++;
            }
            else if (data[LHS] < rhs.data[RHS])
                LHS++;
            else
                RHS++;
        }
        return returnSet;
    }

    /*******************************************
     * SET :: UNION operator
     * Determines where values between two sets
     * 
     *******************************************/
    template <class T>
    set<T> set<T>::operator || ( set<T>& rhs)
    {
        // initialize all member variables
        set<T> returnSet;
        int LHS = 0;
        int RHS = 0;
        
        while (LHS < size() || RHS < rhs.size())
        {
            if (LHS == size())
                returnSet.addToEnd(rhs.data[RHS++]);
            else if (RHS == rhs.size())
                returnSet.addToEnd(data[LHS++]);
            else if (data[LHS] == rhs.data[RHS])
            {
                returnSet.addToEnd(data[LHS++]);
                LHS++, RHS++;
            }
            else if (data[LHS] < rhs.data[RHS])
                returnSet.addToEnd(data[LHS++]);
            else
                returnSet.addToEnd(rhs.data[RHS++]);
        }
        return returnSet;
    }

    /*******************************************
     * SET :: DIFFERENCE operator
     *******************************************/
    template <class T>
    set<T> set<T>::operator - (set<T>& rhs)
    {
        // initialize all member variables
        set<T> returnSet;
        int LHS = 0;
        int RHS = 0;
        
        while (LHS < size() || RHS < rhs.size())
        {
            if (LHS == size())
                RHS++;
            else if (RHS == rhs.size())
                returnSet.addToEnd(data[LHS++]);
            else if (data[LHS] == rhs.data[RHS])
                LHS++, RHS++;
            else if (data[LHS] < rhs.data[RHS])
                returnSet.addToEnd(data[LHS++]);
            else
                RHS++;
        }
        return returnSet;
    }

    /*******************************************
     * SET :: ADDTOEND
     * Adds the passed in parameter to the end 
     * of our set
     *******************************************/
    template <class T>
    void set<T>::addToEnd(const T& t)
    {
        if (numCapacity == 0)
            resize(1);
        if (numElements == numCapacity)
            resize(numCapacity * 2);
            
        data[numElements++] = t;
    }

    /*******************************************
     * SET :: COPY CONSTRUCTOR
     * Copies all of the data using the assignment
     * operator
     *******************************************/
    template <class T>
    set<T>::set(const set<T>& rhs)
    {
        this->data = NULL;
        setSize(0);
        setCapacity(0);

        *this = rhs;
    }

    /**********************************************
     * SET : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
    set<T>::set(int numCapacity)
    {
        assert(numCapacity >= 0);
        this->data = NULL;

        setCapacity(numCapacity);
        
        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (numCapacity == 0)
        {
            cerr << "numCapacity is 0 -----" << endl;
            set();
            return;
        }

        // attempt to allocate
        T* data;
        try
        {
            data = new T[numCapacity];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }

        // copy over the stuff
        setSize(0);
    }

    /********************************************
    * SET :: INSERT
    * Inserts the passed in value into our set
    * at a specified index
    ********************************************/
    template <class T>
    void set<T>::insert(const T& t)
    {

        if (numCapacity == 0)
            resize(1);
        else if (size() == numCapacity)
            resize(numCapacity * 2);  
        else if (numElements == 0)
        {
            if (data == NULL)
            {
                try
                {
                    numCapacity = 1;
                    data = new T[numCapacity];
                }
                catch (std::bad_alloc)
                {
                        throw "ERROR: Unable to allocate buffer a new buffer for set";
                }
            }
            data[0] = t;
            numElements++;
            return;
        }
        int index = findIndex(t);
        if (data[index] != t)
        {
            int index = findIndex(t);
            for (int x = numElements - 1; x > index - 1; x--)
            {
                data[x + 1] = data[x];
            }
            data[index] = t;
            numElements++;
        }

    };

    /**********************************************
     * SET : FIND INDEX
     * Finds the index of a certain value within 
     * our set
     **********************************************/
    template <class T>
    int set<T>::findIndex(const T& t) const
    {
        int begin = 0;
        int end = size() - 1;

        while(begin <= end)
        {
            int result = (begin + end) / 2;
            if (t == data[result])
                return result;
            if (t < data[result])
                end = result - 1;
            else
                begin = result + 1;
        }
        return begin;
    }
};     // namespace custom
#endif // SET_H