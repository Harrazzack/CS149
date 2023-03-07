/**
 *
 * Description: This program will read in an integer, to determine the length of the list. Once the list is
 *              populated, 2 more integers will be read in. This will determine the range that will be printed
 *              out to the console. If any of the elemnts on the list fall within this range, it will be
 *              printed out to the console.
 * Authour: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 */

#include <stdio.h>

int main(void) {

    const int NUM_INTS = 19;
    int userVals[NUM_INTS];
    int i, min, max;

    scanf("%d", &NUM_INTS);
    for (i = 0; i < NUM_INTS; ++i)
    {
        scanf("%d", &(userVals[i]));
    }

    scanf("%d", &min);
    scanf("%d", &max);


    for (i = 0; i < NUM_INTS; ++i)
    {
        if (userVals[i] >= min && userVals[i] <= max)
        {
            printf("%d,", userVals[i]);
        }
    }

    printf("\n");


    return 0;
}
