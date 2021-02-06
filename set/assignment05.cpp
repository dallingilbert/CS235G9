/***********************************************************************
* Program:
*    Assignment 05, Set
*    Brother <instructor here>, CS 235
* Author:
*    Br. Helfrich
* Summary: 
*    This is a driver program to exercise the Set class.  When you
*    submit your program, this should not be changed in any way.  That being
*    said, you may need to modify this once or twice to get it to work.
************************************************************************/

#include <iostream>       // for CIN and COUT
#include <string>         // because testIterate() uses a Set of string
#include "set.h"          // your Set class needs to be in set.h
#include "goFish.h"       // your goFish() function needs to be defined here

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
//using namespace std;
using namespace custom;

// prototypes for our four test functions
void testSimple();
void testFill();
void testFind();
void testUnionIntersection();
void testConstIterator();
void testDifference();

// To get your program to compile, you might need to comment out a few
// of these. The idea is to help you avoid too many compile errors at once.
// I suggest first commenting out all of these tests, then try to use only
// TEST1.  Then, when TEST1 works, try TEST2 and so on.
#define TEST1   // for testSimple()
//#define TEST2   // for testFill()
//#define TEST3   // for testFind()
//define TEST4   // for testUnionIntersection()
//#define TEST5   // for testConstIterator()
//#define TEST6   // for testDifference()

/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
   // menu
   cout << "Select the test you want to run:\n";
   cout << "\t1. Just create and destroy a Set.\n";
   cout << "\t2. The above plus fill and iterate through the Set.\n";
   cout << "\t3. The above plus find if an item is in the Set.\n";
   cout << "\t4. The above plus union and intersection.\n";
   cout << "\t5. Extra credit: test the const iterator.\n";
   cout << "\t6. Extra credit: test the difference operator.\n";
   cout << "\ta. Go Fish!\n";

   // select
   char choice;
   cout << "> ";
   cin  >> choice;
   switch (choice)
   {
      case 'a':
         goFish();
         break;
      case '1':
         testSimple();
         cout << "Test 1 complete\n";
         break;
      case '2':
         testFill();
         cout << "Test 2 complete\n";
         break;
      case '3':
         testFind();
         cout << "Test 3 complete\n";
         break;
      case '4':
         testUnionIntersection();
         cout << "Test 4 complete\n";
         break;
      case '5':
         testConstIterator();
         cout << "Extra credit: const iterator completed\n";
         break;
      case '6':
         testDifference();
         cout << "Extra credit: difference completed\n";
         break;
      default:
         cout << "Unrecognized command, exiting...\n";
   }
   
   return 0;
}

/*******************************************
 * TEST SIMPLE
 * Very simple test for a set: create and destroy
 ******************************************/
void testSimple()
{
#ifdef TEST1
   try
   {
      // Test 1.a: bool Set with default constructor
      cout << "Create a bool Set using default constructor\n";
      set <bool> s1;
      cout << "\tSize:     " << s1.size()                   << endl;
      cout << "\tEmpty?    " << (s1.empty() ? "Yes" : "No") << endl;

      // Test 1.b: double Set with non-default constructor
      cout << "Create a double Set using the non-default constructor\n";
      set <double> s2(10 /*capacity*/);
      cout << "\tSize:     " << s2.size()                   << endl;
      cout << "\tEmpty?    " << (s2.empty() ? "Yes" : "No") << endl;

      // Test 1.c: copy the Set using the copy constructor
      {
         cout << "Create a double Set using the copy constructor\n";
         set <double> s3(s2);
         cout << "\tSize:     " << s3.size()                   << endl;
         cout << "\tEmpty?    " << (s3.empty() ? "Yes" : "No") << endl;
      }

      // Test 1.d: copy the Set using the assignment operator
      cout << "Copy a double Set using the assignment operator\n";
      set <double> s4(2);
      s4 = s2;
      cout << "\tSize:     " << s4.size()                   << endl;
      cout << "\tEmpty?    " << (s4.empty() ? "Yes" : "No") << endl;
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }
#endif // TEST1
}

/******************************************
 * DISPLAY
 * Display the contents of the set
 *****************************************/
template <class T>
ostream & operator << (ostream & out, set <T> & rhs)
{
#ifdef TEST2
   out << "{ ";
   typename set <T> :: iterator it;
   for (it = rhs.begin(); it != rhs.end(); ++it)
      out << *it << ' ';
   out << '}';
#endif // TEST2
   return out;
}

/******************************************
 * TEST FILL
 * This will test the following:
 *   1. Instantiating a Set object
 *   2. Filling the contents with values
 *   3. Iterate through the set to display the contents
 *   4. Destroying an object when finished
 *   5. Copy the set with the copy constructor and assignment operator
 ******************************************/
void testFill()
{
#ifdef TEST2
   try
   {
      // create using the default constructor
      set <int> s1;

      // fill
      cout << "Enter numbers, type 0 when done\n";
      int number;
      do
      {
         cout << "\t" << s1 << " > ";
         cin  >> number;
         if (number)
            s1.insert(number);
      }
      while (number);

      // display how big it is
      cout << "\tSize:     " << s1.size()                   << endl;
      cout << "\tEmpty?    " << (s1.empty() ? "Yes" : "No") << endl;

      // mak a copy of it using the assignment operator and copy constructor
      set <int> s2(2);
      s2.insert(0);
      s2 = s1;
      set <int> s3(s1);

      // destroy the old copy
      s1.clear();
      s1.insert(5);

      // display the two copies
      cout << "\ts1 = " << s1 << endl;
      cout << "\ts2 = " << s2 << endl;
      cout << "\ts3 = " << s3 << endl;      
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }
#endif // TEST2
}

/******************************************
 * TEST FIND
 * This will test the following:
 *   1. Instantiating a Set object
 *   2. Filling the contents with values
 *   3. Displaying the values using an iterator
 *   4. Prompt for the existance of an item in the set and remove it
 *   5. Display the remaining items in the set
 ******************************************/
void testFind()
{
#ifdef TEST3
   try
   {
      // create a list using the default constructor
      set <string> s1;

      // fill the Set with text
      cout << "Enter text, type \"quit\" when done\n";
      string text;
      do
      {
         cout << "\t" << s1 << " > ";
         cin  >> text;
         if (text != "quit")
            s1.insert(text);
      }
      while (text != "quit");

      // make a copy of the set using the copy constructor
      set <string> s2(s1);
   
      // look for an item in the set
      cout << "Find items in the set and delete.\n";
      cout << "Enter words to search for, type \"quit\" when done\n";
      
      cout << "\t" << s1 << " > ";
      cin  >> text;
      do
      {
         set <string> :: iterator itEmpty = s1.end();
         set <string> :: iterator itFind = s1.find(text);
         if (itFind != itEmpty)
         {
            cout << "\tFound and removed!\n";
            s1.erase(itFind);
         }
         else
            cout << "\tNot found\n";
         cout << "\t" << s1 << " > ";
         cin  >> text;
      }
      while (text != "quit");

      // show the list again
      cout << "The remaining set after the items were removed\n";
      cout << "\t" << s1 << endl;

      // show the list before the items were removed
      cout << "The items in the set before the items were removed\n";
      cout << "\t" << s2 << endl;
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }
#endif // TEST3
}

/**********************************************
 * TEST UNION INTERSECTION
 * This will test the following:
 *    1. Instantiate two Set objects and fill them
 *    2. Display the results of Union
 *    4. Display the results of Intersection
 **********************************************/
void testUnionIntersection()
{
#ifdef TEST4
   try
   {
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(1);

      // fill the first set with numbers
      set <float> s1;
      cout << "First set: enter numbers, type 0.0 when done\n";
      float number;
      do
      {
         cout << "\t> ";
         cin  >> number;
         if (number != 0.0)
            s1.insert(number);
      }
      while (number != 0.0);

      // fill the second set with numbers
      set <float> s2;
      cout << "Second set: enter numbers, type 0.0 when done\n";
      do
      {
         cout << "\t> ";
         cin  >> number;
         if (number != 0.0)
            s2.insert(number);
      }
      while (number != 0.0);

      // compute the union and intersection
      set <float> sIntersection(s1 && s2);
      set <float> sUnion(s1 || s2);
      
      // display the contents
      cout << "s1 = " << s1 << endl;
      cout << "s2 = " << s2 << endl;
      cout << "s1 && s2 = " << sIntersection << endl;
      cout << "s1 || s2 = " << sUnion        << endl;
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }   
#endif // TEST4
}

/****************************************************************
 * TEST CONST ITERATOR
 * Extra credit: Test the constant iterator
 ****************************************************************/
void testConstIterator()
{
#ifdef TEST5
   try
   {
      // create the set
      set <int> s1;
      s1.insert(2);
      s1.insert(4);
      s1.insert(6);
      s1.insert(8);

      // display
      cout << "Display the contents using a const iterator\n";
      const set <int> s2(s1);
      for (set <int> :: const_iterator it = s2.cbegin(); it != s2.cend(); ++it)
         cout << '\t' << *it << endl;
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }
#endif // TEST5
}

/***********************************************************
 * TEST DIFFERENCE
 * Extra credit: Test the difference operator
 ***********************************************************/
void testDifference()
{
#ifdef TEST6
   try
   {
      // create a set of 10 characters
      set <char> s1;
      cout << "Please enter 10 characters: ";
      for (int i = 0; i < 10; i++)
      {
         char letter;
         cin >> letter;
         s1.insert(letter);
      }

      // create a second set of 10 characters
      set <char> s2;
      cout << "Please enter another 10 characters: ";
      for (int i = 0; i < 10; i++)
      {
         char letter;
         cin >> letter;
         s2.insert(letter);
      }

      // s1 - s2 and s2 - s1
      set <char> sDifference;
      sDifference = s1 - s2;
      cout << "\t" << s1 << " - " << s2 << " = " << sDifference << endl;
      sDifference = s2 - s1;
      cout << "\t" << s2 << " - " << s1 << " = " << sDifference << endl;
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }   
#endif // TEST6
}
