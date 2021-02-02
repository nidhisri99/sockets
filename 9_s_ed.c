#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Define UDP socket 

    char buffer[1024];
    
    // Start binding 
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    bind(sock, (struct sockaddr *)&server, sizeof(server));
    
    //Client 
    struct sockaddr_in client;
    int clilen = sizeof(struct sockaddr_in);
    while (1)
    {
        int n = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client, &clilen); // Recieve content from client

        write(1, "Received a datagram: ", 21);
        write(1, buffer, n);

        sendto(sock, "Got your message\n", 17,0, (struct sockaddr *)&client, clilen); // Send "got message" to client
    }
}