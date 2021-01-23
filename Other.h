/***********************************************************************
 * Header:
 *    OTHER
 * Summary:
 *    This will handle other transactions to be made
 * Author
 *   John McCleve & Dallin Gilbert
 ************************************************************************/#pragma once
#ifndef OTHER_H
#define OTHER_H


#include "dollars.h"   // for Dollars defined in StockTransaction
#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT

class Other
{
private:
	int shareCount;
	bool sell;
	Dollars buyPrice;
	Dollars soldPrice;

public:
	Other(int count = 1, Dollars share = 1.0, Dollars price = 0.0);
	Other sellShares(int sellCount, Dollars salePrice);

	int ShareCount() const { return shareCount;  }
	Dollars SharePrice() const { buyPrice; }
	Dollars SoldPrice()const { soldPrice; }
	Dollars Profit() const;
	friend std::ostream& operator << (std::ostream& out, const Other& rhs);

};

#endif