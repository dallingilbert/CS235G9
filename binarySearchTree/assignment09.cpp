/***********************************************************************
* Program:
*    Assignment 09, Binary Search Trees
*    Brother <your instructor name>, CS 235
* Author:
*    <your name here>
* Summary: 
*    This is a driver program to exercise the BST class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>      // for CIN and COUT
#include <string>        // for STRING
#include <cassert>       // for ASSERTS
#include "bst.h"         // for BST class which should be in bst.h
using namespace std;
using namespace custom;

// prototypes for our four test functions
void testSimple();
void testAdd();
void testIterate();
void testDelete();
void testBalance();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
//#define TEST2   // for testAdd()
//#define TEST3   // for testIterate()
//#define TEST4   // for testDelete()
//#define TESTA   // for testBalance()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a BST\n";
   cout << "\t2. The above plus add a few nodes\n";
   cout << "\t3. The above plus display the contents of a BST\n";
   cout << "\t4. The above plus find and delete nodes from a BST\n";
   cout << "\ta. Verify that the red-black balancing is handled correctly\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
         testBalance();
         break;
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testAdd();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testIterate();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testDelete();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a BST: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   try
   {
      // Test 1.a: bool BST with default constructor
      cout << "Create a bool BST using the default constructor\n";
      BST <bool> b1;
      cout << "\tSize:     " << b1.size()                   << endl;
      cout << "\tEmpty?    " << (b1.empty() ? "Yes" : "No") << endl;

      // Test 1.b: copy the BST using the copy constructor
      {
         cout << "Create a bool BST using the copy constructor\n";
         BST <bool> b2(b1);
         cout << "\tSize:     " << b2.size()                   << endl;
         cout << "\tEmpty?    " << (b2.empty() ? "Yes" : "No") << endl;
      }

      // Test 1.c: copy the BST using the assignment operator
      cout << "Copy a bool BST using the assignment operator\n";
      BST <bool> b3;
      b3 = b1;
      cout << "\tSize:     " << b3.size()                   << endl;
      cout << "\tEmpty?    " << (b3.empty() ? "Yes" : "No") << endl;
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
      cout << "Create an integer Binary Search Tree\n";
      BST <int> tree1;

      tree1.insert(8);     //               8
      tree1.insert(4);     //          +----+----+
      tree1.insert(12);    //          4         12
      tree1.insert(2);     //       +--+--+   +--+--+
      tree1.insert(6);     //       2     6   9     13
      tree1.insert(9);     //     +-+   +-+   +-+
      tree1.insert(13);    //     0     5       11
      tree1.insert(0);
      tree1.insert(5);
      tree1.insert(11);
      cout << "\tSize of tree1: " << tree1.size() << endl;

      // copy the tree to another
      BST <int> tree2(tree1);
      cout << "\tSize of tree2: " << tree1.size() << endl;
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST2   
}

/******************************************
 * DISPLAY A TREE
 * Display the contents of a BST using an iterator
 ******************************************/
template <class T>
ostream & operator << (ostream & out, BST <T> & rhs)
{
   out << '{';

#ifdef TEST3
   typename BST <T> :: iterator it;
   for (it = rhs.begin(); it != rhs.end(); it++)
      out << "  " << *it;
#endif // TEST3
   
   out << "  }";
   return out;
}

/*******************************************
 * TEST ITERATE
 * We will build a binary tree and display the
 * results on the screen
 ******************************************/
void testIterate()
{
#ifdef TEST3
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);   

   //
   // An empty tree
   //
   try
   {
      BST <bool> tree;      
      cout << "Empty tree\n";
      cout << "\tSize:     " << tree.size() << endl;
      cout << "\tContents: " << tree        << endl;
   }
   catch (const char * s)
   {
      cout << s << endl;
   }

   //
   // A tree with three nodes
   //
   try
   {
      cout << "A tree with three nodes\n";
      BST <double> tree1;
      BST <double> tree2;

      // fill the tree
      cout << "\tFill the BST with: 2.2  1.1  3.3\n";
      tree1.insert(2.2);     //          2.2
      tree1.insert(1.1);     //     +-----+-----+    
      tree1.insert(3.3);     //    1.1         3.3
      cout << "\tContents forward:  " << tree1 << endl;

      // copy the tree and clear the first
      tree2 = tree1;
      tree1.clear();

      // display the contents backwards
      cout << "\tContents backward: {";
      BST <double> :: iterator it;
      for (it = tree2.rbegin(); it != tree2.rend(); --it)
         cout << "  " << *it;
      cout << "  }\n";
   }
   catch (const char * s)
   {
      cout << s << endl;
   }      
   
   //
   // a non-trivial tree
   //
   try
   {
      BST <string> tree1;
      BST <string> tree2;

      // fill the tree
      cout << "Fill the BST with: f  c  i  b  e  g  j  a  d  h  \n";
      tree1.insert(string("f"));     //               f
      tree1.insert(string("c"));     //          +----+----+
      tree1.insert(string("i"));     //          c         i
      tree1.insert(string("b"));     //       +--+--+   +--+--+
      tree1.insert(string("e"));     //       b     e   g     j
      tree1.insert(string("g"));     //     +-+   +-+   +-+
      tree1.insert(string("j"));     //     a     d       h
      tree1.insert(string("a"));     
      tree1.insert(string("d"));
      tree1.insert(string("h"));
      cout << "\tSize:     " << tree1.size() << endl;
      cout << "\tContents: " << tree1        << endl;

      // copy the tree
      cout << "The tree after it was cleared\n";
      tree2 = tree1;
      tree1.clear();
      cout << "\tSize:     " << tree1.size() << endl;
      cout << "\tContents: " << tree1        << endl;

      // show the copied tree
      cout << "The tree that was copied\n";
      cout << "\tSize:     " << tree2.size() << endl;
      cout << "\tContents: " << tree2        << endl;
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }
#endif // TEST3
}

/*******************************************
 * TEST DELETE
 * Insert a few items into a tree, then delete a few items
 *******************************************/
void testDelete()
{
#ifdef TEST4
   try
   {
      BST <char> tree;
      BST <char> :: iterator it;

      // Fill the tree
      cout << "Fill the tree with: G F J A H N E I L O C K M B D P\n";
      tree.insert('G');
      tree.insert('F'); //                       G
      tree.insert('J'); //          +------------+------------+
      tree.insert('A'); //          F                         J
      tree.insert('H'); //   +------+                  +------+------+
      tree.insert('N'); //   A                         H             N
      tree.insert('E'); //   +---+                     +---+     +---+---+
      tree.insert('I'); //       E                         I     L       O
      tree.insert('L'); //    +--+                            +--+--+    +-+
      tree.insert('O'); //    C                               K     M      P
      tree.insert('C'); //  +-+-+                             
      tree.insert('K'); //  B   D                               
      tree.insert('M');
      tree.insert('B');
      tree.insert('D');
      tree.insert('P');

      // display the tree
      cout << "\tContents: "
           << tree
           << endl;

      //
      // Remove node D: leaf
      //

      cout << "Remove a leaf node: 'D'\n";
      
      // find node 'D' and remove it
      it = tree.find('D');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.erase(it);

      // display the tree
      cout << "\tContents: "
           << tree
           << endl;
      
      // look for node 'D' again
      cout << "Attempt to remove 'D' again\n";
      it = tree.find('D');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";

      //
      // Remove node E: one child (left)
      //

      cout << "Remove a one-child node: 'E'\n";
      
      // look for node 'E' and remove it
      it = tree.find('E');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.erase(it);

      // display the tree
      cout << "\tContents: "
           << tree
           << endl;
      
      //
      // Remove node J: two children where 'K' is inorder successor
      //

      cout << "Remove a two-child node: 'J'\n";

      // look for node 'J' and remove it
      it = tree.find('J');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.erase(it);

      // display the tree
      cout << "\tContents: "
           << tree
           << endl;

      //
      // Remove node G: the root
      //

      cout << "Remove the root: 'G'\n";

      // look for node 'G' and remove it
      it = tree.find('G');
      if (it == tree.end())
         cout << "\tNode not found!\n";
      else
         cout << "\tNode '" << *it << "' found\n";
      if (it != tree.end())
         tree.erase(it);

      // display the tree
      cout << "\tContents: "
           << tree
           << endl;
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }
#endif // TEST4
}


/***************************************
 * TEST BALANCE
 * Verify that the red-black balancing is handled correctly
 ***************************************/
void testBalance()
{
#ifdef TESTA
   try
   {
      cout << "Create a simple Binary Search Tree\n";
      BST <int> tree;
      BST <int> :: BNode * root;

      // Case 1: Add a black root
      tree.insert(60);                           //      60b
      root = tree.getRoot();
      assert(root->isRed == false);
      cout << "\tPass Case 1\n";

      // Case 2: Add two children which will be red
      tree.insert(50);                           //       60b
      tree.insert(70);                           //   +----+-----+
      assert(root->pRight->isRed == true);       //  50r        70r
      assert(root->pLeft->isRed == true);
      cout << "\tPass Case 2\n";

      // Case 3: Add a child which should cause 50 and 70 to turn black
      tree.insert(20);                            //           60b
      assert(root->isRed == false);               //      +-----+-----+
      assert(root->data  == 60);                  //     50b         70b
      assert(root->pRight->isRed == false);       //   +--+
      assert(root->pRight->data  == 70);          //  20r
      assert(root->pLeft->isRed == false);
      assert(root->pLeft->data  == 50);
      assert(root->pLeft->pLeft->isRed == true);
      assert(root->pLeft->pLeft->data  == 20);
      cout << "\tPass Case 3\n";

      // Case 4a: Add a child to 20 which should cause a right rotation on 50
      tree.insert(10);                            //           60b
      assert(root->isRed == false);               //      +-----+-----+
      assert(root->data  == 60);                  //     20b         70b
      assert(root->pRight->isRed == false);       //   +--+--+
      assert(root->pRight->data  == 70);          // 10r     50r
      assert(root->pLeft->isRed == false);
      assert(root->pLeft->data  == 20);
      assert(root->pLeft->pLeft->isRed == true);
      assert(root->pLeft->pLeft->data  == 10);
      assert(root->pLeft->pRight->isRed == true);
      assert(root->pLeft->pRight->data  == 50);
      cout << "\tPass Case 4a\n";

      // Case 4b: Add 90 (Case 2) followed by 95 (Case 4b) rotate left
      tree.insert(90);   // case 2
      tree.insert(95);   // case 4b
      assert(root->isRed == false);               //         60b
      assert(root->data  == 60);                  //  +-------+-------+
      assert(root->pRight->isRed == false);       // ...              90b
      assert(root->pRight->data  == 90);          //              +----+-----+
      assert(root->pRight->pRight->isRed == true);//             70r        95r
      assert(root->pRight->pRight->data  == 95);  //
      assert(root->pRight->pLeft->isRed == true);
      assert(root->pRight->pLeft->data  == 70);
      cout << "\tPass Case 4b\n";

      // Case 4c: Add 30 (Case 3 then 2) followed by 40 (Case 4c)
      tree.insert(30); // cause 3, followed by 2
      tree.insert(40); // cause 4c
      assert(root->isRed == false);              //              60b
      assert(root->data  == 60);                 //       +-------+-------+
      assert(root->pRight->isRed == false);      //      20r            ...
      assert(root->pRight->data  == 90);         //  +----+-----+
      assert(root->pLeft->isRed == true);        // 10b        40b
      assert(root->pLeft->data  == 20);          //         +---+---+
      assert(root->pLeft->pLeft->isRed == false);//        30r      50r
      assert(root->pLeft->pLeft->data  == 10);
      assert(root->pLeft->pRight->isRed == false);
      assert(root->pLeft->pRight->data  == 40);
      assert(root->pLeft->pRight->pRight->isRed == true);
      assert(root->pLeft->pRight->pRight->data  == 50);
      assert(root->pLeft->pRight->pLeft->isRed == true);
      assert(root->pLeft->pRight->pLeft->data  == 30);
      cout << "\tPass Case 4c\n";

      // Case 4d: Add 85 (Case 3 then 2) followed by 80 (Case 4d)
      tree.insert(85);    // case 3 followed by 2
      tree.insert(80);    // case 4d
      assert(root->isRed == false);                //         60b
      assert(root->data  == 60);                   //  +-------+-------+
      assert(root->pRight->isRed == true);         // ...              90r
      assert(root->pRight->data  == 90);           //              +----+-----+
      assert(root->pRight->pRight->isRed == false);//             80b       95b
      assert(root->pRight->pRight->data  == 95);   //          +---+---+
      assert(root->pRight->pLeft->isRed == false); //         70r    85r
      assert(root->pRight->pLeft->data  == 80);
      assert(root->pRight->pLeft->pLeft->isRed == true);
      assert(root->pRight->pLeft->pLeft->data  == 70);
      assert(root->pRight->pLeft->pRight->isRed == true);
      assert(root->pRight->pLeft->pRight->data  == 85);
      cout << "\tPass Case 4d\n";

      // make sure it all works as we expect
      cout << "Final tree: " << tree << endl;
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TESTA
   cout << "Test Balance complete\n";
}
