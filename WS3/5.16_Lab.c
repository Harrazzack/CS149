/**
 *
 * Description: This program will take in a positive integer, which indicates the amount of
 *              elements in the upcoming list. Then the list will be iterated through using
 *              a for loop which will output the list in reverse order that it was entered.
 * Authour: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 */

#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 20;         // Number of input integers
    int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers
    int i, k;

    int numVals;

    scanf("%d", &numVals);
    for (i = 0; i < numVals; ++i)
    {
        scanf("%d", &(userVals[i]));
    }

    for (k = numVals; k >= 1; --k)
    {
        printf("%d,", userVals[k-1]);
    }
    printf("\n");

    return 0;
}
