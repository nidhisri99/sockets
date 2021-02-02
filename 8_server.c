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
    char p[100], f[100], c[300], ch;
    int num, num2, f1, fd, fd2, i = 0;

    mknod("fifo1", S_IFIFO | 0666, 0); // Creates a file in mode
    mknod("fifo2", S_IFIFO | 0666, 0);

    printf("SERVER ONLINE\n");

    fd = open("fifo1", O_RDONLY); // File handler to read the name of the file written in fifo1 by client

    printf("client online\nwaiting for request\n\n");

    num = read(fd, p, 100); // To read the name of the file written by client in p
    p[num] = '\0';

    f1 = open(p, O_RDONLY); // Open the file client wants

    printf("\nserver:%s found \ntranfering the contents", p);

    stdin = fdopen(f1, "r"); // attach stdin to the file client wants

    while ((ch = getc(stdin)) != EOF) // Read from stdin i.e from client file
        c[i++] = ch;
    c[i] = '\0';

    printf("\nfile contents \n %s ", c);

    fd2 = open("fifo2", O_WRONLY); // Open in write mode fifo2 to write the contents of file

    write(fd2, c, strlen(c)); // write to that file

    printf("\nserver :tranfer completed");

    exit(1);
}
