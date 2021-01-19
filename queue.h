/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains the notion of a queue: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the queue, set, queue, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       queue             : similar to std::queue
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H
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
    * queue
    * A class that holds stuff
    ***********************************************/
    template <class T>
    class queue
    {
    private:
        T* data;
        int num;
        int cap;
        void resize(int newCap) throw(const char*);
        void setSize(int num) { this->num = num; }
        void setCapacity(int cap) { this->cap = cap; }

    public:
        // default constructor and non-default constructors
        queue()
        {
            setCapacity(0);
            setSize(0);
            this->data = NULL;
        }
        queue(int cap);
        queue(const queue& rhs);

        // destructor
         ~queue()
        {
            if (data != NULL)
            {
                delete[] data;
            }
        }
        
        // overloaded operators
        queue& operator = (const queue<T>& rhs) throw(const char*);

        // member methods 
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
     * queue :: RESIZE
     *******************************************/
    template <class T>
    void queue <T> ::resize(int newCap) throw(const char*)
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
    * queue :: Top
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    T& queue <T> ::top()
    {
        if (!empty())
        {
            return data[size() - 1];
        }
        else if (empty())
        {
            throw "ERROR: Unable to reference the element from an empty queue";
        }
    };

    /********************************************
    * queue :: Top
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    const T& queue <T> ::top() const
    {
        if (!empty())
        {
            return data[size() - 1];
        }
        else
        {
            throw "ERROR: Unable to reference the element from an empty queue\n";
        }
    };

    /********************************************
    * queue :: Push
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void queue <T> ::push(const T& t)
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
     * queue :: Clear
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void queue <T> ::clear()
    {
        num = 0;
    };

    /********************************************
     * queue :: Pop
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void queue <T> ::pop()
    {
        if (!empty())
        {
            num--;
        }
    };

    /*******************************************
     * queue :: Assignment CONSTRUCTOR
     *******************************************/
    template <class T>
 queue <T>& queue <T> :: operator = (const queue <T>& rhs) throw(const char*)
    {
        // we can only copy arrays of equal size. queues are not this way!
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
     * queue :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
 queue <T> :: queue(const queue <T>& rhs)
    {
        data = NULL;
        num = 0;
        cap = 0;

        *this = rhs;

    }

    /**********************************************
     * queue : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
 queue <T> :: queue(int cap)
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
#endif // queue_H

