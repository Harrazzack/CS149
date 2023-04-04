/**
 *
 * Description: Program that builds off of countnames in Assignment 1. Adds fork,
 * pipe, and waiting, to read multiple files, while passing them through pipe to parent.
 * Authors: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-06-2023
 * Creation date: 03-02-2023
 */



#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_NAMES 100
#define MAX_NAMES_LENGTH 30

int main(int argc, char *argv[]) {

    // check if input arguments are correct
    if (argc < 2) {
        fprintf(stderr, "Usage: countnames <filename> [<filename> ...]\n");
        return 1;
    }

    // Initialize arrays for names and duplicate counts
    char lines[MAX_NAMES][MAX_NAMES_LENGTH];
    int counts[MAX_NAMES] = {0};
    int num_names = 0;

    // Create a pipe for communicating with child processes
    int fd[2];
    if (pipe(fd) == -1) {
        fprintf(stderr, "Failed to create pipe.\n");
        return 1;
    }

    // Fork for each file and read names from the file
    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            // Open the input file
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Can't open file: %s\n", argv[i]);
                exit(1);
            }

            // Read names from the file and after each loop iteration of the while
            // line number is incremented.
            char line[MAX_NAMES_LENGTH];
            int line_num = 1;
            while (fgets(line, sizeof(line), fp)) {
                // Remove newline character at the end of line
                if (line[strlen(line) - 1] == '\n') {
                    line[strlen(line) - 1] = '\0';
                }
                // Write the name to the pipe
                write(fd[1], line, strlen(line) + 1);
                // Checking for an empty line otherwise it compares new names to each
                // of the names in the stored array, if a match is found, count is incremented
                if (strlen(line) == 0) {
                    fprintf(stderr,"Warning - Line %d in %s is empty.\n", line_num, argv[i]);
                }
                line_num++;
            }
            // Close the file
            fclose(fp);
            exit(0);
        }
        else if (pid < 0) {
            // Error handling for failed fork
            fprintf(stderr, "Failed to fork.\n");
            return 1;
        }
    }

    close(fd[1]);


    // Wait for all child processes to complete
    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }

    char line[MAX_NAMES_LENGTH];
    while (read(fd[0], line, sizeof(line)) > 0) {
        // Check if the name is already in the array
        int found = 0;
        for (int i = 0; i < num_names; i++) {
            if (strcmp(line, lines[i]) == 0) {
                counts[i]++;
                found = 1;
                break;
            }
        }
        // Add the name to the array if it's not already there
        if (!found) {
            strncpy(lines[num_names], line, sizeof(lines[num_names]));
            counts[num_names]++;
            num_names++;
        }
    }

    // Prints the unique names and their counts
    for (int i = 0; i < num_names; i++) {
        printf("%s: %d\n", lines[i], counts[i]);
    }

    return 0;
}
