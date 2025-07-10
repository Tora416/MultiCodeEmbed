#include<stdio.h>   
#include<string.h> 
#include<stdlib.h> 
#include <unistd.h> 


#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512  
#define PORT 8888   

void error(char *s)
{
    perror(s);
    exit(1);
}



int main(void)
{
    struct sockaddr_in si_client;
    int socket_udp, i, slen=sizeof(si_client);
    char buf[BUFLEN];
    char message[BUFLEN];

    if ((socket_udp=socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        error("socket");
    }

    memset((char *) &si_client, 0, sizeof(si_client));

    si_client.sin_family = AF_INET;
    si_client.sin_port = htons(PORT);
    if (inet_aton(SERVER , &si_client.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while(1)
    {
        printf("Enter message : ");
        fgets(message, 512, stdin);
        
        if(strncmp(message, "close", 5)==0) {
            close(socket_udp);
            exit(0);
        }
        
        if (sendto(socket_udp, message, strlen(message) , 0 , (struct sockaddr *) &si_client, slen)==-1)
        {
            error("sendto()");
        }
        
        
        memset(buf,'\0', BUFLEN);

        
        
        if (recvfrom(socket_udp, buf, BUFLEN, 0, (struct sockaddr *) &si_client, &slen) == -1)
        {
            error("recvfrom()");
        }
        
        puts(buf);
    }

    close(socket_udp);
    return 0;
}