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
        // member variables
        T* data;
        int numPush;
        int numPop;
        int numCapacity;
        
        // setters
        void setPush(int numPush)         { this->numPush = numPush;         }
        void setPop(int numPop)           { this->numPop = numPop;           }
        void setCapacity(int numCapacity) { this->numCapacity = numCapacity; }
        
        // private member methods
        void resize(int newCap) throw(const char*);
        int iHead() { return (getPop() % capacity()); }
        int iTail() { return ((getPush() - 1) % capacity()); }

    public:
        // default constructor and non-default constructors
        queue()
        {
            setCapacity(0);
            setPop(0);
            setPush(0);
            this->data = NULL;
        }
        queue(int numCapacity);
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

        // getters
        int size() const { return (getPush() - getPop()); }
        int capacity() const { return numCapacity; }
        int getPop() const { return numPop; }
        int getPush() const { return numPush; }


         // public member methods 
        bool empty() const { return size() == 0; }
        void clear();
        void push(const T& t);
        void pop();
        T& top();
        const T& top() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
    };
    
    /*******************************************
     * queue :: RESIZE
     *******************************************/
    template <class T>
    void queue <T> ::resize(int newCap) throw(const char*)
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

        for (int i = 0; i < capacity() && i < newCap; i++)
            newData[i] = data[i];

        if (data != NULL)
        {
            delete[] data;
        }

        data = newData;

        if (newCap < capacity())
        {
            setPush(newCap);
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
        setPush(getPush() + 1);
        data[iTail()] = t;
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
        setPush(0);
        setPop(0);
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
            setPop(getPop() + 1);
    };

    /*******************************************
     * queue :: Assignment operator
     *******************************************/
    template <class T>
    queue <T>& queue <T> :: operator = (const queue <T>& rhs) throw(const char*)
    {
        // initialize all member variables
        setPush(0);
        setPop(0);

        if (rhs.numCapacity == 0)
        {
            return *this;
        }
        else if (capacity() < rhs.size())
            resize(rhs.size());
            
        for (int i = rhs.getPop(); i < rhs.getPush(); i++)
            push(rhs.data[i % rhs.capacity()]);

        return *this;
    }

    /*******************************************
     * queue :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    queue <T> :: queue(const queue <T>& rhs)
    {
        this->data = NULL;
        setPush(0);
        setCapacity(0);
        setPop(0);

        *this = rhs;
    }

    /**********************************************
     * queue : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
    queue <T> :: queue(int numCapacity)
    {
        assert(numCapacity >= 0);

        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (numCapacity == 0)
        {
            cerr << "numCapacity is 0 -----" << endl;
            queue();
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
        setPop(0);
        setPush(0);
    }

    /**********************************************
     * queue : FRONT
     * Access the oldest value from the queue by 
     * reference
     **********************************************/
    template <class T>
    T& queue <T> :: front()
    {
        if (empty())
            throw "ERROR: Unable to allocate queue";
        else 
            return data[iHead()];
    }

    /**********************************************
     * queue : FRONT
     * Access the oldest value from the queue by 
     * const
     **********************************************/
    template <class T>
    const T& queue <T> :: front() const
    {
        if (empty())
            throw "ERROR: Unable to allocate queue";
        else 
            return data[iHead()];
    }
};
#endif // queue_H

