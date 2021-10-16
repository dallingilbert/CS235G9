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
 *    John McCleve
 *    Dallin Gilbert
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

        // default constructor
        BST()
        {
            root = NULL;
            numElements = 0;
        }

        // copy constructor
        BST(const BST &rhs)
        {
            copyBinaryTree(rhs.root, root);
            numElements = rhs.numElements;
        }

        // destructor
        ~BST()
        {
            deleteBinaryTree(root);
            root = NULL;
        }

        // overloaded operator
        BST &operator=(const BST &rhs);

        // public member methods
        int size();
        bool empty();
        void clear();
        void insert(T t);
        void erase(iterator &it);

        // iterator methods
        iterator find(T t);
        iterator begin();
        iterator end();
        iterator Rbegin();
        iterator Rend();
        BNode *getRoot();

    private:
        BNode *root;
        int numElements;
        void deleteNode(BNode *del, bool right);
        void deleteBinaryTree(BNode *del);
        void copyBinaryTree(BNode *src, BNode *&dest);
        int sizeRecursive(BNode *rec);
    };

    template <class T>
    class BST<T>::BNode
    {
    public:
        T data;
        BNode *pLeft;
        BNode *pRight;
        BNode *pParent;
        bool isRed;

        // default, non-default contstructors
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

        // copy constructor
        BNode(const BNode &rhs)
        {
            data = rhs.data;
            pRight = rhs.pRight;
            pLeft = rhs.pLeft;
            pParent = rhs.pParent;
            isRed = rhs.isRed;
        };

        //assignment operator
        BNode &operator=(const BNode &rhs)
        {
            data = rhs.data;
            pRight = rhs.pRight;
            pLeft = rhs.pLeft;
            pParent = rhs.pParent;
            isRed = rhs.isRed;
            return *this;
        }

        // public member methods
        void addLeft(BNode *pNode, BNode *pAdd);
        void addRight(BNode *pNode, BNode *pAdd);

        void balance(BNode *pNode)
        {
            //do necessary the necessary rotations for the B/R tree
            //case 1 it's the root
            if (!pNode->pParent && !pNode->pLeft && !pNode->pRight)
            {
                pNode->isRed = false;
                return;
            }

            //case 2 parent is not black
            // if (pNode->pParent && pNode->pParent->isRed)
            // {
            //     if (pNode->pParent->pLeft->isRed || pNode->pParent->pRight->isRed)
            //     {
            //         //make it black
            //         pNode->pParent->isRed = false;
            //         //if it has an aunt also make it black
            //         if (pAunt(pNode) && pAunt(pNode)->isRed)
            //         {
            //             pAunt(pNode)->isRed = false;
            //         }
            //     }
            // }

            //case 3 parent and aunt are red, grandparent is black
            if (pNode->pParent && pNode->pParent->isRed && pAunt(pNode) 
            && pAunt(pNode)->isRed && !pGranny(pNode)->isRed)
            {
                //if the grand grandfather is red
                if (pGranny(pNode)->pParent && pGranny(pNode)->pParent->isRed)
                {
                    pNode->isRed = false;
                }
                //if the grand grandfather is black
                else if (pGranny(pNode)->pParent && !pGranny(pNode)->pParent->isRed)
                {
                    pGranny(pNode)->isRed = true;
                    pNode->pParent->isRed = false;
                    pAunt(pNode)->isRed = false;
                }
                //case its the root
                else
                {
                    pGranny(pNode)->isRed = false;
                    pNode->pParent->isRed = false;
                    pAunt(pNode)->isRed = false;
                }
                return;
            }

            //case 4 parent is red aunt is black or non existent
            //case a

            if (pNode->pParent && pNode->pParent->isRed && pGranny(pNode) 
            && !pGranny(pNode)->isRed && pSibling(pNode) && !pSibling(pNode)->isRed 
            && pAunt(pNode) && !pAunt(pNode)->isRed && pNode->pParent->pLeft == pNode 
            && pGranny(pNode)->pLeft == pNode->pParent)
            {
                pNode->addRight(pNode->pParent, pGranny(pNode));
                pGranny(pNode)->addLeft(pGranny(pNode), pSibling(pNode));
                pGranny(pNode)->isRed = true;
                pNode->pParent->isRed = false;
            }
            else if (pNode->pParent && pNode->pParent->pLeft == pNode && pGranny(pNode) 
            && pGranny(pNode)->pLeft == pNode->pParent && !pNode->pParent->pRight 
            && pGranny(pNode)->pParent)
            {
                ///rotate clockwise
                pNode->pParent->pRight = pGranny(pNode);
                if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
                {
                    pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode->pParent);
                }
                else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
                {
                    pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode->pParent);
                }
                pNode->pParent->pRight->pParent = pNode->pParent;
                pNode->pParent->pRight->pLeft = NULL;

                //color respectively
                pNode->pParent->isRed = false;
                pNode->pParent->pRight->isRed = true;
                pNode->isRed = true;
            }
            //case b
            if (pNode->pParent && pNode->pParent->isRed && pGranny(pNode) 
            && !pGranny(pNode)->isRed && pSibling(pNode) && !pSibling(pNode)->isRed 
            && pAunt(pNode) && !pAunt(pNode)->isRed && pNode->pParent->pRight == pNode 
            && pGranny(pNode)->pRight == pNode->pParent)
            {
                pNode->addLeft(pNode->pParent, pGranny(pNode));
                pGranny(pNode)->addRight(pGranny(pNode), pSibling(pNode));
                pGranny(pNode)->isRed = true;
                pNode->pParent->isRed = false;
            }
            else if (pNode->pParent && pNode->pParent->pRight == pNode && pGranny(pNode) 
            && pGranny(pNode)->pRight == pNode->pParent && !pNode->pParent->pLeft 
            && pGranny(pNode)->pParent)
            {
                ///rotate counter-clockwise
                pNode->pParent->pLeft = pGranny(pNode);
                if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
                {
                    pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode->pParent);
                }
                else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
                {
                    pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode->pParent);
                }

                pNode->pParent->pLeft->pParent = pNode->pParent;
                pNode->pParent->pLeft->pRight = NULL;

                //color respectively
                pNode->pParent->isRed = false;
                pNode->pParent->pLeft->isRed = true;
                pNode->isRed = true;
            }
            //case c
            if (pNode->pParent && pNode->pParent->isRed && pGranny(pNode) 
            && !pGranny(pNode)->isRed && pSibling(pNode) && !pSibling(pNode)->isRed 
            && pAunt(pNode) && !pAunt(pNode)->isRed && pNode->pParent->pRight == pNode 
            && pGranny(pNode)->pLeft == pNode->pParent)
            {
                pGranny(pNode)->pLeft = pNode->pRight;
                pNode->pParent->pRight = pNode->pLeft;
                if (pGranny(pNode)->pParent == NULL)
                {
                    pNode->pParent = NULL;
                }
                else if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
                {
                    pGranny(pNode)->pParent->pLeft = pNode;
                }
                else
                {
                    pGranny(pNode)->pParent->pRight = pNode;
                }

                pNode->pRight = pGranny(pNode);
                pNode->pLeft = pNode->pParent;
                pGranny(pNode)->isRed = true;
                pNode->isRed = false;
            }
            else if (pNode->pParent && pNode->pParent->pRight == pNode 
            && pGranny(pNode) && pGranny(pNode)->pLeft == pNode->pParent 
            && !pNode->pParent->pLeft && pGranny(pNode)->pParent)
            {
                ///rotate counter-clockwise
                pNode->pLeft = pNode->pParent;
                pNode->pRight = pGranny(pNode);
                if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
                {
                    pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode);
                }
                else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
                {
                    pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode);
                }

                pNode->pLeft->pParent = pNode;
                pNode->pRight->pParent = pNode;
                pNode->pRight->pLeft = NULL;
                pNode->pLeft->pRight = NULL;

                //color respectively
                pNode->isRed = false;
                pNode->pLeft->isRed = true;
                pNode->pRight->isRed = true;
            }

            //case d
            if (pNode->pParent && pNode->pParent->isRed && pGranny(pNode) 
            && !pGranny(pNode)->isRed && pSibling(pNode) && !pSibling(pNode)->isRed 
            && pAunt(pNode) && !pAunt(pNode)->isRed && pNode->pParent->pLeft == pNode 
            && pGranny(pNode)->pRight == pNode->pParent)
            {
                pGranny(pNode)->pRight = pNode->pLeft;
                pNode->pParent->pLeft = pNode->pRight;
                if (pGranny(pNode)->pParent == NULL)
                {
                    pNode->pParent = NULL;
                }
                else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
                {
                    pGranny(pNode)->pParent->pRight = pNode;
                }
                else
                {
                    pGranny(pNode)->pParent->pLeft = pNode;
                }

                pNode->pLeft = pGranny(pNode);
                pNode->pRight = pNode->pParent;
                pGranny(pNode)->isRed = true;
                pNode->isRed = false;
            }
            else if (pNode->pParent && pNode->pParent->pLeft == pNode
            && pGranny(pNode) && pGranny(pNode)->pRight == pNode->pParent
            && !pNode->pParent->pRight && pGranny(pNode)->pParent)
            {
                ///rotate counter-clockwise
                pNode->pRight = pNode->pParent;
                pNode->pLeft = pGranny(pNode);

                if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
                {
                    pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode);
                }
                else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
                {
                    pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode);
                }

                pNode->pRight->pParent = pNode;
                pNode->pLeft->pParent = pNode;
                pNode->pRight->pLeft = NULL;
                pNode->pLeft->pRight = NULL;

                //color respectively
                pNode->isRed = false;
                pNode->pLeft->isRed = true;
                pNode->pRight->isRed = true;
            }
        }

    private:
        /**************************************************
        * pSibling
        * returns the sibling of a node
        *************************************************/
        BNode *pSibling(BNode *pNode)
        {
            if (!pNode->pParent)
                return NULL;
            if (pNode->pParent->pLeft == pNode)
                return pNode->pParent->pRight;
            else if (pNode->pParent->pRight == pNode)
                return pNode->pParent->pLeft;
        }
        /**************************************************
        * pAunt
        * returns the aunt of a node
        *************************************************/
        BNode *pAunt(BNode *pNode)
        {
            if (!pNode->pParent || !pNode->pParent->pParent)
                return NULL;
            if (pNode->pParent == pNode->pParent->pParent->pLeft)
                return pNode->pParent->pParent->pRight;
            else if (pNode->pParent == pNode->pParent->pParent->pRight)
                return pNode->pParent->pParent->pLeft;
        }

        /**************************************************
        * pGranny
        * returns the grandparent of a node
        *************************************************/
        BNode *pGranny(BNode *pNode)
        {
            if (!pNode->pParent->pParent)
                return NULL;
            else
                return pNode->pParent->pParent;
        }
        void verifyRB(int depth)
        {
        }
        void verifyBST()
        {
        }
    };

    template <class T>
    class BST<T>::iterator
    {
    private:
        typename BST<T>::BNode *p;

    public:
        // constructors, destructors, and assignment operator
        iterator() : p(NULL){};
        iterator(BNode *p) : p(p){};

        iterator(const iterator &rhs)
        {
            if (NULL != rhs.p)
                p = rhs.p;
            else
                //if the iterator is null just set everything to null
                p = NULL;
        }
        iterator &operator=(const iterator &rhs)
        {
            this->p = rhs.p;
            return *this;
        }

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
                BNode *pSave = p;

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
        iterator operator++(int postfix)
        {
            BNode *tmp = p;
            if (p)
            {
                if (p->pRight)
                {
                    p = p->pRight;
                    while (p->pLeft)
                        p = p->pLeft;
                    return p;
                }
                if (p->pRight == NULL && p->pParent->pLeft == p)
                {
                    p = p->pParent;
                    return p;
                }
                if (p->pRight == NULL && p->pParent->pRight == p)
                {
                    while (p->pParent && p->pParent->pRight == p)
                        p = p->pParent;
                    p = p->pParent;
                    return p;
                }
            }
            else
                iterator(tmp);
        }

        // prefix decrement
        iterator &operator--()
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
                BNode *pSave = p;

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
        iterator operator--(int postfix)
        {
            BNode *tmp = p;
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
                BNode *pSave = p;

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
        friend void BST<T>::erase(BST<T>::iterator &it);
        friend void BST<T>::insert(const T t);
    };

    /*****************************************************
    * ADD LEFT
    * Add a node to the left of our parent node using a
    * passed in node
    ****************************************************/
    template <class T>
    void BST<T>::BNode::addLeft(BNode *pNode, BNode *pAdd)
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
            throw("ERROR: Unable to allocate a node");
        }
        return;
    }

    /*****************************************************
    * ADD RIGHT
    * Add a node to the right of our parent node using a
    * passed in node
    ****************************************************/
    template <class T>
    void BST<T>::BNode::addRight(BNode *pNode, BNode *pAdd)
    {
        try
        {
            if (pAdd != NULL)
                pAdd->pParent = pNode;
            pNode->pRight = pAdd;
        }
        catch (std::bad_alloc)
        {
            throw("ERROR: Unable to allocate a node");
        }
        return;
    }

    /*****************************************************
    * ASSIGNMENT OPERATOR
    * Overload the assignment operator to copy data from
    * one BST to the next
    ****************************************************/
    template <class T>
    BST<T> &BST<T>::operator=(const BST &rhs)
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

    /*****************************************************
    * BST SIZE
    * Returns the size of our Binary Search Tree
    ****************************************************/
    template <class T>
    int BST<T>::size()
    {
        if (root == NULL)
            return 0;
        else
            return sizeRecursive(root);
    }

    /*****************************************************
    * BST EMPTY
    * Returns a boolean value that tells us whether or not
    * the Binary Search Tree is empty or not
    ****************************************************/
    template <class T>
    bool BST<T>::empty()
    {
        return size() == 0;
    }

    /*****************************************************
    * BST CLEAR
    * Removes the values from our Tree and resets the 
    * values to represent the correct state
    ****************************************************/
    template <class T>
    void BST<T>::clear()
    {
        if (root != NULL)
            deleteBinaryTree(root);
        root = NULL;
        numElements = 0;
    }

    /*****************************************************
    * BST INSERT
    * Inserts the correct value within our binary search
    * tree
    ****************************************************/
    template <class T>
    void BST<T>::insert(T t)
    {
        BNode *pNode = new BNode(t);
        BNode *key = new BNode();
        //if its the root
        if (size() == 0)
        {
            root = pNode;
            numElements++;
            pNode->balance(root);
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
        //pNode->balance(pNode);
    }

    /*****************************************************
    * BST ERASE
    * Erases the specified value from our binary search 
    * tree
    ****************************************************/
    template <class T>
    void BST<T>::erase(iterator &it)
    {
        //case 1 no children
        if (it.p->pRight == NULL && it.p->pLeft == NULL)
        {
            if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
                it.p->pParent->pRight = NULL;
            if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
                it.p->pParent->pLeft = NULL;
            delete it.p;
            it.p = NULL;
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
            it.p = NULL;
        }
        else if (it.p->pRight != NULL && it.p->pLeft == NULL)
        {
            it.p->pRight->pParent = it.p->pParent;
            if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
                it.p->pParent->pRight = it.p->pRight;
            if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
                it.p->pParent->pLeft = it.p->pRight;
            delete it.p;
            it.p = NULL;
        }
        //case 3 two children
        else if (it.p->pLeft != NULL && it.p->pRight != NULL)
        {
            iterator successor = it.p;
            successor++;
            assert(successor.p->pLeft == NULL);

            if (successor.p->pRight != NULL)
            {
                successor.p->pParent->pLeft = successor.p->pRight;
                successor.p->pRight->pParent = successor.p->pParent;
            }
            else
                successor.p->pParent->pLeft = NULL;

            if (it.p->pParent != NULL)
            {
                successor.p->pParent = it.p->pParent;
                it.p->pParent->pRight = successor.p;
            }
            else
            {
                this->root = successor.p;
                successor.p->pParent = NULL;
            }

            successor.p->pRight = it.p->pRight;
            it.p->pRight->pParent = successor.p;

            if (it.p->pLeft != NULL)
            {
                successor.p->pLeft = it.p->pLeft;
                it.p->pLeft->pParent = successor.p;
            }

            delete it.p;
            it.p = NULL;
            return;
        }
    }

    /*****************************************************
    * ITERATOR FIND
    * Returns the index of our iterator at the location
    * where our value is found, if not we return the end
    * of our iterator
    ****************************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::find(T t)
    {
        for (iterator it = begin(); it != end(); ++it)
            if (*it == t)
                return it;

        return end();
    }

    /*****************************************************
    * ITERATOR BEGIN
    * Returns the index of our iterator at the beginning
    * of our Binary Search Tree
    ****************************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::begin()
    {
        BNode *x = root;
        if (x)
        {
            while (x->pLeft != NULL)
            {
                x = x->pLeft;
            }
        }
        return iterator(x);
    }

    /*****************************************************
    * ITERATOR END
    * Returns the end of our iterator
    ****************************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::end()
    {
        return iterator(NULL);
    }

    /*****************************************************
    * ITERATOR RBEGIN
    * Returns the index of our iterator using a reverse 
    * beginning iterator
    ****************************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::Rbegin()
    {
        BNode *x = root;
        if (x)
        {
            while (x->pRight != NULL)
            {
                x = x->pRight;
            }
        }
        return iterator(x);
    }

    /*****************************************************
    * ITERATOR REND
    * Returns the index of our iterator using a reverse 
    * end iterator
    ****************************************************/
    template <class T>
    typename BST<T>::iterator BST<T>::Rend()
    {
        return iterator(NULL);
    }

    /*****************************************************
    * BST DELETENODE
    * Deletes the node at a given location
    ****************************************************/
    template <class T>
    void BST<T>::deleteNode(BNode *del, bool right)
    {
        iterator it = find(del);
        erase(it);
    }

    /*****************************************************
    * BST DELETEBINARYTREE
    * Deletes the binary tree, both parent and children
    * at a given node
    ****************************************************/
    template <class T>
    void BST<T>::deleteBinaryTree(BNode *del)
    {
        if (del == NULL)
            return;
        else
        {
            deleteBinaryTree(del->pLeft);
            deleteBinaryTree(del->pRight);
            delete del;
            del = NULL;
        }
    }

    /*****************************************************
    * BST COPYBINARYTREE
    * Copies the binary tree from the source node to the
    * destination node
    ****************************************************/
    template <class T>
    void BST<T>::copyBinaryTree(BNode *src, BNode *&dest)
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
    * BST SIZERECURSIVE
    * Returns the size of the BST
    *************************************************/
    template <class T>
    int BST<T>::sizeRecursive(BNode *rec)
    {
        if (!rec)
            return 0;
        else
            return sizeRecursive(rec->pLeft) + 1 + sizeRecursive(rec->pRight);
    }

    /*****************************************************
    * BST GETROOT
    * Returns the root of our Binary Node
    ****************************************************/
    template <class T>
    typename BST<T>::BNode *BST<T>::getRoot()
    {
        return root;
    }

}
#endif /* bst_h */
