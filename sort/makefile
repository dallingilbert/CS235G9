###############################################################
# Program:
#     Assignment 11, Sorts
#     Brother XXXXX, CS235
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
a.out: assignment11.o
	g++ -o a.out assignment11.o -g
	tar -cf assignment11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment11.o     : the driver program
##############################################################
assignment11.o: assignment11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -c assignment11.cpp -g

