/**
 *
 * Description: Prints hello world from PID xxx! 4 times.
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 03-02-2023
 * Creation date: 03-02-2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int i;

    for (i = 0; i < 4; i++) {
        pid = fork();

        if (pid < 0) {  // fork failed; exit
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (pid == 0) {    // child (new process)
            printf("hello world from PID %d!\n", getpid());
            exit(0);
        }
        else {
            // parent process
        }
    }

    return 0;
}
