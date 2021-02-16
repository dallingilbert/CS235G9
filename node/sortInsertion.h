/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
	Node<T>* ListH = new Node<T>(array[0]); //head of the list
	Node<T>* listC = ListH; //copy of the list
	
	for (int i = 1; i < num; i++)
		ListH = insert(ListH, array[i], true);
	
	//determine the key
	Node<T>* key = listC->pNext;

	//to use the list
	Node<T>* head = listC;
	Node<T>* prevKey = head;

	//sort the array of floats
	while (true)
	{
		while (prevKey != NULL && prevKey->data > key->data)
		{
			//switch data between key and prevKey
			T temp = key->data;
			key->data = prevKey->data;
			prevKey->data = temp;

			//move to the previous element
			key = prevKey;
			prevKey = prevKey->pPrev;
		}
		prevKey = key;
		key = key->pNext;
		if (key == NULL)//when we reach the end of the list with the key
			break;//we exit the loop
	}

	//copy everything back to the array
	int arrayindex = 0;

	for (/*head of the list*/ head; head != NULL; head = head->pNext)
	{
		array[arrayindex] = head->data;
		arrayindex++;
	}
}

#endif // INSERTION_SORT_H

