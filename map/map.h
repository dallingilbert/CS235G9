/***********************************************************************
 * Header:
 *    MAP
 * Summary:
 *    This class contains the notion of a MAP : a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *    MAP : similar to std::MAP
 * Author
 *    John McCleve
 *    Dallin Gilbert
 ************************************************************************/

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cstddef>
#include <cassert> // because I am paranoid
#include "pair.h"
#include "bst.h"

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG
using namespace std;

namespace custom
{
    template <class K, class V>
    class map
    {
    public:
        //class BST;
        class iterator;
        // default constructor
        map()
        {
           bst = new BST<pair<K, V> >();
           //numElements = 0;
        }

        // copy constructor
        map(const map& rhs)
        {
            bst = new BST<pair<K, V> >(*(rhs.bst));
            //numElements = rhs.bst->size();
        }

        // assignment operator
        map &operator=(const map &rhs);

        // destructor
        ~map()
        {
            clear();
        }

        // member functions
        int size();
        bool empty();
        void clear();
        V& operator[](const K& k);
        void insert(const K& k, const V& v);

        // iterator functions
        iterator begin();
        iterator end();
        iterator find(const K& k);

    private:
        BST<pair<K,V>> *bst;
        //int numElements;

    };

    template <class K, class V>
    class map<K, V>::iterator
    {
    private:
        typename BST<pair<K, V> >::iterator *it;
    public:
        // constructors, destructors, and assignment operator
        iterator() : it(NULL) {};
        iterator(iterator* it) : it(it) {};
        iterator(const iterator& rhs)
        {
            if (NULL != rhs.it)
                it = rhs.it;
            else
                //if the iterator is null just set everything to null
                it = NULL;
        }
        iterator& operator = (const iterator& rhs)
        {
            this->it = rhs.it;
            return *this;
        }
        bool operator != (const iterator& rhs) const { return rhs.it != this->it; }

        bool operator == (const iterator& rhs) const { return rhs.it == this->it; }
        // TODO: Impelement the increment and decrement
        iterator & operator --() { --it; return *this; }
        iterator & operator ++() { ++it; return *this; }

        V& operator *() { return (*it).second; }
    };

    template <class K, class V>
    typename map<K, V>::iterator map<K, V>::begin()
    {
        return bst->begin();
    }

    template <class K, class V>
    typename map<K, V>::iterator map<K, V>::end()
    {
        return bst->end();
    }

    template <class K, class V>
    typename map<K, V>::iterator map<K, V>::find(const K& k)
    {
        pair<K, V> searchKey(K, V);
        iterator found = bst->find(searchKey);
        if (found == bst->end()) // We didn't find the value...
        {
            bst->insert(searchKey); // Add this new node
            found = bst->find(searchKey); // Now we should find it and can return it
        }
        return found;
    }
    /*****************************************************
    * MAP ASSIGNMENT OPERATOR
    * Overload the assignment operator to copy data from
    * one BST to the next
    ****************************************************/
    template <class K, class V>
    map<K,V> &map<K,V>::operator=(const map &rhs)
    {
        bst = new BST<pair<K, V> >(*(rhs.bst));
        //numElements = rhs.numElements;
        return *this;
    }

    /*****************************************************
    * MAP SIZE
    * Definition of our Binary Search Tree
    ****************************************************/
    template <class K, class V>
    int map<K, V>::size()
    {
        return bst->size();
    }

    /*****************************************************
    * MAP EMPTY
    * Definition of our Binary Search Tree
    ****************************************************/
    template <class K, class V>
    bool map<K, V>::empty()
    {
        return bst->empty();
    }

    /*****************************************************
    * MAP CLEAR
    * Definition of our Binary Search Tree
    ****************************************************/
    template <class K, class V>
    void map<K, V>::clear()
    {
        bst->clear();
    }
    //access
    template <class K, class V>
    V& map<K, V>::operator [] (const K& k)
    {
        typename BST<pair<K, V> >::iterator it;
        pair<K, V> Pair(k,V());
        it = bst->find(Pair);
        if (it != NULL)
            return (*it).second;
        else
        {
            bst->insert(Pair);
            return (*bst->find(Pair)).second;
        }
    }
    //insert pair
    template <class K, class V>
    void map<K, V>::insert(const K& k, const V& v)
    {
        pair<K, V> Pair(k, v);
        BST<char>::iterator it;
        it = bst->find(Pair);
        if (it != NULL)
            *it = Pair;
        else
        {
            bst->insert(Pair);
        }
    }
} // custom
#endif // MAP_H