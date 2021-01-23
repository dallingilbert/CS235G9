/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <sstream>     // for STRINGSTREAM
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"
#include "Port.h"
using namespace std;
//using namespace custom;

custom::queue <char> s;
/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
    // instructions
    cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
    cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
    cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
    cout << "  display         - Display your current stock portfolio\n";
    cout << "  quit            - Display a final report and quit the program\n";

    // your code here...
    Port port;
    cout << "> ";
    cin.ignore();
    string line;
    while (getline(cin, line))
    {
        // load the line into a stringstream
        stringstream sss;
        sss.str(line);

        // declare variables
        string option;
        int shares;
        Dollars price;

        // read in the data
        sss >> option; // >> shares >> price;

        if (option == "buy")
        {
            sss >> shares >> price;
            port.buy(shares, price);
        }
        else if (option == "sell")
        {
            sss >> shares >> price;
            port.sell(shares, price);
        }
        else if (option == "display")
        {
            cout << port;
        }
        else if (option == "quit")
        {
            break;
        }
        else if (option != "")
            cout << "Unrecognized command, try again.\n";

        cout << "> ";
    }
}

