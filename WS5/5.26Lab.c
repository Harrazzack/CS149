/**
 *
 * Description: Program that reads in a line from scanf with a max of 50 characters.
 * The line will be looped through checking each index and counting all characters,
 * other than spaces, periods, exclamation marks, and commas.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-01-2023
 * Creation date: 03-01-2023
 */

#include <stdio.h>

int main(void) {

    // initialize array with 50 characters and set count to 0
    char input[51];
    int count = 0;

    // printf("Enter a line of text (max 50 characters): ");
    // will read input up to 50 characters or until newline shows up
    scanf("%50[^\n]", input);

    // loops through input array and counts everything other than spaces, periods, exlamation points, and commas
    for(int i=0; input[i]!='\0'; i++) {
        if(input[i] != ' ' && input[i] != '.' && input[i] != '!' && input[i] != ',') {
            count++;
        }
    }

    // print count
    printf("%d\n",count);

    return 0;
}
