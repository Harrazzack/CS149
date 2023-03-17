/**
 * Description: Program that takes 4 integers as input, calls a swap function,
 * swaps the first and second value, swaps the third and fourth value, prints them out.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-16-2023
 * Creation date: 03-16-2023
 */

#include <stdio.h>

// helper swap method
void swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

// swap values 1 with 2 and 3 with 4
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4)
{
    swap(userVal1, userVal2);
    swap(userVal3, userVal4);
}

int main()
{
    int val1, val2, val3, val4;

    // Read in the values from stdin
    scanf("%d %d %d %d", &val1, &val2, &val3, &val4);

    // Call SwapValues function to swap values
    SwapValues(&val1, &val2, &val3, &val4);

    // Print the swapped values
    printf("%d %d %d %d\n", val1, val2, val3, val4);

    return 0;
}