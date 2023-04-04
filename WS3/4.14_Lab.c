/**
 *
 * Description: Simple program to scan in a positive integer, taking the modulos
 *              and printing it out which results in the reverse binary code
 *              of the integer.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 */
#include <stdio.h>

int main(void) {

    int x;
    scanf("%d", &x);

    while(x > 0)
    {
        printf("%d", x % 2);
        x = x / 2;
    }

    printf("\n");

    return 0;
}

