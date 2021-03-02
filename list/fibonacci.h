/***********************************************************************
 * Header:
 *    FIBONACCI
 * Summary:
 *    This will contain just the prototype for fibonacci(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef FIBONACCI_H
#define FIBONACCI_H
#include "list.h"
// the interactive fibonacci program
void fibonacci();

class WholeNumber
{
private:
	//custom::list<std::string>* digits;
	custom::list<int> digits;
public:
	WholeNumber(int num = 0)
	{
		//cerr << num << " begin" << endl;
		digits.push_front(num);
	};
	WholeNumber(WholeNumber& rhs);
	void display(std::ostream& out);
	void addOnto(WholeNumber& rhs);
	WholeNumber& operator = (WholeNumber& rhs);
	WholeNumber& operator += (WholeNumber& rhs);
	friend std::ostream& operator << (std::ostream& out, WholeNumber& rhs);
};
#endif // FIBONACCI_H

