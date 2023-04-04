/**
 *
 * Description: A program that takes in a list of numbers, which will end when a negative
 *              input is entered. While the list is being populated, a sum of the numbers
 *              is being taken. As well as a comparison between the numbers to find the
 *              max. The program takes the sum of the list of numbers and uses it to find
 *              the average of all the numbers inputted. The the program will output the
 *              max of the list and the average.
 * Authour: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 */

#include <stdio.h>

int main(void) {

    int currValue;
    int valuesSum;
    int valueMax;
    int numValues;

    valuesSum = 0;
    numValues = 0;

    scanf("%d", &currValue);
    valueMax = currValue;

    while (currValue > -1)
    {
        valuesSum = valuesSum + currValue;
        numValues = numValues + 1;
        scanf("%d", &currValue);
        if(currValue >= valueMax)
        {
            valueMax = currValue;
        }
    }

    double average = (double)valuesSum/numValues;
    printf("%d ", valueMax);
    printf("%0.2lf\n", average);

    return 0;
}

