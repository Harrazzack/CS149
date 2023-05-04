#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLINE 4096
/**
* The reason for using a hashtable is to store the commands in
hash slots by their pids.
* This way you can lookup a command by a pid and retrieve all the
info you need:
* command, index (this index means the line number in the text
file you read),
* start time, and anything else you might need.
* A hashtable (as you might remember from CS146)
* has slots and each slot contains a linked list of nodes
* (these are the entries that contain all the command info).
* Thus the hashtable (see hashtab array variable below) is
* implemented as an array of nlists. Each array position is a
* slot and a linked list of nlist nodes starts at each array
slot.
* Each array position is a hahstable slot.
* You find the hashtable slot for a pid by using a hash function,
* which will map the pid to a hashtable slot (array position).
*
* You can copy this entire code directly in your .c code. No need
to have
* many files.
* This nlist is a node, which stores one command's info in the
hashtable.
*
* The char *name and char *defn you can remove.
* The nlist *next field is a pointer to the next node in the
linked list.
* There is one hashtable slot in each array position,
* consequently there is one linked list of nlists under a
hashtable slot.
*/
struct nlist
{                       /* table entry: */
    struct nlist *next; /* next entry in chain */
    // long starttime;
    // long finishtime;
    struct timespec starttime, finishtime;
    int index;           /* this is the line index in the input text file */
    int pid;             /* the process id. you can use the pid result of wait to lookup in the hashtable */
    const char *command; /* command. This is good to store for when you decide to restart a command */
};
#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
/* This is the hash function: form hash value for string s */
/* You can use a simple hash function: pid % HASHSIZE */
unsigned hash(int pid)
{
    unsigned hashval = 5381;
    while (pid)
    {
        hashval = ((hashval << 5) + hashval) + (pid % 10);
        pid /= 10;
    }
    return hashval % HASHSIZE;
}
/* lookup: look for s in hashtab */
/* This is traversing the linked list under a slot of the hash
table. The array position to look in is returned by the hash
function */
struct nlist *lookup(int pid)
{
    struct nlist *np;
    for (np = hashtab[hash(pid)]; np != NULL; np = np->next)
        if (pid == np->pid)
            return np; /* found */
    return NULL;       /* not found */
}
char *strdup(const char *);
/* insert: put (name, defn) in hashtab */
/* This insert returns a nlist node. Thus when you call insert in
your main function */
/* you will save the returned nlist node in a variable (mynode).
 */
/* Then you can set the starttime and finishtime from your main
function: */
/* mynode->starttime = starttime; mynode->finishtime = finishtime;
 */
struct nlist *insert(char *command, int pid, int index)
{
    struct nlist *node = lookup(pid);
    /* case 1: the pid is not
    found, so you have to create it with malloc. Then you want to set
    the pid, command and index */
    if (node == NULL)
    {
        node = (struct nlist *)malloc(sizeof(struct nlist));
        if (node == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for nlist\n");
            exit(EXIT_FAILURE);
        }
        node->command = command;
        node->pid = pid;
        node->index = index;
        node->next = hashtab[hash(pid)];
        hashtab[hash(pid)] = node;
    }
    /* case 2: the pid is already there in the
    hashslot, i.e. lookup found the pid. In this case you can either
    do nothing, or you may want to set again the command and index
    (depends on your implementation). */
    else
    {
        /* already there */
        node->index = index;
        node->command = strdup(command);
    }
    return node;
}
/** You might need to duplicate the command string to ensure you
don't overwrite the previous command each time a new line is read
from the input file.
Or you might not need to duplicate it. It depends on your
implementation. **/
char *my_strdup(const char *command) /* make a duplicate of command */
{
    char *p;
    p = (char *)malloc(strlen(command) + 1); /* +1 for */
    if (p != NULL)
        strcpy(p, command);
    return p;
}

#define MAX_COMMANDS 100
#define MAX_COMMANDS_LENGTH 30

int main(void)
{
    pid_t pid;
    int index = 0;
    int cmdcounter = 0;
    int status;

    // create arrays for in/out/err files
    char out_file[20], err_file[20];

    // create array for commands delimited by space or \n
    char commands[MAX_COMMANDS][MAX_COMMANDS_LENGTH];
    char *args[MAX_COMMANDS_LENGTH];

    // while there are commands in stdin, save commands to commands array
    while (fgets(commands[index], sizeof(commands[index]), stdin) != NULL)
    {

        // create token pointer for commands array  strtok() which delimits by space or \n and saves to commands array
        char *token = strtok(commands[index], " \n");

        // create index j for args array
        int j = 0;

        // while token isn't null, save tokens to args array
        while (token != NULL)
        {
            args[j] = token;
            j++;
            // sets token pointer to null or to new token
            token = strtok(NULL, " \n");
        }

        // set last index of args array to null to terminate array for execvp
        args[j] = NULL;

        // increment index and command counter
        index++;
        cmdcounter++;

        // fork process
        if ((pid = fork()) < 0)
        {
            printf("forking error\n");
        }
        else if (pid == 0)
        { // child

            // create output and error files for each command
            sprintf(out_file, "%d.out", getpid());
            sprintf(err_file, "%d.err", getpid());
            int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            // copy file descriptors to stdout and stderr
            dup2(out_fd, 1);
            dup2(err_fd, 2);

            // print child starting info
            printf("Child: Starting command %d: child %d pid of parent %d\n",
                   cmdcounter, getpid(), getppid());
            fflush(stdout);

            // execute commands, assuming only 2 arguments will be taken
            execvp(args[0], args);
            printf("couldn't execute: %s", args[0]);
            exit(127);

            close(out_fd);
            close(err_fd);
        }
        else if (pid > 0)
        { /* parent */
            // add the command, pid, and index to nlist hashtable
            struct nlist *nlist_command = insert(commands[index], pid, index);

            // set the start time
            clock_gettime(CLOCK_MONOTONIC, &nlist_command->starttime);

            // create files for parent
            sprintf(out_file, "%d.out", getpid());
            sprintf(err_file, "%d.err", getpid());
            int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

            // redirect stdout and stderr to output and error files
            dup2(out_fd, 1);
            dup2(err_fd, 2);

            // print start command using nlist_command index, pid, and getpid since we're inside parent
            printf("Parent: Starting command %d: child %d pid of parent %d\n",
                   nlist_command->index, nlist_command->pid, getpid());
            fflush(stdout);
        }
    }

    // wait for all children to finish before exiting parent
    while ((pid = wait(&status)) > 0)
    {
        // create files for each child
        sprintf(out_file, "%d.out", getpid());
        sprintf(err_file, "%d.err", getpid());
        int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
        int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

        // Finished child process
        printf("Finished child %d pid of parent %d", getpid(), getppid());
        fflush(stdout);

        // look up the command node
        struct nlist *get_command = lookup(pid);

        // set the finish time of the command
        clock_gettime(CLOCK_MONOTONIC, &get_command->finishtime);

        // Get elapsed time to finish command
        double elapsed = (get_command->finishtime.tv_sec - get_command->starttime.tv_sec);

        // Print the finished time and elapsed time
        printf("Finished at %ld, runtime duration %f\n", get_command->finishtime.tv_sec, elapsed);

        // if the child exited normally
        if (WIFEXITED(status))
        {
            // redirect stdout and stderr to output and error files
            dup2(out_fd, 1);
            fprintf(stderr, "Exited with exitcode = %d\n", WEXITSTATUS(status));
            if (elapsed <= 2)
            {
                fprintf(stderr, "spawning too fast\n");
            }
        }
        // if the child was terminated by a signal
        else if (WIFSIGNALED(status))
        {
            // redirect stdout and stderr to output and error files
            dup2(err_fd, 2);
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(status));
            if (elapsed <= 2)
            {
                fprintf(stderr, "spawning too fast\n");
            }
        }

        // if the elapsed duration for the restart
        // is greater than 2 seconds, restart the command
        if (elapsed > 2)
        {
            // copy command
            char *command_dup = my_strdup(get_command->command);

            // set index
            index = get_command->index;

            // fork child process
            if ((pid = fork()) < 0)
            {
                printf("forking error");
            }
            else if (pid == 0)
            { /* child */
                // create files for each child
                sprintf(out_file, "%d.out", getpid());
                sprintf(err_file, "%d.err", getpid());
                int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
                int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

                // redirect stdout and stderr to output and error files
                dup2(out_fd, 1);
                dup2(err_fd, 2);

                // print start command
                printf("Child: Starting command %d: child %d pid of parent %d\n",
                       index, getpid(), getppid());
                fflush(stdout);

                // create array for argument tokens
                char *args[20];

                // create tokens from copied command that needed to be restarted
                char *token = strtok(command_dup, " \n");

                // j keeps track of arguments in copied command
                int j = 0;

                // while token isn't null, save tokens to args array
                while (token != NULL)
                {
                    args[j] = token;
                    j++;
                    // sets token pointer to null or to new token
                    token = strtok(NULL, " \n");
                }

                // set end of arguments to NULL for execvp
                args[j] = NULL;

                // execute commands using execvp with args array
                execvp(args[0], args);
                printf("couldn't execute: %s", args[0]);
                exit(127);

                close(out_fd);
                close(err_fd);
            }
            else if (pid > 0)
            { /* parent */
                // add the command, pid, and index to nlist hashtable
                struct nlist *nlist_command = insert(commands[index], pid, index);

                // set the start time
                clock_gettime(CLOCK_MONOTONIC, &nlist_command->starttime);

                // create files for parent
                sprintf(out_file, "%d.out", getpid());
                sprintf(err_file, "%d.err", getpid());
                int out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
                int err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);

                // redirect stdout and stderr to output and error files
                dup2(out_fd, 1);
                dup2(err_fd, 2);

                printf("RESTARTING\n");

                // print start command using nlist_command index, pid, and getpid since we're inside parent
                printf("Parent: Starting command %d: child %d pid of parent %d\n",
                       nlist_command->index, nlist_command->pid, getpid());
                fflush(stdout);
            }
        }
        // close files
        close(out_fd);
        close(err_fd);
    }

    return 0;
}