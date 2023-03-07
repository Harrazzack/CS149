/**
 *
 * Description: This program will read an integer which determines how many strings will be entered. A final
 *              char will be read to determine which strings will be printed. If any of the strings entered
 *              contain the final char, then that string will be printed to the console.
 * Authour: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 02-16-2023
 * Creation date: 02-16-2023
 */


#include <stdio.h>
#include <string.h>

int main(void) {


    int MAX_WORDS;
    const int MAX_LEN = 10;

    scanf("%d", &MAX_WORDS);
    char array[MAX_WORDS][MAX_LEN];

    int i;

    for (i = 0; i < MAX_WORDS; ++i)
    {
        scanf("%s", array[i]);
    }

    char searchChar[1];
    scanf("%s", searchChar);
    for(int j = 0; j < MAX_WORDS; j++)
    {
        if(strchr(array[j], searchChar[0]) != NULL)
        {
            printf("%s,", array[j]);
        }
    }

    printf("\n");


    return 0;
}
