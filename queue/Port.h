#pragma once
/***********************************************************************
 * Header:
 *    PORT
 * Summary:
 *    This will contain the portfoilo for the stocks
 * Author
 *    John McCleve & Dallin Gilbert
 ************************************************************************/
#ifndef PORT_H
#define PORT_H

#include "queue.h"   // The queue
#include "Other.h"	 // Other transactions
#include "dollars.h"   // for Dollars defined in StockTransaction
#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT

using namespace custom;

class Port
{
private:
	queue<Other> holding;
	queue<Other> saleHistory;
	Dollars proceed;

public:
	Port();
	~Port();
	void buy(int num, Dollars cost);
	void sell(int num, Dollars cost);
	friend ostream& operator << (ostream& out, const Port& rhs);


};

#endif