#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char p[100], f[100], c[3000];
    int f1, fd, fd2;
    mknod("fifo1", S_IFIFO | 0666, 0); // same as server program
    mknod("fifo2", S_IFIFO | 0666, 0);

    printf("\n waiting for server...\n");

    fd = open("fifo1", O_WRONLY); // Open fifo1 in write mode to write the file name we want

    printf("\n SERVER ONLINE !\n CLIENT:Enter the path\n");
    gets(p); // Read filename from user

    write(fd, p, strlen(p)); // write the same to file fifo 1 
    printf("Waiting for reply....\n");

    fd2 = open("fifo2", O_RDONLY); 
    read(fd2, c, 3000);// Read contents of file from fifo2 
    printf("File recieved! displaying the contents:\n");
    fputs(c, stdout); // Print the contents to std out
    exit(1);
}