/**
 * Description: Program that continuously reads in lines from std,
 * reverses them, and prints them out. Will continue until "done", "Done", or "d"
 * is read in stdin.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-11-2023
 * Creation date: 03-12-2023
 */

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50

int main() {
    // Maximum length of input line is 50 characters +1 to account for newline \n
    char line[MAX_LENGTH + 1];

    //start infinite loop to continuously ask for input unless "done", "Done", or "d" is read
    while (1) {
        // use fgets() to read a line from stdin and store in line array
        fgets(line, sizeof(line), stdin);

        // Remove newline character at the end of line
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // If string reads "done", "Done", or "d" break loop
        if (strcmp(line, "done") == 0 || strcmp(line, "Done") == 0 || strcmp(line, "d") == 0) {
            break;
        }

        // else read the line array in reverse and print it out
        for (int i = strlen(line) - 1; i >= 0; i--) {
            printf("%c", line[i]);
        }
        printf("\n");
    }
    return 0;
}