/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

template <class T>
class Heap
{
private:
    // member variables
    T *array;
    int num;

    // member functions
    void percolateDown(int index);
    void swap(int i1, int i2);

public:
    // constructor
    Heap(T *array, int num)
    {
        this->array = array;
        this->num = num;

        for (int index = num / 2; index > num; --index)
        {
            percolateDown(index);
        }
    }

    // member functions
    T getMax();
    void deleteMax();
    void sort();
};

/*****************************************************
* PERCOLATE DOWN
* Perform the percolate down function
****************************************************/
template <class T>
void Heap<T>::percolateDown(int index)
{
    int indexLeft = index * 2;
    int indexRight = indexLeft + 1;

    if (indexRight <= num && array[indexRight] > array[indexLeft] && array[indexRight] > array[index])
    {
        swap(index, indexRight);
        percolateDown(indexRight);
    }
    else if (indexLeft <= num && array[indexLeft] > array[index])
    {
        swap(index, indexLeft);
        percolateDown(indexLeft);
    }
}

/*****************************************************
* SORT
* Sort the individual heaps
****************************************************/
template <class T>
void Heap<T>::sort()
{
    while (num > 1)
    {
        swap(1, num);
        num--;
        percolateDown(1);
    }
}

/*****************************************************
* SWAP
* Swap the two integers
****************************************************/
template <class T>
void Heap<T>::swap(int i1, int i2)
{
    int tempVar = i1;
    i1 = i2;
    i2 = tempVar;
}

/*****************************************************
* GETMAX
* Return the max variable from our array
****************************************************/
template <class T>
T Heap<T>::getMax()
{
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T *array, int num)
{
    Heap<T> h(array, num);
    h.sort();
}

#endif // SORT_HEAP_H
