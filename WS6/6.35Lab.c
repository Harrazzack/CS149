/**
 * Description: Program that reads in a value to indicate number of elements,
 * reads in the values, uses bubble sort to sort the array, prints them out
 * in descending order.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-12-2023
 * Creation date: 03-12-2023
 */

#include <stdio.h>

// Swap function to help swap the elements in the array
void swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

// Bubble sort implementation, SortArray takes in an array of numbers and
// an interger value numVals that states how many values there are in the array
void SortArray(int sortingList[], int numVals) {

    int i, j;
    // Start at the beginning of the array, compare the first two elements,
    // swap if the earlier index is smaller than the next index, bigger values
    // to the beginning
    for (i = 0; i < numVals; i++) {
        for (j = 0; j < numVals - 1; j++) {
            if (sortingList[j] < sortingList[j + 1]) {
                swap(&sortingList[j], &sortingList[j + 1]);
            }
        }
    }
}

int main() {

    int numVals, i;

    //read in number from stdin for the number of array elements
    scanf("%d", &numVals);

    //read in the numbers entered from stdin and put them into sortingList array
    int sortingList[numVals];
    for (i = 0; i < numVals; i++) {
        scanf("%d", &sortingList[i]);
    }

    //call sorting function on the entered array
    SortArray(sortingList, numVals);

    // print
    for (i = 0; i < numVals; i++) {
        printf("%d,", sortingList[i]);
    }
    printf("\n");
    return 0;
}