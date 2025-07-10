


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 9734

void main() {
    
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    
    if (serverfd == -1) {
        printf("Couldn't create socket. Exiting!\n");
        exit(0);
    } else {
        printf("Socket created \n");
    }

    
    struct sockaddr_in server_address;
    int len = sizeof(server_address);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = PORT;

    
    int status = connect(serverfd, (struct sockaddr *)&server_address, len);
    
    
    if (status == -1) {
        printf("Couldn't connect. Exiting!\n");
        exit(0);
    } else {
        printf("Connection established!\n\n");
    }

    char time[100];

    read(serverfd, time, 100);
    printf("Server Time: %s\n", time);

    char processid[100];

    read(serverfd, processid, 100);
    printf("Server proccess ID: %s\n", processid);

    
    close(serverfd);
}