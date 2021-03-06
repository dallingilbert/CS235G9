/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This class contains the notion of a deque: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the deque, set, deque, deque, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       Dequeue             : similar to std::deque
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H
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
    * deque
    * A class that holds stuff
    ***********************************************/
    template <class T>
    class deque
    {
    private:
        // member variables
        T* data;
        int iFront;
        int iBack;
        int numCapacity;

        // setters
        void setFront(int iFront) { this->iFront = iFront; }
        void setBack(int iBack) { this->iBack = iBack; }
        void setCapacity(int numCapacity) { this->numCapacity = numCapacity; }

        // private member methods
        void resize(int newCap) throw(const char*);
        //int iHead() { return (getBack() % capacity()); }
        //int iTail() { return ((getFront() - 1) % capacity()); }
        int capacity() const { return numCapacity; }
        int iFrontNormalized() const;
        int iBackNormalized() const;
        int iNormalized(int index) const;
        //void display() const;

    public:
        // default constructor and non-default constructors
        deque()
        {
            setCapacity(0);
            setBack(-1);
            setFront(0);
            this->data = NULL;
        }
        deque(int numCapacity);
        deque(const deque& rhs);

        // destructor
        ~deque()
        {
            if (data != NULL)
            {
                delete[] data;
            }
        }

        // overloaded operators
        deque& operator = (const deque<T>& rhs) throw(const char*);

        // getters
        int size() const { return getBack() - getFront() + 1; }
        int getBack() const { return iBack; }
        int getFront() const { return iFront; }


        // public member methods
        bool empty() const { return size() == 0; }
        void clear();

        // push methods
        void push_back(const T& t);
        void push_front(const T& t);

        // pop methods
        void pop_back();
        void pop_front();

        T& top();
        const T& top() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
    };

    /*******************************************
     * deque :: RESIZE
     *******************************************/
    template <class T>
    void deque <T> ::resize(int newCap) throw(const char*)
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

        if (data != NULL)
        {
            delete[] data;
            data = NULL;
        }
        data = newData;

        setCapacity(newCap);
        //setFront(iFrontNormalized());
        //setBack(iBackNormalized());
    };

    /********************************************
     * deque :: iFrontNormalized()
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    int deque <T> ::iFrontNormalized() const
    {
        return iNormalized(iFront);
    }

    /********************************************
     * deque :: iBackNormalized()
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    int deque <T> ::iBackNormalized() const
    {
        return iNormalized(getBack());
    }

    /********************************************
     * deque :: iNormalized()
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    int deque <T> ::iNormalized(int index) const
    {
        //return (capacity() + (index % capacity())) % capacity();
       /* if (index >= 0)
            return index % capacity();
        if (index < 0)
        {
            int test = (index % capacity()) % capacity();
            cerr << test << "test" <<endl;
            return test;*/
       // else
        int cap = capacity();
        int test = ((cap + ((index) % cap)) % cap);
        //cerr << test << "normal" << endl;
        return test;
    }

    /********************************************
     * deque :: Clear
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void deque <T> ::clear()
    {
        setFront(0);
        setBack(-1);
    };

    /********************************************
    * deque :: Push Back
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void deque <T> ::push_back(const T& t)
    {
        if (capacity() == 0)
        {
            resize(1);
        }
        else if (size() == capacity())
        {
            resize(capacity() * 2);
        }
        setBack(getBack() + 1);
        data[iBackNormalized()] = t;
        //cerr << iBackNormalized() <<"back" << endl;
    };

    /********************************************
    * deque :: Push Front
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void deque <T> ::push_front(const T& t)
    {
        if (capacity() == 0)
        {
            resize(1);
        }
        else if (size() == capacity())
        {
            resize(capacity() * 2);
        }

        setFront((getFront() - 1));
        data[iFrontNormalized()] = t;
        //cerr << iFrontNormalized()<< "front"<< endl;
    };

    /********************************************
     * deque :: Pop Back
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void deque <T> ::pop_back()
    {
        if (!empty())
            setBack(getBack() - 1);
        else
            cout << "";
    };

    /********************************************
     * deque :: Pop Front
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void deque <T> ::pop_front()
    {
        if (!empty())
            setFront(getFront() + 1);
        else
            cout << "";
    };

    /*******************************************
     * deque :: Assignment operator
     *******************************************/
    template <class T>
    deque <T>& deque <T> :: operator = (const deque <T>& rhs) throw(const char*)
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
     * deque :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    deque <T> ::deque(const deque <T>& rhs)
    {
        this->data = NULL;
        setFront(0);
        setCapacity(0);
        setBack(-1);

        *this = rhs;
    }

    /**********************************************
     * deque : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
    deque <T> ::deque(int numCapacity)
    {
        assert(numCapacity >= 0);

        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (numCapacity == 0)
        {
            cerr << "numCapacity is 0 -----" << endl;
            deque();
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
        setBack(-1);
        setFront(0);
    }

    /**********************************************
     * deque : FRONT
     * Access the oldest value from the deque by
     * reference
     **********************************************/
    template <class T>
    T& deque <T> ::front()
    {
        if (empty())
            throw "ERROR: unable to access data from an empty deque";
        else
            return data[iFrontNormalized()];
    }

    /**********************************************
     * deque : FRONT
     * Access the oldest value from the deque by
     * const
     **********************************************/
    template <class T>
    const T& deque <T> ::front() const
    {
        if (empty())
            throw "ERROR: unable to access data from an empty deque";
        else
            return data[iFrontNormalized()];
    }

    /**********************************************
     * deque : BACK
     * Access the oldest value from the deque by
     * reference
     **********************************************/
    template <class T>
    T& deque <T> ::back()
    {
        if (empty())
            throw "ERROR: unable to access data from an empty deque";
        else
            return data[iBackNormalized()];
    }

    /**********************************************
     * deque : BACK
     * Access the oldest value from the deque by
     * const
     **********************************************/
    template <class T>
    const T& deque <T> ::back() const
    {
        if (empty())
            throw "ERROR: unable to access data from an empty deque";
        else
            return data[iBackNormalized()];
    }
};
#endif // DEQUE_H