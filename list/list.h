/***********************************************************************
 * Header:
 *    list
 * Summary:
 *    This class contains the notion of a list: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the list, list, list, list, list, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       listue             : similar to std::list
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <cstddef>
#include <cassert> // because I am paranoid
#include "node.h"

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
    * list
    * A class that holds stuff
    ***********************************************/
    template <class T>
    class list
    {
    private:
        // member variables
        Node *pHead;
        Node *pTail;
        int numElements;

        // setters
        void listSize(int numElements) { this->numElements = numElements; }
        void listCapacity(int numCapacity) { this->numCapacity = numCapacity; }

        // private member methods
        void resize(int newCap);
        void addToEnd(const T& t);
        int findIndex(const T& t) const;


    public:
        // default constructor and non-default constructors
        list()
        {
            listCapacity(0);
            listSize(0);
            this->data = NULL;
        }
        list(int numCapacity);
        list(const list& rhs);

        // destructor
        ~list()
        {
             if (data != NULL)
              {
                  delete[] data;
              }
        }

        // overloaded operators
        list& operator=(const list<T>& rhs);

        // getters
        int size() const { return numElements; }
        int capacity() const { return numCapacity; }
        
        // public member methods
        bool empty() const { return size() == 0; }
        void clear();
        void insert(const T& t);
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // push methods
        void push_back(const T& t);
        void push_front(const T& t);

        // pop methods
        void pop_back();
        void pop_front();
        
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
    * list :: ITERATOR
    * An iterator through a list
    *************************************************/
    template <class T>
    class list<T>::iterator
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
    * list :: CONST_ITERATOR
    * An iterator through array
    *************************************************/
    template <class T>
    class list<T>::const_iterator
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
    * list :: BEGIN
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename list<T>::iterator list<T>::begin()
    {
        return iterator(data);
    }

    /********************************************
    * list :: END
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename list<T>::iterator list<T>::end()
    {
        return iterator(data + numElements);
    }

    /********************************************
    * list :: CBEGIN
    * Returns the beginning of our array
    ********************************************/
    template <class T>
    typename list<T>::const_iterator list<T>::Cbegin() const
    {
        return const_iterator(data);
    }

    /********************************************
    * list :: CEND
    * Returns the end of our array
    ********************************************/
    template <class T>
    typename list<T>::const_iterator list<T>::Cend() const
    {
        return const_iterator(data + numElements);
    }

    /*******************************************
     * list :: RESIZE
     * Dynamically allocates new space for the 
     * additional items created for our list
     *******************************************/
    template <class T>
    void list<T>::resize(int newCap)
    {
        try
        {
            T* temp = new T[newCap];
            
            // copy data from old array to new array
            for (int i = 0; i < numElements; i++)
                temp[i] = data[i];

            delete[] data; // clear memory
            this-> data = temp;
            listCapacity(newCap); // increase capacity
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer a new buffer for list";
        }
    };

    /********************************************
   * list :: ERASE
   * Note that you have to use "typename" before
   * the return value type
   ********************************************/
    template <class T>
    void list<T>::erase(list<T>::iterator& it)
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
     * list : FIND
     * Determines if a value is found within our 
     * list, if it is not found, return the end
     * iterator
     **********************************************/
    template <class T>
    typename list<T>::iterator list<T>::find(const T& t)
    {
        int index = findIndex(t);
        if (data[index] == t)
        {
           return iterator(data + index);
        }
        return end();
    }

    /********************************************
     * list :: Clear
     * Empty our list and relist the size and
     * capacity
     ********************************************/
    template <class T>
    void list<T>::clear()
    {
        listSize(0);
        listCapacity(0);
        data = NULL;
    };

    /********************************************
    * list :: Push Back
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void list <T> ::push_back(const T& t)
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
    * list :: Push Front
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void list <T> ::push_front(const T& t)
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
     * list :: Pop Back
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void list <T> ::pop_back()
    {
        if (!empty())
            setBack(getBack() - 1);
        else
            cout << "";
    };

    /********************************************
     * list :: Pop Front
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void list <T> ::pop_front()
    {
        if (!empty())
            setFront(getFront() + 1);
        else
            cout << "";
    };

    /*******************************************
     * list :: Assignment operator
     * Copies the data from one object to the
     * other
     *******************************************/
    template <class T>
    list<T>& list<T>::operator=(const list<T>& rhs)
    {
        if (numCapacity < rhs.numCapacity)
        {
            resize(rhs.numCapacity);
        }

        if (data == NULL)
        {
            try
            {
                listSize(rhs.size());
                listCapacity(rhs.capacity());
                data = new T[numCapacity];
            }
            catch (std::bad_alloc)
            {
                throw "ERROR: Unable to allocate buffer a new buffer for list";
            }
        }
        for (int i = 0; i < rhs.numElements; i++)
            data[i] = rhs.data[i];

        numElements = rhs.numElements;
        numCapacity = rhs.numCapacity;
        return *this;
    }

    /*******************************************
     * list :: COPY CONSTRUCTOR
     * Copies all of the data using the assignment
     * operator
     *******************************************/
    template <class T>
    list<T>::list(const list<T>& rhs)
    {
        this->data = NULL;
        listSize(0);
        listCapacity(0);

        *this = rhs;
    }

    /**********************************************
     * list : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template <class T>
    list<T>::list(int numCapacity)
    {
        assert(numCapacity >= 0);
        this->data = NULL;

        listCapacity(numCapacity);
        
        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (numCapacity == 0)
        {
            cerr << "numCapacity is 0 -----" << endl;
            list();
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
        listSize(0);
    }

    /********************************************
    * list :: INSERT
    * Inserts the passed in value into our list
    * at a specified index
    ********************************************/
    template <class T>
    void list<T>::insert(const T& t)
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
                        throw "ERROR: Unable to allocate buffer a new buffer for list";
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
     * list : FIND INDEX
     * Finds the index of a certain value within 
     * our list
     **********************************************/
    template <class T>
    int list<T>::findIndex(const T& t) const
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

    /**********************************************
     * list : FRONT
     * Access the oldest value from the list by
     * reference
     **********************************************/
    template <class T>
    T& list <T> ::front()
    {
        if (empty())
            throw "ERROR: attempting to access an element in an empty list";
        else
            return data[iHead()];
    }

    /**********************************************
     * list : FRONT
     * Access the oldest value from the list by
     * const
     **********************************************/
    template <class T>
    const T& list <T> ::front() const
    {
        if (empty())
            throw "ERROR: attempting to access an element in an empty list";
        else
            return data[iHead()];
    }
    
    /**********************************************
     * list : BACK
     * Access the oldest value from the list by 
     * reference
     **********************************************/
    template <class T>
    T& list <T> :: back()
    {
        if (empty())
            throw "ERROR: attempting to access an element in an empty list";
        else 
            return data[iTail()];
    }

    /**********************************************
     * list : BACK
     * Access the oldest value from the list by 
     * const
     **********************************************/
    template <class T>
    const T& list <T> :: back() const
    {
        if (empty())
            throw "ERROR: attempting to access an element in an empty list";
        else 
            return data[iTail()];
    }
};     // namespace custom
#endif // LIST_H