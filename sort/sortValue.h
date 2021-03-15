/***********************************************************************
 * Component:
 *    Week 11, Sort Value
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The purpose of this data-type is to test sorting algorithms.
 *    This data-type has several properties:
 *     1.   It only defines the less-than operator, the only thing necessary
 *          for a comparison sort
 *     2.   It counts the number of times that a value is copied
 *     3.   It counts the number of times the < operator was called
 *     4.   The insertion operator is defined so you can display the results
 ************************************************************************/

#ifndef SORT_VALUE_H
#define SORT_VALUE_H

#include <iostream>  // for CIN
#include <stdlib.h>  // for rand()

/********************************************************
 * SORT VALUE
 ********************************************************/
class SortValue
{
public:
   // constructors
   SortValue() : value(0) {}
   SortValue(const SortValue & rhs) { *this = rhs; }

   // comparision
   bool operator > (const SortValue & rhs) const
   {
      compares++;
      return value > rhs.value;
   }
   bool operator < (const SortValue & rhs) const
   {
      compares++;
      return value < rhs.value;
   }
   bool operator == (const SortValue & rhs) const
   {
      return value == rhs.value;
   }

   // assignment
   SortValue & operator = (const SortValue & rhs)
   {
      assign++;
      value = rhs.value;
      return *this;
   }
   SortValue & operator = (int rhs)
   {
      assign++;
      value = rhs;
      return *this;
   }

   // fill with a random number
   void random()
   {
      value = rand() % 1000000;
   }
   
   // reset the counters
   void reset()
   {
      assign   = 0;
      compares = 0;
   }

   // display
   friend std::ostream & operator << (std::ostream & out, const SortValue &rhs)
   {
      out << rhs.value;
      return out;
   }

   // get the statistics
   unsigned long getAssigns()  const { return assign;   }
   unsigned long getCompares() const { return compares; }
   
private:
   int value;                     // the value we will be sorting with
   static unsigned long assign;   // # times the assigment operator was called
   static unsigned long compares; // # times the > operator was called
};

unsigned long SortValue :: assign = 0;
unsigned long SortValue :: compares = 0;

#endif // SORT_VALUE_H
