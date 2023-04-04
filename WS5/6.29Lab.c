/**
 *
 * Description: Program that reads in an integer from scanf. Prints out the
 * binary number in correct order.
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-02-2023
 * Creation date: 03-01-2023
 */

#include <stdio.h>
#include <string.h>

// Function takes in an integer, converts it into binary, while converting each binary digit
// to its ASCII code equivalent to fit in the char binaryValue[].
void IntToReverseBinary(int integerValue, char binaryValue[]) {

    int i = 0;
    while (integerValue > 0) {
        binaryValue[i++] = (integerValue % 2) + '0';
        integerValue = integerValue / 2;
    }

    binaryValue[i] = '\0';
}

// Function that takes the finished binaryValue in char form, then reverses it to place
// the binary digits in the correct order.
void StringReverse(char inputString[], char reversedString[]) {

    int length = strlen(inputString);
    int i, j = 0;

    for (i = length - 1; i >=0; i--) {
        reversedString[j++] = inputString[i];
    }

    reversedString[j] = '\0';
}

int main(void) {

    int x;
    int j;
    int binary[32];
    int i = 0;
    scanf("%d", &x);

    while(x > 0)
    {
        binary[i] = x % 2;
        x = x / 2;
        i++;
    }

    for (j = i-1; j >= 0; j--) {
        printf("%d", binary[j]);
    }

    printf("\n");

    return 0;
}
