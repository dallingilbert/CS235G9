/***********************************************************************
* Program:
*    Assignment 10, Map
*    Brother Helfrich, CS 235
* Author:
*    Br. Helfrich
* Summary:
*    This is a driver program to exercise the Map class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>      // for CIN and COUT
#include <string>        // for STRING
#include "map.h"         // for BST class which should be in bst.h
#include "wordCount.h"   // for the wordCount() function
//#include <map>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
//using std::setw;
using namespace custom;
//using namespace std;

// prototypes for our four test functions
void testSimple();
void testAdd();
void testIterate();
void testQuery();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
#define TEST2   // for testAdd()
#define TEST3   // for testIterate()
//#define TEST4   // for testQuery()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a Map\n";
   cout << "\t2. The above plus add a few entries\n";
   cout << "\t3. The above plus display the contents of a Map\n";
   cout << "\t4. The above plus retrieve entries from the Map\n";
   cout << "\ta. Count word frequency\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
         wordCount();
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
         testQuery();
         cout << "Test 4 complete\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }

   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a Map: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1

  try
  {
     // Test 1.a: bool-int Map with default constructor
     cout << "Create a bool-int Map using default constructor\n";
     map <bool, int> m1;
     cout << "\tSize:     " << m1.size()                   << endl;
     cout << "\tEmpty?    " << (m1.empty() ? "Yes" : "No") << endl;

     // Test 1.b: double-char Map dynamically allocated
     cout << "Create a double-char Map dynamically allocated\n";
     map <double, char> *pm2 = new map <double, char>;
     cout << "\tSize:     " << pm2->size()                   << endl;
     cout << "\tEmpty?    " << (pm2->empty() ? "Yes" : "No") << endl;


     // Test 1.c: copy the Map using the copy constructor
     {
        cout << "Create a double-char Map using the copy constructor\n";
        map <double, char> m3(*pm2);
        cout << "\tSize:     " << m3.size()                   << endl;
        cout << "\tEmpty?    " << (m3.empty() ? "Yes" : "No") << endl;
     }

     // Test 1.d: copy the Map using the assignment operator
     cout << "Copy a double-char Map using the assignment operator\n";
     map <double, char> m4;
     m4 = *pm2;
     delete pm2;

     cout << "\tSize:     " << m4.size()                   << endl;
     cout << "\tEmpty?    " << (m4.empty() ? "Yes" : "No") << endl;
  }
  catch (const char * sError)
  {
     cout << sError << endl;
  }
#endif //TEST1
}

/*******************************************
 * TEST ADD
 * Add a few nodes to the Map then
 * destroy it when done
 *****************************************/
void testAdd()
{
#ifdef TEST2
   try
   {
      // create
      cout << "Create an integer-string Map\n";
      map <int, string> m1;
      map <int, string> m2;
      cout << "\tEmpty? " << (m1.empty() ? "yes" : "no") << endl;
      cout << "\tCount: " << m1.size() << endl;

      // fill
      cout << "Fill with 10 values\n";
      m1[8]  = string("eight");    //               8
      m1[4]  = string("four");     //          +----+----+
      m1[12] = string("twelve");   //          4         12
      m1[2]  = string("two");      //       +--+--+   +--+--+
      m1[6]  = string("six");      //       2     6   9     13
      m1[9]  = string("nine");     //     +-+   +-+   +-+
      m1[13] = string("thirteen"); //     0     5       11
      m1[0]  = string("zero");
      m1[5]  = string("five");
      m1[11] = string("eleven");

      m2 = m1;
      m1[-1] = string("negative one");
      cout << "\tEmpty? " << (m2.empty() ? "yes" : "no") << endl;
      cout << "\tCount: " << m2.size() << endl;

      // clear
      m1.clear();
      cout << "Empty the contents\n";
      cout << "\tEmpty? " << (m1.empty() ? "yes" : "no") << endl;
      cout << "\tCount: " << m1.size() << endl;
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
#endif // TEST2
}

/*******************************************
 * DISPLAY
 * Display the contents of a map
 ******************************************/
template <class K, class V>
ostream & operator << (ostream & out, map < K, V > & rhs)
{
   out << '{';

#ifdef TEST3
   typename map < K, V > :: iterator it;
   for (it = rhs.begin(); it != rhs.end(); ++it)
      out << "  " << (*it).second;
#endif // TEST3

   out << "  }";

   return out;
}

/*******************************************
 * TEST ITERATE
 * We will build a Map and display the
 * contents on the screen
 ******************************************/
void testIterate()
{
#ifdef TEST3
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);

   //
   // An empty map
   //
   try
   {
      cout << "Create an empty bool-bool Map\n";
      map <bool, bool> m;
      cout << "\tEmpty?    " << (m.empty() ? "yes" : "no") << endl;
      cout << "\tCount:    " << m.size()                   << endl;
      cout << "\tContents: " << m                          << endl;
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }

   //
   // a non-trivial map
   //
   try
   {
      map <string, int> m1;
      map <string, int> m2;

      // fill the tree
      cout << "Create a string-integer map that is filled with: "
           << " f c i b e g j a d h\n";
      m1[string("f")] = 6;
      m1[string("c")] = 3;   //               f
      m1[string("i")] = 9;   //          +----+----+
      m1[string("b")] = 2;   //          c         i
      m1[string("e")] = 5;   //       +--+--+   +--+--+
      m1[string("g")] = 7;   //       b     e   g     j
      m1[string("j")] = 10;  //     +-+   +-+   +-+
      m1[string("a")] = 1;   //     a     d       h
      m1[string("d")] = 4;
      m1[string("h")] = 8;

      // show the contents of the map
      cout << "\tEmpty?    " << (m1.empty() ? "yes" : "no") << endl;
      cout << "\tCount:    " << m1.size()                   << endl;
      cout << "\tContents: " << m1                          << endl;

      // copy the map and destroy the original
      m2 = m1;
      m1.clear();
      m1[string("the answer")] = 42;
      cout << "Copy the map and destroy the original\n";
      cout << "\tEmpty?    " << (m2.empty() ? "yes" : "no") << endl;
      cout << "\tCount:    " << m2.size()                   << endl;
      cout << "\tContents: " << m2                          << endl;

      // display the left side of the tree
      map <string, int> :: iterator it;
      cout << "The left side of the tree:\n";
      for (it = m2.find(string("f")); it != m2.end(); --it)
         cout << "\t" << *it << endl;
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }
#endif // TEST3
}

/*******************************************
 * TEST QUERY
 * Prompt the user for items to put in the map
 * and then allow the user to query for items
 *******************************************/
void testQuery()
{
#ifdef TEST4
   try
   {
      // create the map
      map <char, string> m;
      char letter;
      string word;

      // fill the map
      cout << "Please enter a letter word pair. "
           << "Enter ! for the letter when finished.\n";
      cout << "\t> ";
      cin  >> letter >> word;
      while (letter != '!')
      {
         m[letter] = word;
         cout << "\t> ";
         cin  >> letter >> word;
      }

      // display what was found
      cout << "There are " << m.size() << " items in the map\n";
      cout << "The contents of the map are: " << m << endl;

      // prompt for the values in the map
      cout << "Please enter the letter to be found. Enter ! when finished.\n";
      cout << "\t> ";
      cin  >> letter;
      while (letter != '!')
      {
         cout << "The letter '"
              << letter
              << "' corresponds to \""
              << m[letter]
              << "\"\n";
         cout << "\t> ";
         cin  >> letter;
      }
   }
   catch (const char * s)
   {
      cout << "Thrown exception: " << s << endl;
   }
#endif // TEST4
}

