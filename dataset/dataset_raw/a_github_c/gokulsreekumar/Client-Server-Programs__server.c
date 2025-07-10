#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define BUFSIZE 1024

struct message {
    int type;
    char data[BUFSIZE];
};


void server_set_up(int *sockfd, struct sockaddr_in *server_addr);

void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr);

void send_recv(int i, fd_set *master, int sockfd, int fdmax);

int main()
{
    fd_set master, read_fds;

    int fdmax, i;
    int sockfd = 0;

    struct sockaddr_in server_addr, client_addr;

    
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    server_set_up(&sockfd, &server_addr);

    
    FD_SET(sockfd, &master);

    
    fdmax = sockfd;

    while (1)
    {
        
        read_fds = master;

        
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(4);
        }

        
        for (i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if (i == sockfd)
                    
                    
                    connection_accept(&master, &fdmax, sockfd, &client_addr);
                else
                    
                    send_recv(i, &master, sockfd, fdmax);
            }
        }
    }
    return 0;
}

void server_set_up(int *sockfd, struct sockaddr_in *server_addr)
{
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }

    
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(PORT);
    server_addr->sin_addr.s_addr = INADDR_ANY;

    

    
    if (bind(*sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Unable to bind");
        exit(1);
    }
    printf("TCP Server Bound to Port: %d\n", PORT);
    
    if (listen(*sockfd, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("TCP Server Waiting for Client Requests...\n");
    fflush(stdout);
}


void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int newsockfd;

    if ((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1)
    {
        perror("accept");
        exit(1);
    } 
    else 
    {
        
        FD_SET(newsockfd, master);
        
        if (newsockfd > *fdmax)
            *fdmax = newsockfd;
        printf("New connection at %s : %d \n", inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
    }
}

void send_recv(int i, fd_set *master, int sockfd, int fdmax) 
{
    int recv_size, j;
    char recv_buf[BUFSIZE], buf[BUFSIZE];
    if ((recv_size = recv(i, recv_buf, BUFSIZE, 0)) <= 0)
    {
        if (recv_size == 0)
            printf("Socket with FD: %d Hung Up\n", i);
        else
            perror("recv");

        
        
        close(i);
        FD_CLR(i, master);
    }
    else
    {
        for (j = 0; j <= fdmax; j++)
        {
            
            if (FD_ISSET(j, master))
            {
                if (j != sockfd && j != i)
                {
                    if (send(j, recv_buf, recv_size, 0) == -1)
                    {
                        perror("send");
                    }
                }
            }
        }
        printf("%s\n", recv_buf);
        bzero(recv_buf, BUFSIZE);
    }
}