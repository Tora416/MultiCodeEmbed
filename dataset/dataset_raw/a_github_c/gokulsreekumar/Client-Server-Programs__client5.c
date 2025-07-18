#include <stdio.h> 
#include <string.h> 
#include <unistd.h>     

#include <sys/socket.h> 
#include <arpa/inet.h>  

#include <pthread.h>

#define PORT 8080       
#define LO "127.0.0.1"  

int main(int argc, char const *argv[]) 
{ 
    int socket_client = 0, n; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 

    
    if ((socket_client = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    }

    
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    
    
    if(inet_pton(AF_INET, LO , &serv_addr.sin_addr)<=0) 
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 

    
    if (connect(socket_client, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
    
    
    while(1) {
        bzero(buffer, 1024);
        printf("Enter Client's Message: ");
        fgets(buffer, 1024, stdin);
        char bye[5] = "close";
        if(strncmp(buffer, "close", 5)==0) {
            n = send(socket_client , bye, 1024, 0); 
            
            close(socket_client);
            break;
        }
        n = send(socket_client , buffer, 1024, 0); 
        if(n<0) {
            printf("Reading Error!\n");
        }
        bzero(buffer, 1024);
        n = recv(socket_client , buffer, 1024, 0); 

        printf("Server: %s\n", buffer);
        bzero(buffer, 1024);

    }
    printf("Client Closed Connection.\n"); 
    return 0; 
} 

