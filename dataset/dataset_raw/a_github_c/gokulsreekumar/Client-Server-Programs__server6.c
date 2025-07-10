#include<stdio.h>   
#include<string.h>  
#include<stdlib.h>  
#include<arpa/inet.h>
#include<sys/socket.h>

#include <unistd.h> 

#define BUFLEN 512  
#define PORT 8888   

void error(char *s)
{
    perror(s);
    exit(1);
}




int main(void)
{
    struct sockaddr_in si_server, si_client;
    
    int socket_udp, i, slen = sizeof(si_client) , recv_len;
    char buf[BUFLEN];
    
    
    if ((socket_udp=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        error("socket");
    }
    printf("UDP Socket created!\n");

    
    memset((char *) &si_server, 0, sizeof(si_server));
    
    
    si_server.sin_family = AF_INET;
    si_server.sin_port = htons(PORT);
    si_server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    
    if( bind(socket_udp , (struct sockaddr*)&si_server, sizeof(si_server) ) == -1)
    {
        close(socket_udp);
        error("bind");
    }
    printf("Socket bound to 0.0.0.0: 8888\n");
    
    while(1)
    {
        printf("Waiting for data...\n");
        fflush(stdout);
        bzero(buf, BUFLEN);

        
        
        if ((recv_len = recvfrom(socket_udp, buf, BUFLEN, MSG_WAITALL, (struct sockaddr *) &si_client, &slen)) == -1)
        {
            error("recvfrom()");
        }
        
        
        printf("\n--------- DATA PACKET ------------------\n");
        printf("Received Data Packet from %s:%d\n", inet_ntoa(si_client.sin_addr), ntohs(si_client.sin_port));
        printf("Data: %s\n" , buf);
        printf("----------------------------------------\n\n");
        
        
        if (sendto(socket_udp, buf, recv_len, 0, (struct sockaddr*) &si_client, slen) == -1)
        {
            error("sendto()");
        }
        
        bzero(buf, BUFLEN);
    }

    close(socket_udp);
    return 0;
}