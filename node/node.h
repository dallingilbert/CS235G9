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
#endif // NODE_H

template <class T>
void copy(Node<T> *n)
{
    // n is our node pointer which we will use to
    // copy a linked-list

}

template <class T>
Node<T> insert(Node<T> *n1, Node<T> *n2)
{
    // n1 is our reference node where we are adding n2 
    return *n2;
}
template <class T>
Node<T> find(Node<T> *front, Node<T> *value)
{
    // find the node equal to our parameter in our list
    return *value;
}

template <class T>
void freeData(Node<T> *pHead)
{
    // use pHead to clear the rest of the nodes in our list
    return;
}

template <class T>
void remove(Node<T> *n)
{
    // use n to remove the node passed as a parameter and return a pointer
    // to the previous node (default) or (non-default) return a pointer to
    // the next node
    
    return;
}
