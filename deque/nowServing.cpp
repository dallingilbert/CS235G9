/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Dallin Gilbert 
 *    John McCleve
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h" // for DEQUE
#include "student.h"
#include "line.h"
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   Student current;
   Student incoming;

   string className;
   string name;
   int time;
   int min = 0;
   int input;
   int count = 0;
   Line line;

   do
   {
	   cout << "<" << min++ << "> ";
	   cin >> className;

	   if (className == "!!")
	   {
		   cin >> className >> name >> time;
		   incoming.setClass(className);
		   incoming.setName(name);
		   incoming.setTime(time);
		   incoming.setEmer(true);
		   line.addEmer(incoming);
	   }
	   else if (className != "none" && className != "finished")
	   {
		   className = className;
		   cin >> name >> time;
		   incoming.setClass(className);
		   incoming.setName(name);
		   incoming.setTime(time);
		   incoming.setEmer(false);
		   line.addStud(incoming);
	   }
	   else if (className == "finished")
		   break;
	   int timeCounter = current.getTime();

	   if (timeCounter > 0)
	   {
		   timeCounter--;
		   current.setTime(timeCounter);
	   }
	   if (timeCounter == 0)
	   {
		   if (!line.empty())
			   current = line.serveNext();
	   }

	   if (current.getTime() > 0)
	   {
		   if (current.getEmer())      // display status of emergency request
		   {
			   cout << "\tEmergency for " << current.getName() << " for class "
				   << current.getClass() << ". Time left: " << current.getTime() << endl;
		   }
		   else     // display status of regular request
		   {
			   cout << "\tCurrently serving " << current.getName() << " for class "
				   << current.getClass() << ". Time left: " << current.getTime() << endl;
		   }
	   }
   } while (className != "fisnished");
   // end
   cout << "End of simulation\n";
}


