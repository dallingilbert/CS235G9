/***********************************************************************
* Program:
*    Week 08, Binary Trees 
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the BinaryNode class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>    // for CIN and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "bnode.h"     // your BinaryNode class should be in bnode.h
#include "huffman.h"   // for huffman()
using namespace std;


// prototypes for our four test functions
void testSimple();
void testAdd();
void testDisplay();
void testMerge();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testAdd()
#define TEST3   // for testDisplay()
#define TEST4   // for testMerge()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a BinaryNode\n";
   cout << "\t2. The above plus add a few nodes to create a Binary Tree\n";
   cout << "\t3. The above plus display the contents of a Binary Tree\n";
   cout << "\t4. The above plus merge Binary Trees\n";
   cout << "\ta. To generate Huffman codes\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
      {
         // get the filename
         string fileName;
         cout << "Enter the filename containing the value frequencies.\n";
         cout << "Enter \"quit\" when done.\n";

         cout << "> ";
         cin  >> fileName;

         while (fileName != "quit")
         {
            //huffman(fileName);
            cout << "> ";
            cin  >> fileName;
         }
         break;
      }
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testAdd();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testDisplay();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testMerge();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a BinaryNode: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   try
   {
      // Test1: a bool Stack with defeault constructor
      cout << "Create a bool BinaryNode using the default constructor\n";
      BNode <bool> tree;
      cout << "\tSize:    " << sizeBTree(&tree) << endl;

      // Test2: double Stack with non-default constructor
      cout << "Create a double BinaryNode using the non-default constructor\n";
      BNode <double> *pTree = new BNode <double>(3.14159);
      cout << "\tSize:    " << sizeBTree(pTree) << endl;
      delete pTree;
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif //TEST1
}

/*******************************************
 * TEST ADD
 * Add a few nodes together to create a tree, then
 * destroy it when done
 *****************************************/
void testAdd()
{
#ifdef TEST2
   try
   {
      // create
      BNode <int> * pTree = new BNode <int> (1);

      // add 2 to the left and 3 to the right
      addLeft(pTree, 2);
      addRight(pTree, 3);

      // add 4 and 5 off the left node
      addLeft(pTree->pLeft, 4);
      addRight(pTree->pLeft, new BNode <int> (5));
      // add one node using the other version of addRight()

      // add 6 and 7 to the right node
      addLeft(pTree->pRight, 6);
      addRight(pTree->pRight, 7);

      // now display the results:
      cout << "The elements in the binary tree:\n";
      cout << "\tRoot......... " << pTree->data                 << endl;
      cout << "\tLeft......... " << pTree->pLeft->data          << endl;
      cout << "\tRight........ " << pTree->pRight->data         << endl;
      cout << "\tLeft-Left.... " << pTree->pLeft->pLeft->data   << endl;
      cout << "\tLeft-Right... " << pTree->pLeft->pRight->data  << endl;
      cout << "\tRight-Left... " << pTree->pRight->pLeft->data  << endl;
      cout << "\tRight-Right.. " << pTree->pRight->pRight->data << endl;
      cout << "\tSize: "         << sizeBTree(pTree)            << endl;

      // double-check the parents
      assert(pTree->pLeft->pParent  ==  pTree);
      assert(pTree->pRight->pParent ==  pTree);
      assert(pTree->pLeft ->pLeft ->pParent  ==  pTree->pLeft);
      assert(pTree->pLeft ->pRight->pParent  ==  pTree->pLeft);
      assert(pTree->pRight->pLeft ->pParent  ==  pTree->pRight);
      assert(pTree->pRight->pRight->pParent  ==  pTree->pRight);
      assert(pTree->pLeft ->pLeft ->pParent->pParent  ==  pTree);
      assert(pTree->pLeft ->pRight->pParent->pParent  ==  pTree);
      assert(pTree->pRight->pLeft ->pParent->pParent  ==  pTree);
      assert(pTree->pRight->pRight->pParent->pParent  ==  pTree);
      cout << "All the parent nodes are correctly set\n";
      
      // move some nodes around
      BNode <int> * pSix   = pTree->pRight->pLeft;
      BNode <int> * pSeven = pTree->pRight->pRight;
      addRight(pTree->pRight, pSix);
      addLeft(pTree->pRight, pSeven);
      assert(pTree->pRight->pRight->data == 6);
      assert(pTree->pRight->pLeft->data == 7);
      cout << "Was able to move the '6' and '7' nodes\n";
   
      // delete the left half of the tree
      BNode <int> * pTemp = pTree->pLeft;
      addLeft(pTree, (BNode <int> *)NULL);
      assert(pTree->pLeft == NULL);
      deleteBTree(pTemp);
      cout << "Size after deleting half the nodes: "
           << sizeBTree(pTree) << endl;
   
      // finally, delete everything else
      deleteBTree(pTree);
      cout << "Was able to delete the rest of the binary tree\n";
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST2   
}

/*******************************************
 * TEST Display
 * We will build a binary tree and display the
 * results on the screen
 ******************************************/
void testDisplay()
{
#ifdef TEST3
   try
   {
      // create
      BNode <string> *pTree = NULL;

      // prompt for seven words
      string word;
      cout << "Enter seven words\n";
      cout << "\tRoot node:         ";
      cin  >> word;
      pTree = new BNode <string> (word);

      cout << "\tLeft child:        ";
      cin  >> word;
      addLeft(pTree, new BNode <string> (word));

      cout << "\tRight child:       ";
      cin  >> word;
      addRight(pTree, new BNode <string> (word));
      
      cout << "\tLeft-Left child:   ";
      cin  >> word;
      addLeft(pTree->pLeft, new BNode <string> (word));
      
      cout << "\tLeft-Right child:  ";
      cin  >> word;
      addRight(pTree->pLeft, new BNode <string> (word));
      
      cout << "\tRight-Left child:  ";
      cin  >> word;
      addLeft(pTree->pRight, new BNode <string> (word));
      
      cout << "\tRight-Right child: ";
      cin  >> word;
      addRight(pTree->pRight, new BNode <string> (word));

      // display the results
      cout << "Completed tree: { " << pTree << "}\n";

      // delete the tree
      deleteBTree(pTree);
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST3
}

/*******************************************
 * TEST MERGE
 * Create three binary trees and merge them
 *******************************************/
void testMerge()
{
#ifdef TEST4
   try
   {
      // create the middle tree
      BNode <char> * pMiddle = new BNode <char> ('m');
      addLeft (pMiddle, 'l');
      addRight(pMiddle, 'n');
      cout << "Middle tree: { " << pMiddle            << "}"
           << " size = "        << sizeBTree(pMiddle) << endl;

      // create lower tree
      BNode <char> * pLower  = new BNode <char> ('b');
      addLeft  (pLower, 'a');
      addRight (pLower, 'c');
      cout << "Lower tree: { " << pLower            << "}"
           << " size = "       << sizeBTree(pLower) << endl;
      

      // create upper tree
      BNode <char> * pUpper  = new BNode <char> ('y');
      addLeft  (pUpper, 'x');
      addRight (pUpper, 'z');
      cout << "Upper tree: { " << pUpper            << "}"
           << " size = "       << sizeBTree(pUpper) << endl;
      
   
      // add Lower to the left of Middle, and Upper to the right of Middle
      addLeft(pMiddle->pLeft, pLower);
      addRight(pMiddle->pRight, pUpper);
      cout << "Merged tree: { " << pMiddle            << "}"
           << " size = "        << sizeBTree(pMiddle) << endl;

      // copy the tree
      BNode <char> * pCopy = copyBTree(pMiddle);
      
      // delete the tree
      deleteBTree(pMiddle);
      assert(pMiddle == NULL);

      // display the copied tree
      cout << "Copied tree: { " << pCopy            << "}"
           << " size = "        << sizeBTree(pCopy) << endl;
      deleteBTree(pCopy);
      assert(pCopy == NULL);
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST4
}
