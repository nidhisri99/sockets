#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    int sock = socket(AF_INET, SOCK_STREAM, 0); //Define socket 

    int portno = atoi(argv[1]); // Get port number from arg and atoi method to convert string to integer

    //Binding starts 
    struct sockaddr_in server, client_addr;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);    //convert an IP port number in byte order to the IP port number in network byte order.
    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Server waiting for client\n");

    // Listen to socket 
    listen(sock, 5);


    //Accept connection from client 
    int clilen = sizeof(client_addr);
    int client = accept(sock, (struct sockaddr *)&client_addr, &(clilen));

    //Read from client
    char buffer[256];
    read(client, buffer, 255);

    printf("SERVER : %s\n",buffer);
    printf("SERVER : %s Found!\n Transfering contents\n",buffer);

    // read file and store contents in c
    char ch,c[2000];
    int i = 0;
    freopen(buffer, "r", stdin);
    while ((ch = getc(stdin)) != EOF)
        c[i++] = ch;
    c[i] = '\0';

    printf("File content %s\n",c);
    
    // write c to client 
    write(client, c, 1999);

    return 0;
}
