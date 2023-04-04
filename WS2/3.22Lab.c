/**
 * Description: A program whose inputs are three integers, and whose output is the smallest of the three values.
 * Author names: Haroon and Vincent Nguyen
 * Author emails: vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-06-2023
 * Creation date: 02-06-2023
 **/



#include <stdio.h>

int main(void) {


    int x, y, z;

    scanf("%d %d %d", &x, &y, &z);

    if (x <= y && x <= z )
    {
        printf("%d\n", x);
    }
    else if (y <= x && y <= z)
    {
        printf("%d\n", y);
    }
    else if (z <= x && z <= y)
    {
        printf("%d\n", z);
    }



    return 0;
}
