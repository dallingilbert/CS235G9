/***********************************************************************
 * Header:
 *    OTHER
 * Summary:
 *    This will handle other transactions to be made
 * Author
 *   John McCleve & Dallin Gilbert
 ************************************************************************/
#include "Other.h"   // for the class definition
#include <cassert>         // for ASSERT
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT
using namespace std;

/************************************************
   * PORT:: CONSTRUCTOR
   * Creates new queue to keep track of transactions
   ***********************************************/
Other::Other(int count, Dollars share, Dollars price)
	:shareCount(count), buyPrice(share), soldPrice(price), sell(false)
{
	if (soldPrice > 0)
		sell = true;
}

/************************************************
   * PORT:: BUY
   * Creates new queue to keep track of transactions
   ***********************************************/
Other Other::sellShares(int sellCount, Dollars salePrice)
{
	assert(sellCount >= 0);
	if (sellCount < 0)
		sellCount = 0;

	if (sellCount > shareCount)
		sellCount = shareCount;

	assert(salePrice >= 0);
	if (salePrice < 0)
		salePrice = 0;

	shareCount -= sellCount;

	Other salesOther(sellCount, buyPrice, salePrice);

	assert(shareCount >= 0);
	assert(buyPrice >= 0);
	assert(soldPrice >= 0);

	return salesOther;
}

/************************************************
   * PORT:: PROFIT
   * gets the profit from sale
   ***********************************************/
Dollars Other::Profit() const
{
	if (sell)
		return (soldPrice - buyPrice) * shareCount;
	else
		return Dollars(0);
}

/************************************************
   * PORT INSERT OPERATOR
   * Displays data without std libary
   ***********************************************/
ostream& operator << (ostream& out, const Other & rhs)
{
	if (rhs.sell)
	{
		out << "\tSold " << rhs.shareCount << " shares at " << rhs.soldPrice
			<< " for a profit of " << rhs.Profit() << endl;
	}
	else
	{
		out << "\tBought " << rhs.shareCount << " shares at " << rhs.buyPrice
			<< endl;
	}
	//rhs.display(out);
	return out;
}