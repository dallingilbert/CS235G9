/***********************************************************************
 * Component:
 *    Week 13, Vertex
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A vertex class useful for a graph
 ************************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using std::string;

/********************************************************
 * VERTEX
 * A generic Vertex class serving as a base class
 *******************************************************/
class Vertex
{
public:
   // constructors (With validation)
   Vertex() : i(0)          {             }
   Vertex(int index) : i(0) { set(index); }
   Vertex(const Vertex & v) { i = v.i;    }
 
   // set (the validation part)
   void set(int index) { if (index >= 0 && index < getMax()) this->i = index; }

   // handle max
   int getMax() const   { return max;                       }
   void setMax(int max) { assert(max > 0); this->max = max; }            
   
   // I/O
   friend std::ostream & operator << (std::ostream & out, const Vertex & rhs);
   friend std::istream & operator >> (std::istream & in,        Vertex & rhs);

   virtual string getText() const         { return string("ERROR");       }
   virtual bool setText(const string & s) { assert(false); return false;  }
   
   // get a scalar value
   int index() const { return i; }
   
   // operators so we can use with an associative container
   bool operator >  (const Vertex & rhs) const {return index() >  rhs.index();}
   bool operator >= (const Vertex & rhs) const {return index() >= rhs.index();}
   bool operator <  (const Vertex & rhs) const {return index() <  rhs.index();}
   bool operator <= (const Vertex & rhs) const {return index() <= rhs.index();}
   bool operator == (const Vertex & rhs) const {return index() == rhs.index();}
   bool operator != (const Vertex & rhs) const {return index() != rhs.index();}

   Vertex & operator = (const Vertex & rhs) { i = rhs.i; return *this; }
   
protected:
   int i;
   static int max;
};

/**************************************************
 * VERTEX : display
 * Display a vertex on the screen: 0,0 -> "a1"
 **************************************************/
inline std::ostream & operator << (std::ostream & out, const Vertex & rhs)
{
   out << rhs.getText();
   return out;
}

/***************************************************
 * VERTEX : input
 * Accept a vertex from the keyboard or any other input stream
 **************************************************/
inline std::istream & operator >> (std::istream & in, Vertex & rhs)
{
   // accept the input from the keyboard
   string s;
   in >> s;

   // if we can set the text, good. Otherwise, set the fail bit!
   if (!rhs.setText(s))
      in.setstate(std::ios_base::failbit);

   return in;
}


/****************************************************
 * LETTERS  VERTEX  
 * A vertex that can be one of many single-letter values
 ***************************************************/
class LVertex : public Vertex
{
public:
   LVertex()
   {
      i = 0;
   }
   
   LVertex(char letter)
   {
      i = 0;
      setText(letter);
   }
      
   // return the text version of the index: 0 --> A
   string getText() const
   {
      string s;
      s += (char)(i + 'A');
      return s;
   }

   // sent an index based on a single letter
   bool setText(char letter)
   {
      int tmp = toupper(letter) - 'A';
      if (tmp >= 0 && tmp < getMax())
      {
         i = tmp;
         return true;
      }
      else
         return false;
   }
   
   // set an index based on the text:  A --> 0
   bool setText(const string & s)
   {
      return setText(s[0]);
   }
};

#define NUM_CLASS 28

/****************************************************
 * COURSE  VERTEX  
 * A vertex that consists of class names
 ***************************************************/
class CourseVertex : public Vertex
{
public:
   CourseVertex()        : Vertex() { max = NUM_CLASS;                }
   CourseVertex(const Vertex & v)   { max = NUM_CLASS; i = v.index(); }
   CourseVertex(int num) : Vertex() { set(num);                       }
   
   // return the text version of the index: 0 --> CS124
   string getText() const          { return nameFromIndex(i);        }

   // set an index based on the text:  CS124 --> 0
   bool setText(const string & s)
   {
      for (int i = 0; i < NUM_CLASS; i++)
         if (s == nameFromIndex(i))
         {
            this->i = i;
            return true;
         }
      return false;
   }
private:
   // because this is a bit non-trivial, we need a separate function for this
   string & nameFromIndex(int i) const
   {
      // all the classes in the sequence
      static string classes[] =
         {
            string("CS124"),   string("CS165"),
      
            string("CS213"),   string("CS235"),   string("CS237"),
            string("CS238"),   string("CS246"),

            string("CS306"),   string("CS308"),   string("CS312"), 
            string("CS313"),   string("CS345"),   string("CS361"),
            string("CS364"),   string("CS371"),   string("CS398"),

            string("CS416"),    string("CS432"),  string("CS450"),
            string("CS460"),    string("CS470"),  string("CS480"),
            string("CS499"),

            string("CIT225"),
            
            string("ECEN160"),
            string("ECEN260"),
            string("ECEN324"), string("ECEN361")
         };
      assert(i >= 0 && i < NUM_CLASS);
      assert(sizeof(classes) / sizeof(classes[0]) == NUM_CLASS);
      return classes[i];
   }
};

/***********************************************
 * COORDIANTES VERTEX
 * Verticies that are identified by coordinates on a grid
 ***********************************************/
class CVertex : public Vertex
{
public:
   CVertex()                    : Vertex() {                }
   CVertex(int col, int row)    : Vertex() { set(col, row); }
   CVertex(const CVertex & rhs) : Vertex() { i = rhs.i;     }
   CVertex(const  Vertex & rhs) : Vertex() { i = rhs.index();     }

   // set a given vertex
   bool set(int col, int row)
   {
      if (col >= 0 && col < getMaxCol() &&
          row >= 0 && row < getMaxRow())
      {
         i = row * getMaxCol() + col;
         return true;
      }
      else
         return false;      
   }
   
   
   // return the text version of the index: (1,3) --> b4
   string getText() const
   {
      string s;
      // column is letter a .. z (or whatever)
      // row is number 1 ... 100 (or whatever)
      s += (char)(getCol() + 'a');
      if (getRow() < 9)
         s += (char)(getRow() + '1');
      else
      {
         assert((getRow() + 1) / 10 >= 0 && (getRow() + 1) / 10 <= 9);
         assert((getRow() + 1) % 10 >= 0 && (getRow() + 1) % 10 <= 9);         
         s += (char)((getRow() + 1) / 10 + '0');
         s += (char)((getRow() + 1) % 10 + '0');
      }
      return s;
   }
   
   // set an index based on the text: b4 --> (1,3)
   bool setText(const string & s)
   {
      if (s.size() == 2)
         return set(s[0] - 'a', s[1] - '1');
      else if (s.size() > 2)
         return set(s[0] - 'a', (s[1] - '0') * 10 + (s[2] - '0') - 1);
      return false;
   }

   // get the column and row from the current index
   int getRow()    const { return i / getMaxCol();        }
   int getCol()    const { return i % getMaxCol();        }
   int getMaxCol() const { return maxCol;                 }
   int getMaxRow() const { return getMax() / getMaxCol(); }

   // set the max row
   void setMax(int col, int row)
   {
      assert(col > 0 && row > 0 && col < 26 && row < 100);
      maxCol = col;
      max    = col * row;
   }

private:
   static int maxCol;
};


#endif // VERTEX_H
