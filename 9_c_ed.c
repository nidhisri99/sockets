#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0); // define UDP socket

    struct sockaddr_in server, client;
    
    char buffer[256];
    
    //Host
    struct hostent *host;
    host = gethostbyname(argv[1]);

    //Server 
    server.sin_family = AF_INET;
    server.sin_addr = *((struct in_addr *)host->h_addr);
    server.sin_port = htons(atoi(argv[2]));

    printf("Please enter the message: ");
    fgets(buffer, 255, stdin); // Take input from stdin  

    sendto(sock, buffer, strlen(buffer), 0, &server, sizeof(struct sockaddr_in));//send content to server 
    
    int length = sizeof(client);
    int n = recvfrom(sock, buffer, 256, 0, &client, &length); // Reciever from server
    
    write(1, "Got an ack: ", 12);
    write(1, buffer, n); // Print ack 
}
