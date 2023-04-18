/**
 * Description: Takes in and Phone number of 3 persons
 * and then outputs a contacts list and each person's info.
 * Author emails: haroon.razzack@sjsu.edu and vincent.n.nguyen@sjsu.edu
 * Last modified date: 04-18-2023
 * Creation date: 04-17-2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct definition for ContactNode
typedef struct ContactNode
{
    char contactName[50];
    char contactPhoneNumber[50];
    struct ContactNode *nextNodePtr;
} ContactNode;

// function to initialize a new contact node
void InitializeContactNode(ContactNode *node, char name[], char phone[])
{
    strcpy(node->contactName, name);
    strcpy(node->contactPhoneNumber, phone);
    node->nextNodePtr = NULL;
}

// accessor function to get contact name
char *GetName(ContactNode *node)
{
    return node->contactName;
}

// accessor function to get contact phone number
char *GetPhoneNumber(ContactNode *node)
{
    return node->contactPhoneNumber;
}

// function to insert a new contact node after a given node
void InsertAfter(ContactNode *node, ContactNode *newNode)
{
    newNode->nextNodePtr = node->nextNodePtr;
    node->nextNodePtr = newNode;
}

// accessor function to get the next node in the linked list
ContactNode *GetNext(ContactNode *node)
{
    return node->nextNodePtr;
}

// function to print the details of a contact node
void PrintContactNode(ContactNode *node)
{
    printf("Name: %s\n", node->contactName);
    printf("Phone number: %s\n", node->contactPhoneNumber);
}

int main()
{
    ContactNode *head = NULL;
    ContactNode *currentNode = NULL;
    ContactNode *newNode = NULL;
    char name[50];
    char phone[50];

    // read in contact details and create linked list
    for (int i = 1; i <= 3; i++)
    {
        printf("Enter name for person %d: ", i);
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0'; // remove newline character

        printf("Enter phone number for person %d: ", i);
        fgets(phone, 50, stdin);
        phone[strcspn(phone, "\n")] = '\0'; // remove newline character

        newNode = (ContactNode *)malloc(sizeof(ContactNode));
        InitializeContactNode(newNode, name, phone);

        if (head == NULL)
        {
            head = newNode;
            currentNode = head;
        }
        else
        {
            InsertAfter(currentNode, newNode);
            currentNode = newNode;
        }
    }

    // output each contact
    currentNode = head;
    for (int i = 1; currentNode != NULL; i++)
    {
        printf("Person %d: %s, %s\n", i, GetName(currentNode), GetPhoneNumber(currentNode));
        currentNode = GetNext(currentNode);
    }

    // output linked list
    printf("\nCONTACT LIST\n");
    currentNode = head;
    while (currentNode != NULL)
    {
        PrintContactNode(currentNode);
        currentNode = GetNext(currentNode);
    }

    return 0;
}