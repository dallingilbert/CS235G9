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
    template <typename  T>
    class list
    {
    private:
        // member variables
        Node<T>* pHead;
        Node<T>* pTail;
        int numElements;

    public:
        // default constructor and non-default constructors
        list()
        {
            pHead = NULL;
            pTail = NULL;
            numElements = 0;
        }
        list(list& rhs);

        // destructor
        ~list()
        {
            if (pHead != NULL)
            {
                Node<T>* pDelete = pHead;
                pHead = pHead->pNext;
                delete pDelete;
            }
        }

        // overloaded operators
        list& operator=(list<T>& rhs);

        // getters
        int size() const { return numElements; }

        // public member methods
        bool empty() const { return size() == 0; }
        void clear();
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // push methods
        void push_back(T t);
        void push_front(T t);

        // pop methods
        void pop_back();
        void pop_front();

        // the various iterator interfaces
        class iterator;
        iterator find(const T& t);
        iterator erase(iterator& it);
        iterator insert(const iterator& it, const T& t);
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
        iterator() : data(NULL) {}
        iterator(Node<T>* temp) : data(temp) {}//: data(*data) {}
        iterator(const iterator& rhs) { *this = rhs; }
        iterator& operator=(const iterator& rhs)
        {
            this->data = rhs.data;
            return *this;
        }

        friend iterator list<T>::insert(const iterator& it, const T& t);
        //friend iterator list<T>::erase(const iterator& it);
        // equals, not equals operator
        bool operator!=(const iterator& rhs) const { return rhs.data != this->data; }
        bool operator==(const iterator& rhs) const { return rhs.data == this->data; }

        // dereference operator
        T& operator*() { return data->data; }
        const T& operator*() const { return data->data; }

        // prefix increment
        iterator& operator++()
        {
            data++;
            return *this;
        }

        // postfix increment
        iterator operator++(int postfix)
        {
            iterator tmp(*this);
            data++;
            return tmp;
        }

    private:
        Node<T>* data;
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
        const_iterator() : data(NULL) {}
        const_iterator(T* data) : data(data) {}
        const_iterator(const const_iterator& rhs) { *this = rhs; }
        const_iterator& operator=(const const_iterator& rhs)
        {
            this->data = rhs.data;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const const_iterator& rhs) const { return rhs.data != this->data; }
        bool operator==(const const_iterator& rhs) const { return rhs.data == this->data; }

        // dereference operator
        const T& operator*() { return *data; }
        const T& operator*() const { return *data; }

        // prefix increment
        const_iterator& operator++()
        {
            data++;
            return *this;
        }

        // postfix increment
        const_iterator operator++(int postfix)
        {
            iterator tmp(*this);
            data++;
            return tmp;
        }

    private:
        T* data;
    };

    /********************************************
    * list :: BEGIN
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename list<T>::iterator list<T>::begin()
    {
        return iterator(pHead);
    }

    /********************************************
    * list :: END
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename list<T>::iterator list<T>::end()
    {
        return iterator(NULL);
    }

    /********************************************
    * list :: CBEGIN
    * Returns the beginning of our array
    ********************************************/
    template <class T>
    typename list<T>::const_iterator list<T>::Cbegin() const
    {
        return const_iterator(pHead);
    }

    /********************************************
    * list :: CEND
    * Returns the end of our array
    ********************************************/
    template <class T>
    typename list<T>::const_iterator list<T>::Cend() const
    {
        return const_iterator(NULL);
    }

    /********************************************
   * list :: ERASE
   * Note that you have to use "typename" before
   * the return value type
   ********************************************/
    template <class T>
    typename list<T> ::iterator list<T>::erase(iterator& it)
    {
        if (it == NULL)
        {
            return NULL;
        }
        else if (it->pPrev != NULL)
        {
            it->pPrev->pNext = it->pNext;
        }
        else if (it->pNext != NULL)
        {
            it->pNext->pPrev = it->pPrev;
        }

        //return either the prev or next node
        Node<T>* pReturn;
        if (it->pPrev != NULL)
        {
            pReturn = it->pPrev;
        }
        else
        {
            pReturn = it->pNext;
        }
        delete it;
        return pReturn;
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
        // find the node equal to our parameter in our list
        if (front == NULL || front->pNext == NULL && front->data == t)
            return front;
        else
        {
            for (Node<T>* data = front; data != NULL; data = data->pNext)
            {
                //searches if the data is in the list
                if (data->data == t)
                {
                    //if value is found
                    return data;
                }
            }
        }
        return NULL;
    }

    /********************************************
     * list :: Clear
     * Empty our list and relist the size and
     * capacity
     ********************************************/
    template <class T>
    void list<T>::clear()
    {
        Node<T>* pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    };

    /********************************************
    * list :: Push Back
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void list <T> ::push_back(T t)
    {
        Node<T>* pNew = new Node<T>(t);
        numElements++;
        if (pTail != NULL)
        {
            pNew->pNext = pTail->pNext;
            pNew->pPrev = pTail;
            pTail->pNext = pNew;
            pTail = pNew;
            if (pNew->pPrev)
                pNew->pPrev->pNext = pNew;
        }
        if (pTail == NULL)
        {
            pTail = pNew;
            pHead = pNew;
        }
    };

    /********************************************
    * list :: Push Front
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    void list <T> ::push_front(T t)
    {
        Node<T>* pNew = new Node<T>(t);
        numElements++;
        if (pHead != NULL)
        {
            pNew->pNext = pHead;
            pNew->pPrev = pHead->pPrev;
            pHead->pPrev = pNew;
            pHead = pNew;
            if (pNew->pHead)
                pNew->pPrev->pNext = pNew;
        }
    };

    /********************************************
     * list :: Pop Back
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void list <T> ::pop_back()
    {
        if (pTail != NULL)
        {
            Node<T>* tmp = pTail->pPrev;
            pTail->pPrev->pNext = NULL;
            pTail = tmp;
            numElements--;
        }
    };

    /********************************************
     * list :: Pop Front
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    void list <T> ::pop_front()
    {
        if (pHead != NULL)
        {
            Node<T>* tmp = pHead->pPrev;
            pHead->pPrev->pNext = NULL;
            pHead = tmp;
            numElements--;
        }
    };

    /*******************************************
     * list :: Assignment operator
     * Copies the data from one object to the
     * other
     *******************************************/
    template <class T>
    list<T>& list<T>::operator=(list<T>& rhs)
    {
        if (rhs.pHead != NULL)
        {
            if (pHead != NULL)
                clear();
          
            for (list<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
                push_back(*it);
        }
        else
            throw "ERROR: Unable to allocate buffer a new buffer for set";

        return *this;
    }

    /*******************************************
     * list :: COPY CONSTRUCTOR
     * Copies all of the data using the assignment
     * operator
     *******************************************/
    template <class T>
    list<T>::list(list<T>& rhs)
    {
        pHead = NULL;
        pTail = NULL;
        numElements = 0;

        if (rhs.pHead != NULL)
        {
            if (pHead != NULL)
                clear();

            for (list<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
                push_back(*it);
        }
        else
            throw "ERROR: Unable to allocate buffer a new buffer for set";

        *this = rhs;
    }

    /********************************************
    * list :: INSERT
    * Inserts the passed in value into our list
    * at a specified index
    ********************************************/
    template <class T>
    typename list<T> ::iterator list<T>::insert(const list<T>::iterator& it, const T& t)
    {
        //if they insert a null pointer add to the end
        if (it == NULL)
        {
            Node<T>* pNew = new Node<T>(t);
            pNew->pPrev = pTail;
            pNew->pNext = NULL;

            //point tail to pNew
            pTail->pNext = pNew;
            numElements++;
            pTail = pNew;
            return iterator(pNew);
        }

        //create new node
        Node<T>* pNew = new Node<T>(t);
        if (pHead == NULL && pTail == NULL)
        {
            pHead = pNew;
            pTail = pNew;
            numElements++;
            return iterator(pNew);
        }
        //point new node to prev and next nodes
        pNew->pNext = it.data;
        pNew->pPrev = it.data->pPrev;

        //point prev and next nodes to the new node
        it.data->pPrev = pNew;
        if (pNew->pPrev != NULL)
            pNew->pPrev->pNext = pNew;

        //special cases front and back of the list
        if (pNew->pPrev == NULL)
            pHead = pNew;
        else if (pNew->pNext == NULL)
            pTail = pNew;
            
        numElements++;
        return iterator(pNew);
    };

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
            return pHead->data;
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
            return pHead->data;
    }

    /**********************************************
     * list : BACK
     * Access the oldest value from the list by
     * reference
     **********************************************/
    template <class T>
    T& list <T> ::back()
    {
        if (empty())
            throw "ERROR: attempting to access an element in an empty list";
        else
            return pTail->data;
    }

    /**********************************************
     * list : BACK
     * Access the oldest value from the list by
     * const
     **********************************************/
    template <class T>
    const T& list <T> ::back() const
    {
        if (empty())
            throw "ERROR: attempting to access an element in an empty list";
        else
            return pTail->data;
    }
};     // namespace custom
#endif // LIST_H