#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    
    int sock = socket(AF_INET, SOCK_STREAM, 0); // Define socket 

    printf("Client Online !\n");

    int portno = atoi(argv[2]); // Get port number

    struct hostent* server;
    server = gethostbyname(argv[1]); // Get hostname

    //Connecting to server, same as bind almost
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
    connect(sock, (struct sockaddr_in *)&serv_addr, sizeof(serv_addr));

    printf("Server Online\n");

    //file path input from user
    char filepath[256],file[2000];
    printf("client : Enter path with file name\n");
    scanf("%s", filepath);

    //Write file path to socket 
    write(sock, filepath, strlen(filepath));

    //Read the response from server and store it in file
    read(sock, file, 2999);

    //Put contents of the file to stdout
    printf("Client : displaying from socket\n");
    fputs(file, stdout);
    return 0;
}