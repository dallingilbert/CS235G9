/***********************************************************************
 * Header:
 *    vector
 * Summary:
 *    This class contains the notion of a vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       array :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef vector_h
#define vector_h

#include <cassert>  // because I am paranoid
#include <cstddef> // for NULL
#include <new>

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * ARRAY
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector() { setSize(0); setCapacity(0); }
   vector(int numElements);
   //vector(int numElements, T t);
   vector(const vector & rhs);
   ~vector();
   vector & operator = (const vector & rhs);
   
   // standard container interfaces
   int size()     const { return getSize();             }
   int capacity() const { return getCapacity();         }
   //void clear()          { this->numElements = 0;      }
   bool empty() const   { return (numElements == 0 ? true : false); }
   
   // array-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)
   {
      return array[index];
   }
   const T & operator [] (int index) const 
   {
      return array[index];
   }
   
   // the various iterator interfaces
   //class iterator;
   //iterator begin()      { return iterator (data); }
   //iterator end();

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   //void display() const; 
   
private:
   T * array; // dynamically allocated array of T
   int numElements;        // the number of elements
   int numCapacity;        // the capacity of the vector

   // private methods
   void resize(int cNew);

   // setters
   void setSize(int numElements) { this->numElements = numElements; }
   void setCapacity(int numCapacity) { this->numCapacity = numCapacity; }

   // getters
   int getSize() const { return this->numElements; }
   int getCapacity() const { return this->numCapacity; }
};

// /**************************************************
//  * ARRAY ITERATOR
//  * An iterator through array
//  *************************************************/
// template <class T>
// class vector <T> :: iterator
// {
// public:
//    // constructors, destructors, and assignment operator
//    iterator()      : p(NULL)      {              }
//    iterator(T * p) : p(p)         {              }
//    iterator(const iterator & rhs) { *this = rhs; }
//    iterator & operator = (const iterator & rhs)
//    {
//       this->p = rhs.p;
//       return *this;
//    }

//    // equals, not equals operator
//    bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
//    bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

//    // dereference operator
//          T & operator * ()       { return *p; }
//    const T & operator * () const { return *p; }

//    // prefix increment
//    iterator & operator ++ ()
//    {
//       p++;
//       return *this;
//    }

//    // postfix increment
//    iterator operator ++ (int postfix)
//    {
//       iterator tmp(*this);
//       p++;
//       return tmp;
//    }
   
// private:
//    T * p;
// };


// /********************************************
//  * VECTOR :: END
//  * Note that you have to use "typename" before
//  * the return value type
//  ********************************************/
// template <class T>
// typename vector <T> :: iterator vector <T> :: end ()
// {
//    return iterator (data + num);
// }

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
{
   // set numElements equal to 0
   this->numElements = 0;

   // Handle the condition of destination vector size 
   // when it is smaller
   if (rhs.size() > capacity())
   {
      resize(rhs.size());
   }

   numElements = rhs.size();

   assert(numElements == rhs.numElements); // check both vectors for equal size

   for (int i = 0; i < numElements - 1; i++)
      array[i] = rhs.array[i];

   return *this;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) 
{
   assert(rhs.numElements >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numElements == 0)
   {
      this->numElements = 0;
      this->array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[rhs.numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   if (rhs.capacity() > rhs.size())
      this->numElements = rhs.size(); // only copy over size
   else {
      this->numCapacity = rhs.numCapacity; // copy over the capacity
      
   }

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int numCapacity) 
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity == 0)
   {
      setCapacity(0);
      setSize(0);
      this->array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   setSize(numCapacity);
}

/**********************************************
 * VECTOR : RESIZE
 * Reallocates vector capacity to copy over a 
 * larger vector
 *********************************************/
template <class T>
void custom::vector <T> :: resize(int cNew)
{
   try {
      T *arrayTemp = new T[cNew];
      for (int i = 0; i < numElements; i++)
         arrayTemp[i] = array[i];

      delete array;
      array = arrayTemp;
      this->numCapacity = cNew;
   } 
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/**********************************************
 * VECTOR : DESTRUCTOR
 * Clears allocated data of objects created
 *********************************************/
template <class T>
vector <T> :: ~vector()
{
   if (array == NULL)
      return;

   delete[] array;
}

// /********************************************
//  * ARRAY : DISPLAY
//  * A debug utility to display the contents of the array
//  *******************************************/
// template <class T>
// void vector <T> :: display() const
// {
// #ifndef NDEBUG
//    std::cerr << "array<T>::display()\n";
//    std::cerr << "\tnum = " << num << "\n";
//    for (int i = 0; i < num; i++)
//       std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
// #endif // NDEBUG
// }

}; // namespace custom

#endif // vector_h
