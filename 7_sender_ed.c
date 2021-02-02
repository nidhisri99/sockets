#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main()
{

    int sock = socket(AF_INET, SOCK_STREAM, 0); // Define socket

    //Bind starts 
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(17000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    

    listen(sock, 5); // Listen to socket 

    //Accept connection from client 
    struct sockaddr_in client_addr;
    int clilen = sizeof(struct sockaddr_in);
    int client = accept(sock, (struct sockaddr *)&client_addr, &clilen);

    //Input from user - dataframes
    char fr[30] = " ",data[1024];
    int i = 1;
    while (strcmp(fr, "exit") != 0)
    {
        printf("Enter Data Frame %d:(Enter exit for End):", i);
        scanf("%s", fr);

        send(client, fr, strlen(fr), 0); // Send the frames to user 

        recv(sock, data, 1024, 0); // recieve a message from a connected socket (getting acknowledgment)
        i++;
    }
    close(sock);
    return (0);
}