#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/**
 * CS149 assignment#4 helper code.
 * See the TODO's in the comments below! You need to implement those.
 **/

/**
 * TRACE_NODE_STRUCT is a linked list of
 * pointers to function identifiers
 * TRACE_TOP is the head of the list is the top of the stack
 **/
struct TRACE_NODE_STRUCT
{
    char *functionid;               // ptr to function identifier (a function name)
    struct TRACE_NODE_STRUCT *next; // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE *TRACE_TOP = NULL; // ptr to the top of the stack

/* --------------------------------*/
/* function PUSH_TRACE */
/*
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do.
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
 **/
void PUSH_TRACE(char *p) // push p on the stack
{
    TRACE_NODE *tnode;
    static char glob[] = "global";

    if (TRACE_TOP == NULL)
    {

        // initialize the stack with "global" identifier
        TRACE_TOP = (TRACE_NODE *)malloc(sizeof(TRACE_NODE));

        // no recovery needed if allocation failed, this is only
        // used in debugging, not in production
        if (TRACE_TOP == NULL)
        {
            printf("PUSH_TRACE: memory allocation error\n");
            exit(1);
        }

        TRACE_TOP->functionid = glob;
        TRACE_TOP->next = NULL;
    } // if

    // create the node for p
    tnode = (TRACE_NODE *)malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (tnode == NULL)
    {
        printf("PUSH_TRACE: memory allocation error\n");
        exit(1);
    } // if

    tnode->functionid = p;
    tnode->next = TRACE_TOP; // insert fnode as the first in the list
    TRACE_TOP = tnode;       // point TRACE_TOP to the first node

} /*end PUSH_TRACE*/

/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */
void POP_TRACE() // remove the op of the stack
{
    TRACE_NODE *tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);

} /*end POP_TRACE*/

/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok: funcC:funcB:funcA:global */
char *PRINT_TRACE()
{
    int depth = 50; // A max of 50 levels in the stack will be combined in a string for printing out.
    int i, length, j;
    TRACE_NODE *tnode;
    static char buf[100];

    if (TRACE_TOP == NULL)
    {                          // stack not initialized yet, so we are
        strcpy(buf, "global"); // still in the `global' area
        return buf;
    }

    /* peek at the depth(50) top entries on the stack, but do not
       go over 100 chars and do not go over the bottom of the
       stack */

    sprintf(buf, "%s", TRACE_TOP->functionid);
    length = strlen(buf); // length of the string so far
    for (i = 1, tnode = TRACE_TOP->next;
         tnode != NULL && i < depth;
         i++, tnode = tnode->next)
    {
        j = strlen(tnode->functionid); // length of what we want to add
        if (length + j + 1 < 100)
        { // total length is ok
            sprintf(buf + length, ":%s", tnode->functionid);
            length += j + 1;
        }
        else // it would be too long
            break;
    }
    return buf;
} /*end PRINT_TRACE*/

// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void *REALLOC(void *p, int t, char *file, int line)
{
    p = realloc(p, t);
    fprintf(stdout, "File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, PRINT_TRACE(), p, t);
    return p;
}

// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void *MALLOC(int t, char *file, int line)
{
    void *p = malloc(t);
    fprintf(stdout, "File %s, line %d, function %s allocated new memory segment at address %p to size %d\n", file, line, PRINT_TRACE(), p, t);
    return p;
}

// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void *p, char *file, int line)
{
    fprintf(stdout, "File %s, line %d, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), p);
    free(p);
}

#define realloc(a, b) REALLOC(a, b, __FILE__, __LINE__)
#define malloc(a) MALLOC(a, __FILE__, __LINE__)
#define free(a) FREE(a, __FILE__, __LINE__)
#define MAX_INPUT_LENGTH 100

// -----------------------------------------
// Creating a linked list to hold the commands
// index of the command in the linked list
// a pointer to the command string
struct COMMAND_STRUCT
{
    int index;
    char *command;

    // pointer to next node
    struct COMMAND_STRUCT *nextnode;
};

typedef struct COMMAND_STRUCT COMMAND_NODE;

// pointer to the head of the list
static COMMAND_NODE *COMMAND_TOP = NULL;

// current index of the command
static int COMMAND_INDEX = 0;

// push commands into the linked list
void PUSH_COMMAND(char *cmd)
{
    PUSH_TRACE("PUSH_COMMAND");
    // pointer to the new cnode
    COMMAND_NODE *cnode;

    // malloc space for the new cnode
    cnode = (COMMAND_NODE *)malloc(sizeof(COMMAND_NODE));
    if (cnode == NULL)
    {
        printf("PUSH_COMMAND: memory allocation error\n");
        exit(1);
    }
    // set command to cmd, increment the command index in the linked list, set next as the old command_top
    // this cnode is the new head of the command list
    cnode->command = cmd;           // set the command to the cmd
    cnode->index = COMMAND_INDEX++; // increment the command index
    cnode->nextnode = COMMAND_TOP;  // set the next node to the old command top
    COMMAND_TOP = cnode;            // set the new command top to the cnode
    POP_TRACE();
}

// Pop a command from the stack
void POP_COMMAND()
{
    PUSH_TRACE("POP_COMMAND");
    COMMAND_NODE *cnode;           // pointer to the cnode to be popped
    cnode = COMMAND_TOP;           // set cnode to the head of the list
    COMMAND_TOP = cnode->nextnode; // set the head of the list to the next node
    free(cnode);                   // free the cnode
    POP_TRACE();
}

// clear commands to free up the entire linked list
// while the head of the linked list isn't null, cnode is set to head, and head is set to next
// then the cnode is freed, also resetting command index to 0
void FREE_COMMANDS()
{
    PUSH_TRACE("FREE_COMMANDS");
    COMMAND_NODE *cnode;
    while (COMMAND_TOP != NULL)
    {
        cnode = COMMAND_TOP;                 // set cnode to the head of the list
        COMMAND_TOP = COMMAND_TOP->nextnode; // set the head of the list to the next node
        free(cnode);                         // free the cnode
    }
    COMMAND_INDEX = 0;
    POP_TRACE();
}

// print the commands in the linked list
void PRINT_COMMANDS()
{
    PUSH_TRACE("PRINT_NODES");
    COMMAND_NODE *cnode; // pointer to the current node
    for (cnode = COMMAND_TOP; cnode != NULL; cnode = cnode->nextnode)
    {
        printf("array[%d] = \"%s\"\n", cnode->index, cnode->command); // print the command and its index
    }
    POP_TRACE();
}

// -----------------------------------------
// function add_column will add an extra column to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
// Returns the number of new columns (updated)
int add_column(int **array, int rows, int columns)
{
    PUSH_TRACE("add_column");
    int i;

    for (i = 0; i < rows; i++)
    {
        array[i] = (int *)realloc(array[i], sizeof(int) * (columns + 1));
        array[i][columns] = 10 * i + columns;
    } // for
    POP_TRACE();
    return (columns + 1);
} // end add_column

// ------------------------------------------
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
void make_extend_array()
{
    PUSH_TRACE("make_extend_array");
    int i, j;
    int **array;
    int ROW = 4;
    int COL = 3;

    // make array
    array = (int **)malloc(sizeof(int *) * 4); // 4 rows
    for (i = 0; i < ROW; i++)
    {
        array[i] = (int *)malloc(sizeof(int) * 3); // 3 columns
        for (j = 0; j < COL; j++)
            array[i][j] = 10 * i + j;
    } // for

    // display array
    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            printf("array[%d][%d]=%d\n", i, j, array[i][j]);

    // and a new column
    int NEWCOL = add_column(array, ROW, COL);

    // now display the array again
    for (i = 0; i < ROW; i++)
        for (j = 0; j < NEWCOL; j++)
            printf("array[%d][%d]=%d\n", i, j, array[i][j]);

    // now deallocate it
    for (i = 0; i < ROW; i++)
        free((void *)array[i]);
    free((void *)array);

    POP_TRACE();
    return;
} // end make_extend_array

// takes in inout with fgets, pushes them to the command linked list
// then prints them out
void commands_array()
{
    PUSH_TRACE("commands_array");

    // set the rows of the array to 10 and the index to 0
    int ROW = 10;
    int index = 0;
    // initialize the array of pointers to null
    char **array;
    // allocate memory for the array of pointers and the input from stdin
    array = (char **)malloc(sizeof(char) * ROW);
    char *input = (char *)malloc(sizeof(char) * MAX_INPUT_LENGTH);

    // Read commands from stdin and add them to the linked list
    while (fgets(input, MAX_INPUT_LENGTH, stdin) != NULL)
    {

        // Remove newline character at the end of line
        if (input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }

        // Add the command to the linked list
        PUSH_COMMAND(strdup(input));

        // Increment the index
        index++;

        // Resize the array using realloc if Rows grow
        if (index >= ROW)
        {
            ROW += 10;
            array = (char **)realloc(array, sizeof(char *) * ROW);
        }
        // Store the latest command into the last index of the
        // commands array
        array[index - 1] = strdup(input); // strdup allocates memory for the input string
    }

    // Print the commands array
    PRINT_COMMANDS();

    // Free memory and return
    for (int i = 0; i < index; i++)
    {
        free(array[i]);
    }

    // free both memory allocations
    free(input);
    free((void *)array); // free the array of pointers
    POP_TRACE();
    return;
} // end commands_array

// ----------------------------------------------
// function main
int main()
{
    // Open memtrace.out file and redirect output to memtrace.out
    int logFile = open("memtrace.out", O_RDWR | O_CREAT | O_APPEND);
    chmod("memtrace.out", S_IRWXU);
    dup2(logFile, STDOUT_FILENO);
    PUSH_TRACE("main"); // push the main function onto the stack
    commands_array();   // call the function to demonstrate memory usage tracing
    // pop global stack
    POP_TRACE();    // pop the main function off the stack
    POP_TRACE();    // pop the global stack off the stack (to avoid valgrind errors)
    close(logFile); // remember to close the file
    return (0);
} // end main
