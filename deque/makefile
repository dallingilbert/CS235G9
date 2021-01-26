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
a.out: deque.h assignment04.o
	g++ -o a.out assignment04.o 
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp