/**
 * Description: A program that takes a first name as the input, and outputs a welcome message to that name.
 * Author names: Haroon Razzack and Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-06-2023
 * Creation date: 02-06-2023
 **/



#include <stdio.h>

int main(void) {
    char userName[50];

    scanf("%s", userName);

    printf("Hello %s, and welcome to CS Online!\n", userName);

    return 0;
}
