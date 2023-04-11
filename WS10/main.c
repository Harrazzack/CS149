/**
 * Description: Program that takes in an input string as an item name,
 * its integer price and quantity, and then ouputs the total price.
 * This is accomplished using structs.
 * Authors: Haroon Razzack
 * Author emails: haroon.razzack@sjsu.edu
 * Last modified date: 04-10-2023
 * Creation date: 04-9-2023
 */
#include <stdio.h>
#include "ItemToPurchase.h"
#include <string.h>

int main(void)
{
    ItemToPurchase item1, item2;
    char c;

    // Prompt for first item
    printf("Item 1\n");
    printf("Enter the item name:\n");
    fgets(item1.itemName, 50, stdin);
    item1.itemName[strcspn(item1.itemName, "\n")] = '\0'; // remove newline character
    printf("Enter the item price:\n");
    scanf("%d", &item1.itemPrice);
    printf("Enter the item quantity:\n");
    scanf("%d", &item1.itemQuantity);
    // remove unneccessary input from buffer
    c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }

    // Prompt for second item
    printf("\nItem 2\n");
    printf("Enter the item name:\n");
    fgets(item2.itemName, 50, stdin);
    item2.itemName[strcspn(item2.itemName, "\n")] = '\0'; // remove newline character
    printf("Enter the item price:\n");
    scanf("%d", &item2.itemPrice);
    printf("Enter the item quantity:\n");
    scanf("%d", &item2.itemQuantity);
    // remove unneccessary input from buffer
    c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }

    // Print item costs
    printf("\nTOTAL COST\n");
    PrintItemCost(item1);
    PrintItemCost(item2);
    printf("Total: $%d\n", ((item1.itemPrice * item1.itemQuantity) + (item2.itemPrice * item2.itemQuantity)));

    return 0;
}
