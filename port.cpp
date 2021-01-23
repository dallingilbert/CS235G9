/***********************************************************************
 * Header:
 *    PORT
 * Summary:
 *    This will contain the portfoilo for the stocks
 * Author
 *    John McCleve & Dallin Gilbert
 ************************************************************************/
#include "Port.h" //The Port class header
#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
using namespace std;

/************************************************
   * PORT:: CONSTRUCTOR
   * Creates new queue to keep track of transactions
   ***********************************************/
Port::Port() :proceed(0)
{
}

/************************************************
   * PORT:: DESTRUCTOR
   * Creates new queue to keep track of transactions
   ***********************************************/
Port::~Port()
{
}

/************************************************
   * PORT:: BUY
   * Creates new queue to keep track of transactions
   ***********************************************/
void Port::buy(int num, Dollars cost)
{
	Other t = Other(num, cost);
	holding.push(t);
}

/************************************************
   * PORT:: SELL
   * Sells stocks
   ***********************************************/
void Port::sell(int num, Dollars cost)
{
	Other sale = holding.front().sellShares(num, cost);
	num -= sale.ShareCount();
	proceed = sale.Profit();
	saleHistory.push(sale);

	if (holding.front().ShareCount() == 0)
		holding.pop();
}

/************************************************
   * PORT INSERT OPERATOR
   * Displays data without std libary
   ***********************************************/
ostream & operator << (ostream & out, const Port & rhs)
{
	queue<Other> q = rhs.holding;
	if (!rhs.holding.empty())
	{
		out << "Currently held:\n";

		while (!q.empty())
		{
			out << q.front();
			q.pop();
		}
	}

	if (!rhs.saleHistory.empty())
	{
		out << q.front();
		queue<Other> o = rhs.saleHistory;

		while (!o.empty())
		{
			out << o.front();
			o.pop();
		}
	}
	out << "Proceeds: " << rhs.proceed << endl;
	return out;
}