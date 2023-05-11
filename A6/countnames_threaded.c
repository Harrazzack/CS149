/*****************************************
 * Description: Program expands on Assignment 2 for CS149
 * which takes two files. Each thread will process one file.
 * The names will be counted using ahshmap and pritned out.
 * Authors: Haroon Razzack
 * Author emails: haroon.razzack@sjsu.edu, harrazzack@gmail.com
 * Last modified date: 05-10-2023
 * Creation date: 05-0-2023
 *
 * CS149 SP23
 * Template for assignment 6
 * San Jose State University
 * originally prepared by Bill Andreopoulos
 *****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

/*****************************************
//CS149 SP23
//Template for assignment 6
//San Jose State University
//originally prepared by Bill Andreopoulos
*****************************************/

// thread mutex lock for access to the log index
// TODO you need to use this mutexlock for mutual exclusion
// when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;

// thread mutex lock for critical sections of allocating THREADDATA
// TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;

// thread mutex lock for access to the name counts data structure
// TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void *thread_runner(void *);
pthread_t tid1, tid2;

// struct points to the thread that created the object.
// This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT
{
    pthread_t creator;
    char filename[20];
};
typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA *p = NULL;

// variable for indexing of messages by the logging function.
int logindex = 0;
// this is a pointer to the logindex variable, so that you can pass it to the logging function.
int *logip = &logindex;

// The name counts.
//  You can use any data structure you like, here are 2 proposals: a linked list OR an array (up to 100 names).
// The linked list will be faster since you only need to lock one node, while for the array you need to lock the whole array.
// You can use a linked list template from A5. You should also consider using a hash table, like in A5 (even faster).
struct NAME_STRUCT
{
    char name[30];
    int count;
};
typedef struct NAME_STRUCT THREAD_NAME;

// array of 100 names
THREAD_NAME names_counts[100];

// node with name_info for a linked list
struct NAME_NODE
{
    //
    THREAD_NAME name_count;
    struct NAME_NODE *next;
};

// define hash size as 100
#define HASH_SIZE 100
//
static struct NAME_NODE *hash_table[HASH_SIZE];

// hash function:
int hash(char *name)
{
    int hash = 0;
    int i;
    // add up all the characters in the name
    for (i = 0; name[i] != '\0'; i++)
    {
        hash += name[i]; //
    }
    return hash % HASH_SIZE;
}

// create a struct lookup table for given entry in hash_table
struct NAME_NODE *lookup(char *name)
{
    struct NAME_NODE *np;
    // go through the hash table
    for (np = hash_table[hash(name)]; np != NULL; np = np->next)
    {
        // if the name is found in the hash table
        if (strcmp(name, np->name_count.name) == 0)
        {
            return np; // found
        }
    }
    return NULL; // not found
}

// return a pointer to the name_info for the given name
char *my_strdup(char *s)
{
    char *p;
    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
    {
        strcpy(p, s);
    }
    return p;
}

// create function to free the NAME_NODE objects in the hash table
void free_hash_table()
{
    struct NAME_NODE *np, *next;
    // go through the hash table
    for (int i = 0; i < HASH_SIZE; i++)
    {
        // go through the linked list
        for (np = hash_table[i]; np != NULL; np = next)
        {
            next = np->next;
            free(np);
        }
    }
}

// adding a logprint to print out the logs
void print_log(char *message)
{
    time_t now;
    struct tm *local;
    // Obtain current time and convert it to calendar time
    time(&now);
    local = localtime(&now);

    // Obtain the date
    int day = local->tm_mday;         // get day of month (1 to 31)
    int month = local->tm_mon + 1;    // get month of year (0 to 11)
    int year = local->tm_year + 1900; // get year since 1900

    // Obtain the time
    int hours = local->tm_hour;  // get hours since midnight (0-23)
    int minutes = local->tm_min; // get minutes passed after the hour (0-59)
    int seconds = local->tm_sec; // get seconds passed after minute (0-59)
    // lock the mutex lock
    pthread_mutex_lock(&tlock1);
    logindex = ++(*logip);
    pthread_t me = pthread_self();
    // Before midday
    if (hours < 12)
        printf("Logindex %d, thread %lu, PID %ld, %02d/%02d/%d %02d:%02d:%02d am: %s", logindex, (unsigned long)me, (unsigned long)pthread_self(), day, month, year, hours, minutes, seconds, message);

    // After midday
    else
        printf("Logindex %d, thread %lu, PID %ld, %02d/%02d/%d %02d:%02d:%02d pm: %s", logindex, (unsigned long)me, (unsigned long)pthread_self(), day, month, year, hours - 12, minutes, seconds, message);

    // unlock the mutex lock
    pthread_mutex_unlock(&tlock1);
}

// create function to insert a new node into the hash table
struct NAME_NODE *insert_node(char *name)
{
    struct NAME_NODE *np;
    // if the name is not found in the hash table
    if ((np = lookup(name)) == NULL)
    {
        // create a new node
        np = (struct NAME_NODE *)malloc(sizeof(struct NAME_NODE));
        // if the node is not created
        if (np == NULL)
        {
            return NULL;
        }
        // insert the node into the hash table
        np->next = hash_table[hash(name)];
        hash_table[hash(name)] = np;
    }
    return np;
}

/*********************************************************
// function main
*********************************************************/
int main(int argc, char *argv[])
{
    // TODO similar interface as A2: give as command-line arguments three filenames of numbers (the numbers in the files are newline-separated).
    if (argc != 3)
    {
        printf("Usage: program <file1> <file2>\n");
        return 1;
    }

    printf("create first thread\n");
    pthread_create(&tid1, NULL, thread_runner, argv[1]);

    printf("create second thread\n");
    pthread_create(&tid2, NULL, thread_runner, argv[2]);

    printf("wait for first thread to exit\n");
    pthread_join(tid1, NULL);
    printf("first thread exited\n");

    printf("wait for second thread to exit\n");
    pthread_join(tid2, NULL);
    printf("second thread exited\n");

    // TODO print out the sum variable with the sum of all the numbers
    struct NAME_NODE *np;
    for (int i = 0; i < HASH_SIZE; i++)
    {
        // go through the hash table
        for (np = hash_table[i]; np != NULL; np = np->next)
        {
            // print out the name and count
            printf("%s %d\n", np->name_count.name, np->name_count.count);
        }
    }
    free_hash_table();
    exit(0);

} // end main

/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void *thread_runner(void *x)
{
    // this is the thread's id
    pthread_t me;
    me = pthread_self();
    char *file = (char *)x;

    // p is a pointer to the THREADDATA struct for this thread
    printf("This is thread %lu (p=%p)\n", (unsigned long)me, p);

    // tlock2 is defined as a global variable at line 25
    pthread_mutex_lock(&tlock2); // critical section starts
    if (p == NULL)
    {
        p = (THREADDATA *)malloc(sizeof(THREADDATA));
        p->creator = me;
    }
    pthread_mutex_unlock(&tlock2); // critical section ends

    // open the file and read names. Basic A2 implementation but with hashmap and locks
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", file);
        // exit(1);
    }
    else
    {
        // Read names from the file and after each loop iteration of the while line number is incremented
        char line[100];
        int line_number = 0;
        // read the file line by line and store the line in the variable line
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            // Remove newline character at the end of the line
            if (line[strlen(line) - 1] == '\n')
            {
                line[strlen(line) - 1] = '\0';
            }

            /* check if there is an empty line otherwise it compares
            the name with the names in the hash table and increments the count */
            if (strlen(line) == 0)
            {
                fprintf(stderr, "Warning - Line %d in %s is empt.\n", line_number, file);
            }
            // take in a line and check if it is not empty
            if (line[0] != '\0')
            {

                struct NAME_NODE *np;
                // look up the name in the hash table
                np = lookup(line);

                pthread_mutex_lock(&tlock3); // critical section starts
                // if the name is not found in the hash table
                if (np == NULL)
                {
                    // call the insert_node function to insert the name into the hash table
                    np = insert_node(line);
                    // if the name is not inserted into the hash table
                    if (np == NULL)
                    {
                        printf("Error inserting name %s into hash table\n", line);
                        exit(1);
                    }
                }
                else
                {
                    // increment the count if the name is found in the hash table
                    np->name_count.count++;
                }
                pthread_mutex_unlock(&tlock3); // critical section ends

                // Close the file so that it can be opened again in the next iteration
                fclose(fp);
                print_log("Thread finished file processing\n");
            }
        }

        pthread_mutex_lock(&tlock1);
        if (p != NULL && p->creator == me)
        {
            printf("This is thread %lu and I delete THREADDATA\n", (unsigned long)me);
            /**
             * TODO Free the THREADATA object.
             * Freeing should be done by the same thread that created it.
             * See how the THREADDATA was created for an example of how this is done.
             */
            free(p);
            p = NULL; // set p to NULL so that other threads know that the THREADDATA is no longer available
        }
        else
        {
            printf("This is thread %lu and I can access the THREADDATA\n", (unsigned long)me);
        }
        // TODO critical section ends
        pthread_mutex_unlock(&tlock1);
        pthread_exit(NULL);

    } // end thread_runner
    return NULL;
}
