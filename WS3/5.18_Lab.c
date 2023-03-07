/**
 *
 * Description: A program that first takes a positive integer to determine the amount of elements in the list.
 *              Then the list will be propogated with integers. The final integer that is scanned in will
 *              determine what will be printed. The elements in the array will be compared to the final integer
 *              that was read in. Any element that is less than the final integer will be printed out to the
 *              console.
 * Authour: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 *
 */

#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 20;
    int userValues[NUM_ELEMENTS];    // Set of data specified by the user
    int lessThan;

    int i;

    scanf("%d", &NUM_ELEMENTS);

    for (i = 0; i < NUM_ELEMENTS; ++i)
    {
        scanf("%d", &userValues[i]);
    }

    scanf("%d", &lessThan);

    int k;
    for (k = 0; k < NUM_ELEMENTS; ++k)
    {
        if(userValues[k] <= lessThan)
        {
            printf("%d,", userValues[k]);
        }
    }
    printf("\n");


    return 0;
}
