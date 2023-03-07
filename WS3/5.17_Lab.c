/**
 *
 * Description: A program that takes in a list of numbers and stops when it reads in a negative integer.
 *              While the list is being acquired, a count of the elements in the list is being made,
 *              which is used to find the middle index of the list. Once the middle index of the list is
 *              found. The program will output the data in the middle index.
 * Authour: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 *
 */

#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 9;
    int userValues[NUM_ELEMENTS];
    int count = 0;

    int i;

    for (i = 0; i < 20; ++i)
    {
        scanf("%d", &(userValues[i]));
        if(userValues[i] < 0 || count > NUM_ELEMENTS)
        {
            break;
        }
        count++;
    }

    int middle = (count / 2);
    if (count > 9)
    {
        printf("Too many numbers\n");
    }
    else
    {
        printf("Middle item: %d\n", userValues[middle]);
    }

    return 0;
}
