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

    int sock = socket(AF_INET, SOCK_STREAM, 0); // Define a socket

    printf("Socket created\n");

    struct hostent *host;
    host = gethostbyname("127.0.0.1"); // Get host name

    // Make connection to the server socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(17000);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    //Keep receiving
    int i = 1;
    while (1)
    {
        char receive[30];
        
        int bytes_received = recv(sock, receive, 20, 0); // Recieve from socket connected to server
        receive[bytes_received] = '\0';
        if (strcmp(receive, "exit") == 0)
        {
            close(sock);
            break;
        }
        else
        {
            printf("\nFrame %d data %s received\n", i, receive);
            send(0, receive, strlen(receive), 0); // sending 0 bytes is an indicator
            i++;
        }
    }
    close(sock);
    return (0);
}