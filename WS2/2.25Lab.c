/**
 * Description: Aprogram using integers userNum and x as input, and output userNum divided by x three times.
 * Author names: Haroon Razzack and Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-06-2023
 * Creation date: 02-06-2023
 **/


#include <stdio.h>

int main(void) {

    int userNum, x;

    scanf("%d", &userNum);
    scanf("%d", &x);

    userNum = userNum / x;
    printf("%d ", userNum);

    userNum = userNum / x;
    printf("%d ", userNum);

    userNum = userNum / x;
    printf("%d\n", userNum);

    return 0;
}
