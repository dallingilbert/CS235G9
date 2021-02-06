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
#include <cassert>  // because I am paranoid

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
        void setElements(int numElements) { this->numElements = numElements; }
        void setCapacity(int numCapacity) { this->numCapacity = numCapacity; }

        // private member methods
        void resize(int newCap) throw(const char*);
        int capacity() const { return numCapacity; }

    public:
        // default constructor and non-default constructors
        set()
        {
            setCapacity(0);
            setElements(0);
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
        set& operator = (const set<T>& rhs) throw(const char*);

        // getters
        int size() const { return getBack() - getFront() + 1; }


        // public member methods 
        bool empty() const { return size() == 0; }
        void clear();
    };

    /*******************************************
     * set :: RESIZE
     *******************************************/
    template <class T>
    void set <T> ::resize(int newCap) throw(const char*)
    {
        T* newData;
        try
        {
            newData = new T[newCap];
        }
        catch (std::bad_alloc)
        {
            throw "Bad allocation";
        }

        int index = 0;
        for (int i = 0; i < size(); i++)
        {
            int index = (getFront() + i) % capacity();
            newData[i] = data[index];
        }

        delete[] data;
        data = newData;

        setCapacity(newCap);
    };

    /********************************************
     * set :: Clear
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void set <T> ::clear()
    {
        setFront(0);
        setBack(-1);
    };

    /*******************************************
     * set :: Assignment operator
     *******************************************/
    template <class T>
    set <T>& set <T> :: operator = (const set <T>& rhs) throw(const char*)
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
        else if (capacity() < rhs.size())
            resize(rhs.size());

        for (int i = rhs.getFront(); i <= rhs.getBack(); i++)
            push_back(rhs.data[iNormalized(i)]);

        return *this;
    }

    /*******************************************
     * set :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    set <T> ::set(const set <T>& rhs)
    {
        this->data = NULL;
        setElements(0);
        setCapacity(0);

        *this = rhs;
    }

    /**********************************************
     * set : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
    set <T> ::set(int numCapacity)
    {
        assert(numCapacity >= 0);

        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (numCapacity == 0)
        {
            cerr << "numCapacity is 0 -----" << endl;
            set();
            return;
        }

        // attempt to allocate
        data = new T[numCapacity];
        try
        {
            data = new T[numCapacity];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }


        // copy over the stuff
        setCapacity(numCapacity);
    }
};
#endif // SET_H
