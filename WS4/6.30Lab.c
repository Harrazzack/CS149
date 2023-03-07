/**
 *
 * Description: Program that defines two functions MaxNumber and MinNumber,
 * they both take in the same 4 numbers as input. MaxNumber finds the max and
 * MinNumber finds the min.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-21-2023
 * Creation date: 02-21-2023
 */

#include <stdio.h>

int MaxNumber(int num1, int num2, int num3, int num4) {

    int max = num1;
    if (num2 > max){
        max = num2;
    }
    if (num3 > max){
        max = num3;
    }
    if (num4 > max){
        max = num4;
    }
    return max;
}

int MinNumber(int num1, int num2, int num3, int num4) {

    int min = num1;
    if (num2 < min){
        min = num2;
    }
    if (num3 < min){
        min = num3;
    }
    if (num4 < min){
        min = num4;
    }
    return min;

}

int main(void) {

    int num1, num2, num3, num4;

    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
    int max = MaxNumber(num1, num2, num3, num4);
    int min = MinNumber(num1, num2, num3, num4);

    printf("Maximum is %d\n", max);
    printf("Minimum is %d\n", min);

    return 0;
}
