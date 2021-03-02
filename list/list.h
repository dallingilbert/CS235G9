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
        list(list<T>& rhs);

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
        iterator erase(const iterator& it);
        iterator insert(const iterator& it, const T& t);
        iterator begin();
        iterator end();

        class const_iterator;
        const_iterator Cbegin();
        const_iterator Cend();

        class reverse_iterator;
        reverse_iterator Rbegin();
        reverse_iterator Rend();

        class const_reverse_iterator;
        const_reverse_iterator CRbegin();
        const_reverse_iterator CRend();
    };

    /**************************************************
    * list :: ITERATOR
    * An iterator through a list
    *************************************************/
    template <class T>
    class list<T>::iterator
    {
    private:
        Node<T>* p;
    public:
        // constructors, destructors, and assignment operator
        iterator() : p(NULL) {}
        iterator(Node<T>* temp) : p(temp) {}//: data(*data) {}
        iterator(const iterator& rhs) { *this = rhs; }
        iterator& operator=(const iterator& rhs)
        {
            this->data = rhs.data;
            return *this;
        }

        friend iterator list<T>::insert(const iterator& it, const T& t);
        friend iterator list<T>::erase(const iterator& it);
        // equals, not equals operator
        bool operator!=(const iterator& rhs) const { return rhs.data != this->data; }
        bool operator==(const iterator& rhs) const { return rhs.data == this->data; }

        // dereference operator
        T& operator*() { return p->data; }
        const T& operator*() const { return p->data; }

        // prefix increment
        iterator& operator++()
        {
            p = p->pNext;
            iterator tmp(p);
            return tmp;
        }

        // postfix increment
        iterator operator++(int postfix)
        {
            iterator tmp(*this);
            tmp = tmp.p->p;
            return tmp;
        }
        // prefix increment
        iterator& operator--()
        {
            p = p->pPrev;
            iterator tmp(p);
            return tmp;
        }

        // postfix increment
        iterator operator--(int prefix)
        {
            iterator tmp(*this);
            tmp = tmp.p->pPrev;
            return tmp;
        }
    };

    /**************************************************
    * list :: const_iterator
    * An iterator through a list
    *************************************************/
    template <class T>
    class list<T>::const_iterator
    {
    private:
        Node<T>* p;
    public:
        // constructors, destructors, and assignment operator
        const_iterator() : p(NULL) {}
        const_iterator(Node<T>* temp) : p(temp) {}//: data(*data) {}
        const_iterator(const iterator& rhs) { *this = rhs; }
        const_iterator& operator=(const iterator& rhs)
        {
            this->data = rhs.data;
            return *this;
        }

        friend const_iterator list<T>::insert(const const_iterator& it, const T& t);
        friend const_iterator list<T>::erase(const const_iterator& it);
        // equals, not equals operator
        bool  operator!=(const const_iterator & rhs) const { return rhs.p != this->p; }
        bool operator ==(const const_iterator & rhs) const { return rhs.p == this->p; }

        // dereference operator
        const T& operator*() { return p->data; }
        const T& operator*() const { return p->data; }

        // prefix increment
        const_iterator& operator++()
        {
            p = p->pNext;
            const_iterator tmp(p);
            return tmp;
        }

        // postfix increment
        const_iterator operator++(int postfix)
        {
            const_iterator tmp(*this);
            tmp = tmp.p->p;
            return tmp;
        }
        // prefix increment
        const_iterator& operator--()
        {
            p = p->pPrev;
            const_iterator tmp(p);
            return tmp;
        }

        // postfix increment
        const_iterator operator--(int prefix)
        {
            const_iterator tmp(*this);
            tmp = tmp.p->pPrev;
            return tmp;
        }
    };

    /**************************************************
    * list :: reverse_iterator
    * An iterator through array
    *************************************************/
    template <class T>
    class list<T>::reverse_iterator
    {
    private:
        Node<T>* p;
    public:
        // constructors, destructors, and assignment operator
        reverse_iterator() : p(NULL) {}
        reverse_iterator(Node<T>* temp) : p(temp) {}
        reverse_iterator(const reverse_iterator& rhs) { *this = rhs; }
        reverse_iterator& operator=(const reverse_iterator& rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const reverse_iterator& rhs) const { return rhs.p != this->p; }
        bool operator==(const reverse_iterator& rhs) const { return rhs.p == this->p; }

        // dereference operator
        T& operator*() { return p->data; }
        const T& operator*() const { return p->data; }

        // prefix increment
        reverse_iterator& operator++()
        {
            p = p->pPrev;
            reverse_iterator tmp(p);
            return tmp;
        }

        // postfix increment
        reverse_iterator operator++(int postfix)
        {
            reverse_iterator tmp(*this);
            tmp = tmp.p->p;
            return tmp;
        }
        // prefix increment
        reverse_iterator& operator--()
        {
            p = p->pNext;
            reverse_iterator tmp(p);
            return tmp;
        }

        // postfix increment
        reverse_iterator operator--(int prefix)
        {
            reverse_iterator tmp(*this);
            tmp = tmp.p->pPrev;
            return tmp;
        }
    };

    /**************************************************
    * list :: const_reverse_iterator
    * An iterator through array
    *************************************************/
    template <class T>
    class list<T>::const_reverse_iterator
    {
    private:
        Node<T>* p;
    public:
        // constructors, destructors, and assignment operator
        const_reverse_iterator() : p(NULL) {}
        const_reverse_iterator(Node<T>* temp) : p(temp) {}
        const_reverse_iterator(const const_reverse_iterator& rhs) { *this = rhs; }
        const_reverse_iterator& operator=(const const_reverse_iterator& rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const const_reverse_iterator& rhs) const { return rhs.p != this->p; }
        bool operator==(const const_reverse_iterator& rhs) const { return rhs.p == this->p; }

        // dereference operator
        const T& operator*() { return p->data; }
        const T& operator*() const { return p->data; }

        // prefix increment
        const_reverse_iterator& operator++()
        {
            p = p->pPrev;
            const_reverse_iterator tmp(p);
            return tmp;
        }

        // postfix increment
        const_reverse_iterator operator++(int postfix)
        {
            const_reverse_iterator tmp(*this);
            tmp = tmp.p->p;
            return tmp;
        }
        // prefix increment
        const_reverse_iterator& operator--()
        {
            p = p->pNext;
            const_reverse_iterator tmp(p);
            return tmp;
        }

        // postfix increment
        const_reverse_iterator operator--(int prefix)
        {
            const_reverse_iterator tmp(*this);
            tmp = tmp.p->pPrev;
            return tmp;
        }
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
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename list<T>::const_iterator list<T>::Cbegin()
    {
        return const_iterator(pHead);
    }

    /********************************************
    * list :: CEND
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename list<T>::const_iterator list<T>::Cend()
    {
        return const_iterator(NULL);
    }

    /********************************************
    * list :: RBEGIN
    * Returns the beginning of our array
    ********************************************/
    template <class T>
    typename list<T>::reverse_iterator  list<T>::Rbegin()
    {
        return reverse_iterator(pTail);
    }

    /********************************************
    * list :: REND
    * Returns the end of our array
    ********************************************/
    template <class T>
    typename list<T>::reverse_iterator  list<T>::Rend()
    {
        return reverse_iterator(NULL);
    }

    /********************************************
    * list :: CRBEGIN
    * Returns the beginning of our array
    ********************************************/
    template <class T>
    typename list<T>::const_reverse_iterator  list<T>::CRbegin()
    {
        return const_reverse_iterator(pTail);
    }

    /********************************************
    * list :: CREND
    * Returns the end of our array
    ********************************************/
    template <class T>
    typename list<T>::const_reverse_iterator  list<T>::CRend()
    {
        return const_reverse_iterator(NULL);
    }

    /********************************************
   * list :: ERASE
   * Note that you have to use "typename" before
   * the return value type
   ********************************************/
    template <class T>
    typename list<T> ::iterator list<T>::erase(const iterator& it)
    {
        if (it.p == NULL)
            return iterator(NULL);
        if (it.p->pPrev != NULL)
            it.p->pPrev->pNext = it.p->pNext;
        if (it.p->pNext != NULL)
            it.p->pNext->pPrev = it.p->pPrev;
        if (pHead == it.p)
            pHead = it.p->pNext;
        if (pTail == it.p)
            pTail = it.p->pPrev;
        Node<T>* temp;
        if (it.p->pPrev != NULL)
            temp = it.p->pPrev;
        else
            temp = it.p->pNext;
        delete it.p;
        return iterator(temp);
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
        while (pHead != NULL)
        {
            Node<T>* pDelete = pHead;
            pHead = pHead->pNext;
            delete pDelete;
        }
        numElements = 0;
        pHead = NULL;
        pTail = NULL;
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
            pNew->pNext = NULL;
            pNew->pPrev = pTail;
            pTail->pNext = pNew;
            pTail = pNew;
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
        }
        if (pHead == NULL)
        {
            pTail = pNew;
            pHead = pNew;
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
            else
                throw "ERROR: Unable to allocate buffer a new buffer for set";
            for (list<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
                push_back(*it);
        }
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
        int x = 0;
        if (rhs.pHead != NULL)
        {
            if (pHead != NULL)
                clear();
            for (list<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
                push_back(*it);
        }
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
        pNew->pNext = it.p;
        pNew->pPrev = it.p->pPrev;
        //point prev and next nodes to the new node
        it.p->pPrev = pNew;
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