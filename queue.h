/***********************************************************************
 * Header:
 *    Stacl
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       stack             : similar to std::stack
 *       array :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef STACK_H
#define STACK_H
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
    * stack
    * A class that holds stuff
    ***********************************************/
    template <class T>
    class stack
    {
    private:
        T* data;
        int num;
        int cap;
        void resize(int newCap) throw(const char*);
        void setSize(int num) { this->num = num; }
        void setCapacity(int cap) { this->cap = cap; }

    public:
        stack()
        {
            setCapacity(0);
            setSize(0);
            this->data = NULL;
        }
        stack(int cap);
        stack(const stack& rhs);
        ~stack()
        {
            if (data != NULL)
            {
                delete[] data;
            }
        }
        stack& operator = (const stack<T>& rhs) throw(const char*);
        int size() const { return num; }
        int capacity() const { return cap; }
        bool empty() const { return num == 0; }
        void clear();
        void push(const T& t);
        void pop();
        T& top();
        const T& top() const;
    };
    
    /*******************************************
     * STACK :: RESIZE
     *******************************************/
    template <class T>
    void stack <T> ::resize(int newCap) throw(const char*)
    {
        //delete[] data;
        T* newData;
        try
        {
            newData = new T[newCap];
        }
        catch (std::bad_alloc)
        {
            throw "Bad allocation";
        }

        for (int i = 0; i < capacity() && i < newCap; i++)
            newData[i] = data[i];

        if (data != NULL)
        {
            delete[] data;
        }

        data = newData;

        if (newCap < capacity())
        {
            setSize(newCap);
        }

        setCapacity(newCap);

    };

    /********************************************
    * STACK :: Top
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    T& stack <T> ::top()
    {
        if (!empty())
        {
            return data[size() - 1];
        }
        else if (empty())
        {
            throw "ERROR: Unable to reference the element from an empty Stack";
        }
    };

    /********************************************
    * STACK :: Top
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    const T& stack <T> ::top() const
    {
        if (!empty())
        {
            return data[size() - 1];
        }
        else
        {
            throw "ERROR: Unable to reference the element from an empty Stack\n";
        }
    };

    /********************************************
    * STACK :: Push
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void stack <T> ::push(const T& t)
    {
        if (capacity() == 0)
        {
            resize(1);
        }
        if (size() == capacity())
        {
            resize(capacity() * 2);
        }
        data[num++] = t;
        //std::cout << "Num: " << size() << endl;
    };

    /********************************************
     * STACK :: Clear
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void stack <T> ::clear()
    {
        num = 0;
    };

    /********************************************
     * STACK :: Pop
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void stack <T> ::pop()
    {
        if (!empty())
        {
            num--;
        }
    };

    /*******************************************
     * STACK :: Assignment CONSTRUCTOR
     *******************************************/
    template <class T>
    stack <T>& stack <T> :: operator = (const stack <T>& rhs) throw(const char*)
    {
        // we can only copy arrays of equal size. stacks are not this way!
        if (data != NULL)
        {
            delete[] data;
        }
        data = NULL;
        num = 0;
        cap = 0;
        if (rhs.cap == 0)
        {
            return *this;
        }
        try
        {
            data = new T[rhs.cap];
        }
        catch (std::bad_alloc)
        {
            throw "Bad allocation";
        }
        cap = rhs.cap;
        num = rhs.num;
        for (int i = 0; i < cap; i++)
            data[i] = rhs.data[i];

        return *this;
    }

    /*******************************************
     * STACK :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    stack <T> ::stack(const stack <T>& rhs)
    {
        data = NULL;
        num = 0;
        cap = 0;

        *this = rhs;

    }

    /**********************************************
     * STACK : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
    stack <T> ::stack(int cap)
    {
        assert(cap >= 0);

        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (cap == 0)
        {
            cerr << "cap is 0 -----" << endl;
            this->num = 0;
            this->cap = 0;
            this->data = NULL;
            return;
        }

        // attempt to allocate
        data = new T[cap];
        try
        {
            data = new T[cap];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }


        // copy over the stuff
        this->cap = cap;
        this->num = 0;


    }

};
#endif // STACK_H

