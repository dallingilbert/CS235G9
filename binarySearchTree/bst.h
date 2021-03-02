/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *    This class contains the notion of a BST: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       BST             : similar to std::BST
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef BST_H
#define BST_H
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
    * BST
    * A class that holds stuff
    ***********************************************/
    template <typename T>
    class BST
    {
    private:
        class BNode
        {
        public:
            // member variables
            T data;
            BNode *pLeft;
            BNode *pRight;
            BNode *pParent;
            bool isRed;

            // default constructor
            BNode()
            {
                this->pParent = NULL;
                this->pNext = NULL;
                this->pPrev = NULL;
                data = T();
                isRed = false;
            }

            // non-default constructor
            BNode(const T &t)
            {
                this->pLeft = NULL;
                this->pRight = NULL;
                this->pParent = NULL;
                data = t;
                isRed = false;
            }

        private:
            // private member methods
            void verifyRB(int depth);
            void verifyBST();
            void balance();
        };

        // private member variables BST
        BNode *root;
        int numElements;

        // private member methods BST
        void deleteNode(BNode *del, bool right);
        void deleteBinaryTree(BNode *del);
        void copyBinaryTree(BNode *src, BNode *dest);

    public:
        // default constructor and non-default constructors
        BST()
        {
            root = NULL;
            numElements = 0;
        }

        // copy constructor
        BST(BST<T> &rhs);

        // destructor
        ~BST()
        {
            if (root != NULL)
            {
                delete root;
            }
        }

        // overloaded operators
        BST &operator=(BST<T> &rhs);

        // getters
        int size() const { return numElements; }

        // public member methods
        bool empty() const { return size() == 0; }
        void clear();

        // the various iterator interfaces
        class iterator;
        iterator find(const T &t);
        iterator erase(const iterator &it);
        iterator insert(const T &t);
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
    * BST :: ITERATOR
    * An iterator through a BST
    *************************************************/
    template <class T>
    class BST<T>::iterator
    {
    private:
        typename BST<T>::BNode *p;

    public:
        // constructors, destructors, and assignment operator
        iterator() : p(NULL) {}
        iterator(typename BST<T>::BNode *temp) : p(temp) {} //: data(*data) {}
        iterator(const iterator &rhs) { *this = rhs; }
        iterator &operator=(const iterator &rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        friend iterator BST<T>::insert(const T &t);
        friend iterator BST<T>::erase(const iterator &it);
        friend iterator BST<T>::begin();

        // equals, not equals operator
        bool operator!=(const iterator &rhs) const { return rhs.p != this->p; }
        bool operator==(const iterator &rhs) const { return rhs.p == this->p; }

        // dereference operator
        T &operator*() { return p->data; }
        const T &operator*() const { return p->data; }

        // prefix increment
        iterator &operator++()
        {
            if (p)
                p = p->pNext;
            return *this;
        }

        // postfix increment
        iterator operator++(int postfix)
        {
            iterator tmp(p);
            if (p)
                p = p->pNext;
            return tmp;
        }
        // prefix increment
        iterator &operator--()
        {
            p = p->pPrev;
            iterator tmp(p);
            return tmp;
        }

        // postfix increment
        iterator operator--(int prefix)
        {
            iterator tmp(p);
            tmp = tmp.p->pPrev;
            return tmp;
        }
    };

    /**************************************************
    * BST :: const_iterator
    * An iterator through a BST
    *************************************************/
    template <class T>
    class BST<T>::const_iterator
    {
    private:
        typename BST<T>::BNode *p;

    public:
        // constructors, destructors, and assignment operator
        const_iterator() : p(NULL) {}
        const_iterator(typename BST<T>::BNode *temp) : p(temp) {} //: data(*data) {}
        const_iterator(const iterator &rhs) { *this = rhs; }
        const_iterator &operator=(const iterator &rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        friend const_iterator BST<T>::insert(const const_iterator &it, const T &t);
        friend const_iterator BST<T>::erase(const const_iterator &it);
        // equals, not equals operator
        bool operator!=(const const_iterator &rhs) const { return rhs.p != this->p; }
        bool operator==(const const_iterator &rhs) const { return rhs.p == this->p; }

        // dereference operator
        const T &operator*() { return p->data; }
        const T &operator*() const { return p->data; }

        // prefix increment
        const_iterator &operator++()
        {
            if (p)
                p = p->pNext;
            return *this;
        }

        // postfix increment
        const_iterator operator++(int postfix)
        {
            const_iterator tmp(*this);
            if (p)
                p = p->pNext;
            return tmp;
        }
        // prefix increment
        const_iterator &operator--()
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
    * BST :: reverse_iterator
    * An iterator through array
    *************************************************/
    template <class T>
    class BST<T>::reverse_iterator
    {
    private:
        typename BST<T>::BNode *p;

    public:
        // constructors, destructors, and assignment operator
        reverse_iterator() : p(NULL) {}
        reverse_iterator(typename BST<T>::BNode *temp) : p(temp) {}
        reverse_iterator(const reverse_iterator &rhs) { *this = rhs; }
        reverse_iterator &operator=(const reverse_iterator &rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const reverse_iterator &rhs) const { return rhs.p != this->p; }
        bool operator==(const reverse_iterator &rhs) const { return rhs.p == this->p; }

        // dereference operator
        T &operator*() { return p->data; }
        const T &operator*() const { return p->data; }

        // prefix increment
        reverse_iterator &operator++()
        {
            if (p)
                p = p->pPrev;
            return *this;
        }

        // postfix increment
        reverse_iterator operator++(int postfix)
        {
            reverse_iterator tmp(*this);
            if (p)
                p = p->pPrev;
            return tmp;
        }
        // prefix increment
        reverse_iterator &operator--()
        {
            p = p->pNext;
            reverse_iterator tmp(p);
            return tmp;
        }

        // postfix increment
        reverse_iterator operator--(int prefix)
        {
            p = p->pNext;
            reverse_iterator tmp(*this);
            return tmp;
        }
    };

    /**************************************************
    * BST :: const_reverse_iterator
    * An iterator through array
    *************************************************/
    template <class T>
    class BST<T>::const_reverse_iterator
    {
    private:
        typename BST<T>::BNode *p;

    public:
        // constructors, destructors, and assignment operator
        const_reverse_iterator() : p(NULL) {}
        const_reverse_iterator(typename BST<T>::BNode *temp) : p(temp) {}
        const_reverse_iterator(const const_reverse_iterator &rhs) { *this = rhs; }
        const_reverse_iterator &operator=(const const_reverse_iterator &rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator!=(const const_reverse_iterator &rhs) const { return rhs.p != this->p; }
        bool operator==(const const_reverse_iterator &rhs) const { return rhs.p == this->p; }

        // dereference operator
        const T &operator*() { return p->data; }
        const T &operator*() const { return p->data; }

        // prefix increment
        const_reverse_iterator &operator++()
        {
            if (p)
                p = p->pPrev;
            return *this;
        }

        // postfix increment
        const_reverse_iterator operator++(int postfix)
        {
            const_reverse_iterator tmp(*this);
            if (p)
                p = p->pPrev;
            return tmp;
        }
        // prefix increment
        const_reverse_iterator &operator--()
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
    * BST :: BEGIN
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::begin()
    {
        return iterator();
    }

    /********************************************
    * BST :: END
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::end()
    {
        return iterator(NULL);
    }

    /********************************************
    * BST :: CBEGIN
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename BST<T>::const_iterator BST<T>::Cbegin()
    {
        return const_iterator(p.pParent);
    }

    /********************************************
    * BST :: CEND
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
    template <class T>
    typename BST<T>::const_iterator BST<T>::Cend()
    {
        return const_iterator(NULL);
    }

    /********************************************
    * BST :: RBEGIN
    * Returns the beginning of our array
    ********************************************/
    template <class T>
    typename BST<T>::reverse_iterator BST<T>::Rbegin()
    {
        return reverse_iterator(pTail);
    }

    /********************************************
    * BST :: REND
    * Returns the end of our array
    ********************************************/
    template <class T>
    typename BST<T>::reverse_iterator BST<T>::Rend()
    {
        return reverse_iterator(NULL);
    }

    /********************************************
    * BST :: CRBEGIN
    * Returns the beginning of our array
    ********************************************/
    template <class T>
    typename BST<T>::const_reverse_iterator BST<T>::CRbegin()
    {
        return const_reverse_iterator(pTail);
    }

    /********************************************
    * BST :: CREND
    * Returns the end of our array
    ********************************************/
    template <class T>
    typename BST<T>::const_reverse_iterator BST<T>::CRend()
    {
        return const_reverse_iterator(NULL);
    }

    /********************************************
   * BST :: ERASE
   * Note that you have to use "typename" before
   * the return value type
   ********************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::erase(const iterator &it)
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

        typename BST<T>::BNode *temp;

        if (it.p->pPrev != NULL)
            temp = it.p->pPrev;
        else
            temp = it.p->pNext;

        delete it.p;
        return iterator(temp);
    }

    /**********************************************
     * BST : FIND
     * Determines if a value is found within our
     * BST, if it is not found, return the end
     * iterator
     **********************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::find(const T &t)
    {
        // find the node equal to our parameter in our BST
        if (front == NULL || front->pNext == NULL && front->data == t)
            return front;
        else
        {
            for (typename BST<T>::BNode *data = front; data != NULL; data = data->pNext)
            {
                //searches if the data is in the BST
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
     * BST :: Clear
     * Empty our BST and reBST the size and
     * capacity
     ********************************************/
    template <class T>
    void BST<T>::clear()
    {
        while (pHead != NULL)
        {
            typename BST<T>::BNode *pDelete = pHead;
            pHead = pHead->pNext;
            delete pDelete;
        }

        numElements = 0;
        pHead = NULL;
        pTail = NULL;
    };

    /*******************************************
     * BST :: Assignment operator
     * Copies the data from one object to the
     * other
     *******************************************/
    template <class T>
    BST<T> &BST<T>::operator=(BST<T> &rhs)
    {
        if (rhs.pHead != NULL)
        {
            if (pHead != NULL)
                clear();
            else
                throw "ERROR: Unable to allocate buffer a new buffer for set";

            for (BST<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
                push_back(*it);
        }
        return *this;
    }

    /*******************************************
     * BST :: COPY CONSTRUCTOR
     * Copies all of the data using the assignment
     * operator
     *******************************************/
    template <class T>
    BST<T>::BST(BST<T> &rhs)
    {
        pHead = NULL;
        pTail = NULL;
        numElements = 0;
        int x = 0;

        if (rhs.pHead != NULL)
        {
            if (pHead != NULL)
                clear();

            for (BST<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
                push_back(*it);
        }
    }

    /********************************************
    * BST :: INSERT
    * Inserts the passed in value into our BST
    * at a specified index
    ********************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::insert(const T &t)
    {
        //if they insert a null pointer add to the end
        if (it == NULL)
        {
            typename BST<T>::BNode *pNew = new BNode(t);
            pNew->pPrev = pTail;
            pNew->pNext = NULL;

            //point tail to pNew
            pTail->pNext = pNew;
            numElements++;
            pTail = pNew;

            return iterator(pNew);
        }

        //create new node
        typename BST<T>::BNode *pNew = new BNode(t);

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

        //special cases front and back of the BST
        if (pNew->pPrev == NULL)
            pHead = pNew;
        else if (pNew->pNext == NULL)
            pTail = pNew;

        numElements++;

        return iterator(pNew);
    };
};     // namespace custom
#endif // BST_H