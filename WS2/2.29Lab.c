/**
* Description: Given three floating-point numbers x, y, and z, output x to the power of z,
*			   x to the power of (y to the power of 2), the absolute value of y, and the square root of
*			   (xy to the power of z).
* Author names : Haroon Razzack and Vincent Nguyen
* Author emails : vincent.n.nguyen@sjsu.edu
* Last modified date : 02 - 06 - 2023
* Creation date : 02 - 06 - 2023
* */




#include <stdio.h>
#include <math.h>

int main(void) {
    double x;
    double y;
    double z;

    scanf("%lf", &x);
    scanf("%lf", &y);
    scanf("%lf", &z);

    printf("%0.2lf ", pow(x, z));
    printf("%0.2lf ", pow(x, pow(y, 2)));
    printf("%0.2lf ", fabs(y));
    printf("%0.2lf\n", pow(sqrt(x*y), z));

    return 0;
}
