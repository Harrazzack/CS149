#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void func(char arr[])
{
    // Open the file for READ only.
    int f_read = open("start.txt", O_RDONLY);
    // Open the file for WRITE and READ only.
    int f_write = open("end.txt", O_WRONLY | O_CREAT, 0777);

    int count = 1; //start count at 1 
    int i = 0;

    while (read(f_read, arr, 1))
    {
        // Write every (1+3*i)th character to output file
        if (count == 1 + 3*i)
        {
            write(f_write, arr, 1); 
            i++;
        }
        count++;
    }
    //remember to close files 
    close(f_write);
    close(f_read);
}

int main()
{
    char arr[100];

    // Calling for the function
    func(arr);

    return 0;
}
