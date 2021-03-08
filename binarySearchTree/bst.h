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
template <class T>
class BST
{
public:
   class BNode;
   class iterator;
   class reverse_iterator;
   BST()
   {
       root = NULL;
       numElements = 0;
   }

   BST(const BST& rhs)
   {
       copyBinaryTree(rhs.root, root);
       numElements = rhs.numElements;
   }

   ~BST()
   {
       deleteBinaryTree(root);
   }

   BST& operator = (const BST& rhs);
   int size();
   bool empty();
   void clear();
   void insert(T  t);
   void erase(iterator& it);
   iterator find(T t);
   iterator begin();
   iterator end();
   iterator Rbegin();
   iterator Rend();
   BNode* getRoot();

private:
    BNode* root;
    int numElements;
    void deleteNode(BNode* del, bool right);
    void deleteBinaryTree(BNode* del);
    void copyBinaryTree(BNode* src, BNode* &dest);
    int sizeRecursive(BNode* rec);
};

template <class T>
class BST<T>::BNode
{
public:
   T data;
   BNode* pLeft;
   BNode* pRight;
   BNode* pParent;
   bool isRed;

   BNode()
   {
      data = T();
      pLeft = NULL;
      pRight = NULL;
      pParent = NULL;
      isRed = true;
   }

   BNode(T data)
   {
      this->data = data;
      pLeft = NULL;
      pRight = NULL;
      pParent = NULL;
      isRed = true;
   }

   BNode(const BNode& rhs)
   {
       data = rhs.data;
       pRight = rhs.pRight;
       pLeft = rhs.pLeft;
       pParent = rhs.pParent;
       isRed = rhs.isRed;
   };
   //assignment operator
   BNode& operator = (const BNode& rhs)
   {
       data = rhs.data;
       pRight = rhs.pRight;
       pLeft = rhs.pLeft;
       pParent = rhs.pParent;
       isRed = rhs.isRed;
       return *this;
   }
   void addLeft(BNode* pNode, BNode* pAdd);
   void addRight(BNode* pNode, BNode* pAdd);
private:
   void verifyRB(int depth)
   {

   }
   void verifyBST()
   {

   }
   void balance()
   {

   }

};

template <class T>
class BST<T>::iterator
{
private:
    typename BST<T>::BNode* p;
public:
   // constructors, destructors, and assignment operator
   iterator() : p(NULL) {};
   iterator(BNode* p) : p(p) {};

   iterator(const iterator & rhs)
   {
       if (NULL != rhs.p)
           p = rhs.p;
       else
           //if the iterator is null just set everything to null
           p = NULL;
   }
   iterator & operator = (const iterator & rhs)
   {
       this->p = rhs.p;
       return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }

   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }


   // dereference operator
   T& operator*() { return p->data; }
   const T& operator * () const { return p->data; }

   // prefix increment
   iterator& operator ++ ()
   {
       if (p)
       {
           if (NULL != p->pRight)
           {
               // go right
               p = p->pRight;

               // jig left - there might be more left-most children
               while (p->pLeft)
                   p = p->pLeft;
               return *this;
           }
           // there are no right children, the left are done
           assert(NULL == p->pRight);
           BNode* pSave = p;

           // go up
           p = p->pParent;

           // if the parent is the NULL, we are done!
           if (NULL == p)
               return *this;

           // if we are the left-child, got to the parent.
           if (pSave == p->pLeft)
               return *this;

           // we are the right-child, go up as long as we are the right child!
           while (NULL != p && pSave == p->pRight)
           {
               pSave = p;
               p = p->pParent;
           }
           return *this;
       }
       else
       {
           return *this;
       }
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
       BNode* tmp = p;
       if (p)
       {
           // if there is a right node, take it
           if (NULL != p->pRight)
           {
               // go right
               p = p->pRight;

               // jig left - there might be more left-most children
               while (p->pLeft)
                   p = p->pLeft;
               return iterator(tmp);
           }

           // there are no right children, the left are done
           assert(NULL == p->pRight);
           BNode* pSave = p;

           // go up
           p = p->pParent;

           // if the parent is the NULL, we are done!
           if (NULL == p)
               return iterator(tmp);

           // if we are the left-child, got to the parent.
           if (pSave == p->pLeft)
               return iterator(tmp);

           // we are the right-child, go up as long as we are the right child!
           while (NULL != p && pSave == p->pRight)
           {
               pSave = p;
               p = p->pParent;
           }
           return iterator(tmp);
      }
       else
           iterator(tmp);
   }

   // prefix decrement
   iterator & operator -- ()
   {
       if (p)
       {
           // if there is a left node, take it
           if (NULL != p->pLeft)
           {
               // go left
               p = p->pLeft;

               // jig right - there might be more right-most children
               while (p->pRight)
                   p = p->pRight;
               return *this;
           }
           // there are no left children, the right are done
           assert(NULL == p->pLeft);
           BNode* pSave = p;

           // go up
           p = p->pParent;

           // if the parent is the NULL, we are done!
           if (NULL == p)
               return *this;

           // if we are the right-child, got to the parent.
           if (pSave == p->pRight)
               return *this;

           // we are the left-child, go up as long as we are the left child!
           while (NULL != p && pSave == p->pLeft)
           {
               pSave = p;
               p = p->pParent;
           }
           return *this;
       }
       else
           return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
       BNode* tmp = p;
       if (p)
       {
           if (NULL != p->pLeft)
           {
               // go left
               p = p->pLeft;

               // jig right - there might be more right-most children
               while (p->pRight)
                   p = p->pRight;
               return iterator(tmp);
           }

           // there are no left children, the right are done
           assert(NULL == p->pLeft);
           BNode* pSave = p;

           // go up
           p = p->pParent;

           // if the parent is the NULL, we are done!
           if (NULL == p)
               return iterator(tmp);

           // if we are the right-child, got to the parent.
           if (pSave == p->pRight)
               return iterator(tmp);

           // we are the left-child, go up as long as we are the left child!
           while (NULL != p && pSave == p->pLeft)
           {
               pSave = p;
               p = p->pParent;
           }
           return iterator(tmp);
       }
       else
           iterator(tmp);
   }
   friend void BST<T>::erase(BST<T>::iterator& it);
   friend void BST<T>::insert(const T t);
};

/*****************************************************
 * ADD LEFT
 * Add a node to the left of our parent node using a
 * passed in node
 ****************************************************/
template <class T>
void BST<T>::BNode::addLeft(BNode* pNode, BNode* pAdd)
{
    // set the parent node
    try
    {
        if (pAdd != NULL)
            pAdd->pParent = pNode;

        // set pLeft of node
        pNode->pLeft = pAdd;
     }
    catch (std::bad_alloc)
    {
        throw ("ERROR: Unable to allocate a node");
    }
    return;
}

/*****************************************************
 * ADD RIGHT
 * Add a node to the right of our parent node using a
 * passed in node
 ****************************************************/
template <class T>
void BST<T>::BNode::addRight(BNode* pNode, BNode* pAdd)
{
    try
    {
        if (pAdd != NULL)
            pAdd->pParent = pNode;
        pNode->pRight = pAdd;
    }
    catch (std::bad_alloc)
    {
        throw ("ERROR: Unable to allocate a node");
    }
    return;
}

template <class T>
BST<T> & BST<T>::operator = (const BST & rhs)
{
    if (root != NULL)
        deleteBinaryTree(root);
    if (rhs.root != NULL)
    {
        root = new BNode(rhs.root->data);
        copyBinaryTree(rhs.root, root);
        numElements = rhs.numElements;
    }
    return *this;
}

template <class T>
int BST<T>::size()
{
    return sizeRecursive(root);
}

template <class T>
bool BST<T>::empty()
{
   return size() == 0;
}

template <class T>
void BST<T>::clear()
{
    if (root != NULL)
     deleteBinaryTree(root);
    root = NULL;
    numElements = 0;
}

template <class T>
void BST<T>::insert(T t)
{
    BNode* pNode = new BNode(t);
    BNode* key = new BNode();
    //if its the root
    if (size() == 0)
    {
        root = pNode;
        numElements++;
       //pNode->balance(pNode);
        return;
    }
    //search where to insert the node
    for (iterator it = begin(); it != end(); ++it)
    {
        if (*it < pNode->data)
        {
            key = it.p;
            continue;
        }
        else if (*it > pNode->data)
        {
            key = it.p;
            break;
        }
        //TODO case if equals to the last element
        else if (*it == pNode->data)
        {
            ++it;
            key = it.p;
            break;
        }
    }

    //case 1 if the element was bigger tha all the nodes
    if (key->data < pNode->data)
    {
        //insert at the end & furthest right
        key->addRight(key, pNode);
    }
    else
    {
        //insert to the left of the key
        if (!key->pLeft && !key->pRight)
            key->addLeft(key, pNode);
        //insert to the right of the left element of the key
        else if (key->pLeft && key->pLeft->pRight)
        {
            key = key->pLeft;
            while (key->pRight)
                key = key->pRight;
            pNode->addRight(key, pNode);
        }
        else if (key->pLeft && !key->pLeft->pRight)
            pNode->addRight(key->pLeft, pNode);
        else if (!key->pLeft)
            pNode->addLeft(key, pNode);
    }
    numElements++;
   // pNode->balance(pNode);
}

template <class T>
void BST<T>::erase(iterator& it)
{
    //case 1 no children
    if (it.p->pRight == NULL && it.p->pLeft == NULL)
    {
        if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
            it.p->pParent->pRight = NULL;
        if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
            it.p->pParent->pLeft = NULL;
        delete it.p;
        return;
    }
    // case 2 one child
    if (it.p->pRight == NULL && it.p->pLeft != NULL)
    {
        it.p->pLeft->pParent = it.p->pParent;
        if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
            it.p->pParent->pRight = it.p->pLeft;
        if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
            it.p->pParent->pLeft = it.p->pLeft;
        delete it.p;
    }
    else if (it.p->pRight != NULL && it.p->pLeft == NULL)
    {
        it.p->pRight->pParent = it.p->pParent;
        if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
            it.p->pParent->pRight = it.p->pRight;
        if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
            it.p->pParent->pLeft = it.p->pRight;
        delete it.p;
    }
    //case 3 two children
    if (it.p->pLeft != NULL && it.p->pRight != NULL)
    {
        while (it.p->pLeft != NULL)
            it.p = it.p->pLeft;


        ////point the left node to the right node as parent
        //it.p->pLeft->pParent = it.p->pRight;
        ////point the right node to the parent of it
        //it.p->pRight->pParent = it.p->pParent;
        ////point the parent of it the right node either to the left or right of it
        //if (it.p->pParent->pLeft == it.p)
        //    it.p->pParent->pLeft = it.p->pRight;
        //else
        //    it.p->pParent->pRight = it.p->pRight;
        ////point the right to the left as a left child
        //it.p->pRight->pLeft = it.p->pLeft;

        delete it.p;
        return;
    }
    // if its the root and has NO grandchildren
    else if (!it.p->pParent && it.p->pLeft && !it.p->pLeft->pLeft && !it.p->pLeft->pRight
        && it.p->pRight && !it.p->pRight->pLeft && !it.p->pRight->pRight)
    {
        //point the left node to the right node as parent
        it.p->pLeft->pParent = it.p->pRight;
        //point the right node to the parent of it
        it.p->pRight->pParent = NULL;
        //point the right to the left as a left child
        it.p->pRight->pLeft = it.p->pLeft;
        root = it.p->pRight;
        delete it.p;
        return;
    }
    // if its not the root and has grandchildren the left but not on the right
    else if (it.p->pParent && it.p->pLeft && it.p->pRight
        && (it.p->pLeft->pLeft || it.p->pLeft->pRight)
        && !it.p->pRight->pLeft)
    {
        //point the parent to the the new node
        it.p->pLeft->pParent = it.p->pRight;
        //point the parent of it the right node either to the left or right of it
        if (it.p->pParent->pLeft == it.p)
            it.p->pParent->pLeft = it.p->pRight;
        else
            it.p->pParent->pRight = it.p->pRight;
        //point new node to its realtives
        it.p->pRight->pLeft = it.p->pLeft;
        it.p->pRight->pParent = it.p->pParent;
        delete it.p;
        return;
    }
    // if its not the root and has grandchildren on the right but not on the left
    else if (it.p->pParent && it.p->pRight && it.p->pLeft
        && (it.p->pRight->pLeft || it.p->pRight->pRight)
        && !it.p->pLeft->pRight)
    {
        //point the parent to the the new node
        it.p->pRight->pParent = it.p->pLeft;
        //point the parent of it the right node either to the left or right of it
        if (it.p->pParent->pLeft == it.p)
            it.p->pParent->pLeft = it.p->pLeft;
        else
            it.p->pParent->pRight = it.p->pLeft;
        //point new node to its realtives
        it.p->pLeft->pRight = it.p->pRight;
        it.p->pLeft->pParent = it.p->pParent;
        delete it.p;
        return;
    }
}

template <class T>
typename BST<T>::iterator BST<T>::find(T t)
{
    for (iterator it = begin(); it != end(); ++it)
        if (*it == t)
            return it;
    return end();
}


template <class T>
typename BST<T>::iterator BST<T>::begin()
{
    BNode* x = root;
    if (x)
    {
        while (x->pLeft != NULL)
        {
            x = x->pLeft;
        }
    }
   return iterator(x);
}

template <class T>
typename BST<T>::iterator BST<T>::end()
{
   return iterator(NULL);
}

template <class T>
typename BST<T>::iterator BST<T>::Rbegin()
{
    BNode* x = root;
    if (x)
    {
        while (x->pRight != NULL)
        {
            x = x->pRight;
        }
    }
    return iterator(x);
}

template <class T>
typename BST<T>::iterator BST<T>::Rend()
{
    return iterator(NULL);
}

template <class T>
void BST<T>::deleteNode(BNode* del, bool right)
{
    iterator it = find(del);
    erase(it);
}

template <class T>
void BST<T>::deleteBinaryTree(BNode* del)
{
    if (del == NULL)
        return;
    else {
        deleteBinaryTree(del->pLeft);
        deleteBinaryTree(del->pRight);
        delete del;
        del = NULL;
    }
}

template <class T>
void BST<T>::copyBinaryTree(BNode* src, BNode* &dest)
{
    if (src == NULL)
        return;

    dest = new BNode(src->data);

    // copy over pointer to left node
   copyBinaryTree(src->pLeft, dest->pLeft);

    if (dest->pLeft != NULL)
        dest->pLeft->pParent = dest;

    copyBinaryTree(src->pRight, dest->pRight);

    if (dest->pRight != NULL)
        dest->pRight->pParent = dest;
    return;
}

/**************************************************
 * BST :: sizeRecursive
 * RETURN: size of the BST
 *************************************************/
template <class T>
int BST<T>::sizeRecursive(BNode* rec)
{
    if (!rec)
        return 0;
    else
        return sizeRecursive(rec->pLeft) + 1 + sizeRecursive(rec->pRight);
}
template <class T>
typename BST<T>::BNode* BST<T>::getRoot()
{
   return root;
}

}
#endif /* bst_h */
