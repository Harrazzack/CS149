/**
* Description: a program with two inputs, current price and last month's price (both integers).
*			   Then, output a summary listing the price, the change since last month, and the
*			   estimated monthly mortgage computed as (currentPrice * 0.051) / 12.
* Author names : Haroon Razzack and Vincent Nguyen
* Author emails : vincent.n.nguyen@sjsu.edu
* Last modified date : 02 - 06 - 2023
* Creation date : 02 - 06 - 2023
* */



#include <stdio.h>

int main(void) {
    int currentPrice;
    int lastMonthsPrice;

    scanf("%d", &currentPrice);
    scanf("%d", &lastMonthsPrice);


    printf("This house is $%d. ", currentPrice);
    printf("The change is $%d since last month.\n", currentPrice - lastMonthsPrice);
    printf("The estimated monthly mortgage is $%lf.\n", (currentPrice*0.051)/12);

    return 0;
}
