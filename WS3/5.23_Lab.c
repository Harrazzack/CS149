/**
 *
 * Description: This program will read in an integer to determine the number of elements in the list.
 *              Once the list is populated, the array will be traversed and a minimum will be found. Once
 *              minimum is found, the array will be looped through again and a 2nd minimum that is greater
 *              than the first minimum AND lower than the rest of the list will be found. The two numbers
 *              will then be printed to the console.
 * Authour: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 *
 */

#include <stdio.h>

int main(void) {

    const int NUM_VALS = 19;
    int userVals[NUM_VALS];
    int i, min, min2;

    min = 10;
    min2 = 20;

    scanf("%d", &NUM_VALS);
    for (i = 0; i < NUM_VALS; ++i)
    {
        scanf("%d", &(userVals[i]));
    }

    for (i = 0; i < NUM_VALS; ++i)
    {
        if (userVals[i] < min)
        {
            min = userVals[i];
        }
    }

    for (i = 0; i < NUM_VALS; ++i)
    {
        if (userVals[i] < min2 && userVals[i] > min)
        {
            min2 = userVals[i];
        }
    }

    printf("%d and %d\n", min, min2);



    return 0;
}
