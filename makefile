###############################################################
# Program:
#     Assignment 03, QUEUE
#     Brother XXXX, CS235
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h assignment03.o dollars.o stock.o
	g++ -o a.out assignment03.o dollars.o stock.o
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

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp
