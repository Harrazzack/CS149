/**
 * Description: Program that reads in a string of two words separated by a comma.
 * Program separates the string into two separate words to be printed out removing any
 * white space that may have been entered.
 * Authors: Haroon, Razzack
 * Author emails: haroon.razzack@sjsu.edu
 * Last modified date: 04-03-2023
 * Creation date: 03-27-2023
 */
#include <stdio.h>
#include <string.h>

int main()
{
    char input[100];
    char *token1, *token2;

    while (1)
    {
        printf("Enter input string:\n");
        fgets(input, 100, stdin);

        // remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // check for exit condition
        if (strcmp(input, "q") == 0)
        {
            break;
        }

        // check for comma in input
        char *comma = strchr(input, ',');
        if (comma == NULL)
        {
            printf("Error: No comma in string.\n\n");
            continue;
        }

        // extract first and second words
        token1 = strtok(input, ",");
        token2 = strtok(NULL, ",");
        if (token1 != NULL && token2 != NULL)
        {
            // remove spaces from words
            char *p = token1;
            while (*p && (*p == ' ' || *p == '\t' || *p == '\r'))
                p++;
            token1 = p;

            p = token2;
            while (*p && (*p == ' ' || *p == '\t' || *p == '\r'))
                p++;
            token2 = p;

            printf("First word: %s\n", token1);
            printf("Second word: %s\n\n", token2);
        }
    }

    return 0;
}
