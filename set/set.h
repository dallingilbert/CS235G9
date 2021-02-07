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
        T *data;
        int numElements;
        int numCapacity;

        // setters
        void setSize(int numElements) { this->numElements = numElements; }
        void setCapacity(int numCapacity) { this->numCapacity = numCapacity; }

        // private member methods
        void resize(int newCap) throw(const char *);
        int findIndex(const T &t) const;

    public:
        // default constructor and non-default constructors
        set()
        {
            setCapacity(0);
            setSize(0);
            this->data = NULL;
        }
        set(int numCapacity);
        set(const set &rhs);

        // destructor
        ~set()
        {
            if (data != NULL)
            {
                delete[] data;
            }
        }

        // overloaded operators
        set &operator=(const set<T> &rhs) throw(const char *);

        // getters
        int size() const { return numElements; }

        // public member methods
        bool empty() const { return size() == 0; }
        void clear();
        void sort();
        void insert(const T& t)
        {
            data.sort();

            iInsert = findIndex(t);

            if (data[iInsert] != t)
            {
                for (int i = numElements; i < iInsert)
            }
        }

        iterator find(const T& t)
        {
            data.sort();

            iBegin = 0;
            iEnd = numElements - 1;

            while(iBegin <= iEnd)
            {
                iMiddle = (iBegin + iEnd) / 2;

                if (t == data[iMiddle])
                    return iMiddle;
                else if (t < data[iMiddle])
                    iEnd = iMiddle - 1;
                else
                    iBegin = iMiddle + 1;

                return numElements;
            }
        }

        // the various iterator interfaces
        class iterator;
        iterator begin() { return iterator(data); }
        iterator end();
    };

    /**************************************************
    * SET ITERATOR
    * An iterator through array
    *************************************************/
    template <class T>
    class set<T>::iterator
    {
    public:
        // constructors, destructors, and assignment operator
        iterator() : p(NULL) {}
        iterator(T *p) : p(p) {}
        iterator(const iterator &rhs) { *this = rhs; }
        iterator &operator=(const iterator &rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const iterator &rhs) const { return rhs.p != this->p; }
        bool operator==(const iterator &rhs) const { return rhs.p == this->p; }

        // dereference operator
        T &operator*() { return *p; }
        const T &operator*() const { return *p; }

        // prefix increment
        iterator &operator++()
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
        T *p;
    };

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

    /*******************************************
     * set :: RESIZE
     *******************************************/
    template <class T>
    void set<T>::resize(int newCap) throw(const char *)
    {
        try
        {
            T *arrayTemp = new T[newCap];
            for (int i = 0; i < numCapacity && i < newCap; i++)
                arrayTemp[i] = data[i];

            delete[] data;
            data = arrayTemp;
            setCapacity(newCap);
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer a new buffer for set";
        }
    };

    /********************************************
     * set :: Clear
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void set<T>::clear()
    {
        setSize(0);
        setCapacity(0);
    };

    /*******************************************
     * set :: Assignment operator
     *******************************************/
    template <class T>
    set<T> &set<T>::operator=(const set<T> &rhs) throw(const char *)
    {
        // initialize all member variables
        clear();

        if (data != NULL)
        {
            delete[] data;
            data = NULL;
        }

        if (rhs.numCapacity == 0)
        {
            return *this;
        }
        else if (numCapacity < rhs.size())
            resize(rhs.size());

        for (int i = 0; i < size(); i++)
            data[i] = rhs.data[i];

        return *this;
    }

    /*******************************************
     * set :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    set<T>::set(const set<T> &rhs)
    {
        this->data = NULL;
        setSize(0);
        setCapacity(0);

        *this = rhs;
    }

    /**********************************************
     * set : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
    set<T>::set(int numCapacity)
    {
        assert(numCapacity >= 0);
        this->data = NULL;

        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (numCapacity == 0)
        {
            cerr << "numCapacity is 0 -----" << endl;
            set();
            return;
        }

        // attempt to allocate
        T *data;
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
        setCapacity(numCapacity);
    }

    /**********************************************
     * set : FIND INDEX
     * Determines where 
     **********************************************/
    template <class T>
    int set<T>::findIndex(const T &t) const
    {
    }

    template <class T>
    void set<T>::sort() 
    {
        int pos = 1;
        for (int i = 0; i < numElements; i++)
        {
            T tempArray = data;
            if (tempArray[i] < tempArray[i + pos])
                data[i] = tempArray[i + pos]
            else 
                data[i] = tempArray[i];

            pos++;
        }

        for (int i = 0; i < numElements; i++)
        {
            cout << data[i] << endl;
        }
    }
};     // namespace custom
#endif // SET_H
