###############################################################
# Program:
#     Assignment 03, QUEUE
#     Brother XXXX, CS235
# Author:
#     John McCleve & Dallin Gilbert
# Summary:
#     This program shows the data structure queue can do
#	  It also keeps track of your stocks
# Time:
#	  Pair programing: 3 hours
#     John: 6 hours
#	  Dallin: 6 hours
# Most challanging part:
#	  John: Trying to find out where are queue wasn't wrapping
#     around from the front to the back
#	  Dallin:
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h assignment03.o dollars.o stock.o Other.o port.o
	g++ -o a.out assignment03.o dollars.o stock.o Other.o port.o
	tar -cf assignment03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
assignment03.o: queue.h assignment03.cpp
	g++ -c assignment03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h Port.h
	g++ -c stock.cpp

port.o: Port.h port.cpp dollars.h
	g++ -c port.cpp

Other.o: Other.h Other.cpp dollars.h
	g++ -c Other.cpp