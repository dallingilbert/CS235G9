#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <class T>
class Node {
    public:
        T data;
        Node *pNext;
        Node *pPrev;

        // default constructor
        Node()
        {
            this->data = NULL;
            this->pNext = NULL;
            this->pPrev = NULL;
        }

        // non-default constructor
        Node(const T& t)
        {
            this->data = t;
            this->pNext = NULL;
            this->pPrev = NULL;
        }
};

template <class T>
Node<T>* copy(Node<T>* pSource)
{
    // n is our node pointer which we will use to
    // copy a linked-list
    Node<T>* pDestination = new Node<T>(pSource->data);
    Node<T>* pSrc = pSource;
    Node<T>* pDes = pDestination;
    
    for (pSrc; pSrc->pNext != NULL; pSrc = pSrc->pNext)
        pDes = insert(pDes, pSrc->pNext->data, true);
        
    return pDestination;
}

template <class T>
Node<T>* insert(Node<T> * pSource, const T & t, bool after = false)
{
    // n1 is our reference node where we are adding n2
    Node<T>* pNew = new Node<T>(t);
    
    if (pSource != NULL && after == false)
    {
        //point new node to prev and next nodes
        pNew->pNext = pSource;
        pNew->pPrev = pSource->pPrev;
        
        //point prev and next nodes to the new node
        pSource->pPrev = pNew;
        
        if (pNew->pPrev != NULL)
        {
            pNew->pPrev->pNext = pNew;
        }
    }
    //check if it'll be inserted after, and if it exists
    else if (pSource != NULL && after == true)
    {
        //point new node to prev and next nodes
        pNew->pNext = pSource->pNext;
        pNew->pPrev = pSource;
        
        //point prev and next nodes to the new node
        pSource->pNext = pNew;
        
        if (pNew->pNext != NULL)
        {
            pNew->pNext->pPrev = pNew;
        }
    }

    return pNew;
}

template <class T>
Node<T>* find(Node<T>* front, const T& t)
{
    // find the node equal to our parameter in our list
    if (front == NULL || front->pNext == NULL && front->data == t)
        return front;
    else
    {
        for (Node<T>* p = front; p != NULL; p = p->pNext)
        {
            //searches if the data is in the list
            if (p->data == t)
            {
                //if value is found
                return p;
            }
        }
    }
    return NULL;
}
/************************************************
 * INSERTION OPERATOR
 * Overload the insertion operator to display
 * a linked list.
 ***********************************************/
template <class T>
std::ostream& operator << (std::ostream& out, const Node <T>* pHead)
{
    for (const Node <T>* p = pHead; p; p = p->pNext)
    {
        out << p->data;
        
        if (p->pNext)
            out << ", ";
    }
    
    return out;
}


template <class T>
void freeData(Node<T>* &pHead)
{
    // use pHead to clear the rest of the nodes in our list
    while (pHead != NULL)
    {
        Node<T>* pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    }
}

template <class T>
Node<T>* remove(Node<T> *n)
{
    // use n to remove the node passed as a parameter and return a pointer
    // to the previous node (default) or (non-default) return a pointer to
    // the next node
    if (n == NULL)
        return NULL;
        
    if (n->pPrev != NULL)
        n->pPrev->pNext = n->pNext;
        
    if (n->pNext != NULL)
        n->pNext->pPrev = n->pPrev;

    //return either the prev or next node
    Node<T>* pReturn;
    
    if (n->pPrev != NULL)
        pReturn = n->pPrev;
    else
        pReturn = n->pNext;
        
    delete n;
    
    return pReturn;
}

#endif // NODE_H