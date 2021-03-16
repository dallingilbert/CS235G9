/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
    for (int iPivot = num - 1; iPivot > 1; --iPivot)
    {
        bool swapped = false;
        for (int iCheck = 0; iCheck < iPivot; iCheck++)
        {
            if (array[iCheck] > array[iCheck + 1])
            {
                // swap the variables
                T tempVar = array[iCheck];
                array[iCheck] = array[iCheck + 1];
                array[iCheck + 1] = tempVar;
                swapped = true;
            }
        }
        if (!swapped)
            return;
    }
}


#endif // SORT_BUBBLE_H
