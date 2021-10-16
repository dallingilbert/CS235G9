/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

/*****************************************************
 * MERGE
 * Perform the individual array merges
 ****************************************************/
template <class T>
void merge(T destination[], T *source1[], int size1, T *source2[], int size2)
{
    int i1 = 0;
    int i2 = 0;

    for (int iDestination = 0; iDestination < (size1 + size2); iDestination++)
    {
        if (i1 <= size1 && (i2 == size2 || source1[i1] < source2[i2]))
            destination[iDestination] = source1[i1++];
        else
            destination[iDestination] = source2[i2++];
    }
}

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
    // T *source = array;
    // int iBegin1 = 0;
    // int iBegin2 = 0;
    // int iEnd1 = 0;
    // int iEnd2 = 0;
    // int numIterations = 0;

    // // do while loop

    // do
    // {
    //     int numIterations = 0;

    //     while (iBegin1 < num)
    //     {
    //         numIterations++;

    //         for (int iEnd1 = iBegin1 + 1; iEnd1 < num && !(source[iEnd1 - 1] > source[iEnd1]); iEnd1++)
    //             iBegin2 = iEnd1 + 1;

    //         for (int iEnd2 = iBegin2 + 1; iEnd2 < num && !(source[iEnd2 - 1] > source[iEnd2]); iEnd2++)
    //         {
    //             if (iBegin2 < num)
    //             {
    //                 merge(array, source + iBegin1, iEnd1 - iBegin1 + 1,
    //                       source + iBegin2, iEnd2 - iBegin2 + 1);
    //             }
    //             iBegin1 = iEnd2 + 1;
    //         }
    //     }
    //     // swap destination and source pointers

    // } while (numIterations > 1);

    // if (array != source)
    // {
    //     for (int i = 0; i < num - 1; i++)
    //     {
    //         array[i] = source[i];
    //         --numIterations;
    //     }
    // }
}

#endif // SORT_MERGE_H
