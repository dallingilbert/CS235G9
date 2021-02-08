###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother Kirby, CS235
# Author:
#     John McCleve & Dallin Gilbert
# Summary:
#     This program demonstrates the implementation of a deque
#     data structure and also represents how a deque works
#     with the nowServing header and source files included
#	  
# Time:
#	  Pair programing: 3 hours
#     John: 6 hours
#	  Dallin: 6 hours
# Most challanging part:
#	  John: The hardest part was figuring out why the deque was 
#     not displaying anything within our first few tests
#	  Dallin: The hardest part was figuring out a logical error
#     within our assignment operator that was causing the 
#     iNormalized method to return the wrong index due to 
#     capacity being 0 instead of 4 within the calculation
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