/**
 *
 * Description: Program that defines a function LapsToMiles that takes in a userLaps
 * parameter and returns the number of miles ran.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-21-2023
 * Creation date: 02-21-2023
 */

#include <stdio.h>

double LapsToMiles(double userLaps) {
    const double MILES_PER_LAP = 0.25;
    return userLaps * MILES_PER_LAP;
}

int main(void) {

    double userLaps;
    scanf("%lf", &userLaps);
    double miles = LapsToMiles(userLaps);
    printf("%0.2lf\n", miles);

    return 0;
}
