/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <cassert>
#include <iostream>
#include <iomanip>
#include <ostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
    // show the first serveral Fibonacci numbers
    int number;
    cout << "How many Fibonacci numbers would you like to see? ";
    cin >> number;

    // Start with the initial number (1) and the initial predecessor
    {
        WholeNumber first(0);
        WholeNumber second(0);
        WholeNumber third(1);

        while (number > 0)
        {
            cout << '\t' << third << endl;
            first = second;
            second = third;
            third += first;
            --number;
        }
    }

    // prompt for a single large Fibonacci
    cout << "Which Fibonacci number would you like to display? ";
    cin >> number;

    // your code to display the <number>th Fibonacci number
    {
        WholeNumber first(0);
        WholeNumber second(0);
        WholeNumber third(1);
        while (number > 1)
        {
            first = second;
            second = third;
            third += first;
            --number;
        }
        cout << '\t' << third << endl;
    }
}

/************************************************
 * WHOLENUMBER :: copy constructor
 * copies the list from rhs to our digit data member
 ***********************************************/
WholeNumber::WholeNumber(WholeNumber& rhs)
{
	digits = rhs.digits;
};

/************************************************
* WHOLENUMBER :: Insertion Operator
* Displays the list on the screen
***********************************************/
std::ostream& operator << (std::ostream& out, WholeNumber& rhs)
{
    rhs.display(out);
    return out;
}

/************************************************
* WHOLENUMBER :: Add-Onto Operator
* Adds to whole numbers & puts results in this.
***********************************************/
WholeNumber& WholeNumber::operator += (WholeNumber& rhs)
{
    this->addOnto(rhs);
    return *this;
}

/************************************************
* WHOLENUMBER :: Assignment Operator
* Copies one list to another
***********************************************/
WholeNumber& WholeNumber :: operator = (WholeNumber& rhs)
{
	digits = rhs.digits;
	return *this;
}

/************************************************
* WHOLENUMBER :: DISPLAY
* Writes this large integer to an output stream
***********************************************/
void WholeNumber::display(std::ostream& out)
{
    custom::list<int>::iterator it = digits.begin();
    while (it != digits.end())
    {
        if (it == digits.begin())
            out << *it;
        else
            out << std::setw(3) << std::setfill('0') << *it;
        ++it;
        if (it != digits.end())
            out << ",";
    }
}

/************************************************
* WHOLENUMBER :: Add Onto
* Adds one large integer onto this one
***********************************************/
void WholeNumber::addOnto(WholeNumber& rhs)
{
    // we need a carry in case the number exceeds the max value that can fit in a node
    int carry = 0;

    custom::list<int>::reverse_iterator myIt = digits.Rbegin();
    custom::list<int>::reverse_iterator otherIt = rhs.digits.Rbegin();

    while (myIt != digits.Rend() || otherIt != rhs.digits.Rend())
    {
        if (otherIt == rhs.digits.Rend())
        {
            while (myIt != digits.Rend())
            {
                int sum = *myIt + carry;
                *myIt = sum % 1000;
                carry = sum / 1000;
                --myIt;
            }
            break;
        }
        else if (myIt == digits.Rend())
        {
            while (otherIt != rhs.digits.Rend())
            {
                int sum = *otherIt + carry;
                digits.push_front(sum % 1000);
                carry = sum / 1000;
                --otherIt;
            }
            break;
        }
        else
        {
            int sum = *myIt + *otherIt + carry;
            *myIt = sum % 1000;
            carry = sum / 1000;
            --myIt;
            --otherIt;
        }
    }
    if (carry)
    {
       //cerr << carry  << " carray"<< endl;
        digits.push_front(carry);

    }
    return;
}

