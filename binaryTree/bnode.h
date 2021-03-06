/***********************************************************************
 * Header:
 *    Binary Tree
 * Summary:
 *    This class contains the notion of a list: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the list, list, list, list, list, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       Binary Tree             : similar to std::list
 * Author
 *    Br. Helfrich
 ************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <iostream>
using namespace std;

template <class T>
class BNode
{
public:
    // member variables
    T data;
    BNode *pLeft;
    BNode *pRight;
    BNode *pParent;

    // default, non-default constructors
    BNode()
    {
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
        data = T();
    }

    BNode(const T &t)
    {
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
        data = t;
    }
};

// functions to manipulate our binary tree class

template <class T>
void addLeft(BNode<T> *pNode, const T &t)
{
    // since no node is passed in, allocate space for one
    try
    {
        BNode<T> *tempNode = new BNode<T>(t);

        // set pParent of tempNode
        tempNode->pParent = pNode;

        // set pLeft to tempNode
        pNode->pLeft = tempNode;
    }
    catch (string e)
    {
        throw "Unable to allocate a node";
    }
}

template <class T>
void addLeft(BNode<T> *pNode, BNode<T> *pAdd)
{
    // set the parent node
    if (pAdd != NULL)
        pAdd->pParent = pNode;

    // set pLeft of node
    pNode->pLeft = pAdd;
}

template <class T>
void addRight(BNode<T> *pNode, const T &t)
{
    // since no node is passed in, allocate space for one
    try
    {
        BNode<T> *tempNode = new BNode<T>(t);

        // set pParent of tempNode
        tempNode->pParent = pNode;

        // set pRight to tempNode
        pNode->pRight = tempNode;
    }
    catch (string e)
    {
        throw "Unable to allocate a node";
    }
}

template <class T>
void addRight(BNode<T> *pNode, BNode<T> *pAdd)
{
    // set the parent node
    if (pAdd != NULL)
        pAdd->pParent = pNode;

    // set pRight of node
    pNode->pRight = pAdd;
}

template <class T>
int sizeBTree(BNode<T> *pNode)
{
    if (pNode == NULL)
        return 0;
    else
        return sizeBTree(pNode->pLeft) + 1 + sizeBTree(pNode->pRight);
}

template <class T>
void deleteBTree(BNode<T> *pNode)
{
    if (pNode == NULL)
        return;

    // delete the tree
    deleteBTree(pNode->pLeft);
    deleteBTree(pNode->pRight);
    
    delete pNode;
}

template <class T>
BNode<T>* copyBTree(BNode<T> *source)
{
    if (source == NULL)
        return source;

    BNode<T> *destination = new BNode<T>(source->data);

    // copy over pointer to left node
    destination->pLeft = copyBTree(source->pLeft);

    if (destination->pLeft != NULL)
        destination->pLeft->pParent = destination;

    destination->pRight = copyBTree(source->pRight);

    if (destination->pRight != NULL)
        destination->pRight->pParent = destination;

    return destination;
}

template <class T>
ostream &operator<<(ostream &out, const BNode<T> *BNode)
{
    if (BNode == NULL)
    {
        return out;
    }

    out << BNode->pLeft;
    out << BNode->data << " ";
    out << BNode->pRight;

    return out;
}
#endif // BNODE_H
