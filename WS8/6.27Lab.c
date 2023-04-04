#include <stdio.h>
#include <string.h>

int CalcNumCharacters(char *userString, char userChar)
{
    int count = 0;
    for (int i = 0; userString[i] != '\0'; i++)
    {
        if (userString[i] == userChar)
        {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <char> <string>\n", argv[0]);
        return 1;
    }
    char userChar = argv[1][0];
    char *userString = argv[2];
    int count = CalcNumCharacters(userString, userChar);
    printf("%d %c%s\n", count, userChar, (count != 1) ? "'s" : "");
    return 0;
}
