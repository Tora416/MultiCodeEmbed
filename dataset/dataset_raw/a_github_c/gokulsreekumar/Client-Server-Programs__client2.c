#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#include <sys/socket.h>
#include <arpa/inet.h> 
#include <netinet/in.h>

#include <signal.h>
#include <errno.h>

#define BUFSIZE 1024
#define LO "127.0.0.1"
#define PORT 8080







struct message
{
    int type;
    char name[32];
    char data[BUFSIZE];
};

void trim_newline(char *arr, int length);

void connect_request(int *sockfd, struct sockaddr_in *server_addr);
void send_recv(int i, int sockfd, char name[32], fd_set *master);

int main()
{
    int sockfd, fdmax, i;
    struct sockaddr_in server_addr;
    fd_set master;
    fd_set read_fds;
    char name[32];
    char password[32];
    char new_entry_message[45];

    
    printf("Please enter your name: ");
    fgets(name, 32, stdin);
    trim_newline(name, strlen(name));
    if (strlen(name) > 32 || strlen(name) < 2)
    {
        printf("Name must be less than 30 and more than 2 characters.\n");
        return EXIT_FAILURE;
    }
    printf("Please enter your password: ");
    fgets(password, 32, stdin);
    trim_newline(password, strlen(password));

    
    connect_request(&sockfd, &server_addr);

    
    struct message new_member_message;
    new_member_message.type = 1;
    strcpy(new_member_message.name, name);
    strcpy(new_member_message.data, password);
    send(sockfd, &new_member_message, sizeof(struct message), 0);

    
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    
    
    FD_SET(0, &master);
    FD_SET(sockfd, &master);

    printf("\nWelcome to Project COBRA\n");

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
            if (FD_ISSET(i, &read_fds))
                send_recv(i, sockfd, name, &master);
    }
    close(sockfd);
    return 0;
}

void connect_request(int *sockfd, struct sockaddr_in *server_addr)
{
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }

    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(PORT);
    server_addr->sin_addr.s_addr = inet_addr(LO);

    if (connect(*sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
}
int cnt = 0;
void send_recv(int i, int sockfd, char name[32], fd_set *master)
{
    char in_buf[BUFSIZE];
    char send_buf[BUFSIZE + 32] = "";
    char recv_buf[BUFSIZE];
    char disconnect_mssge[32];
    struct message send_message, recv_message;
    int nbyte_recvd;
    if (i == 0)
    {
        fgets(in_buf, BUFSIZE, stdin);
        trim_newline(in_buf, BUFSIZE);

        
        send_message.type = 0;
        strcpy(send_message.name, name);
        sprintf(send_message.data, "%s", in_buf);

        if (strncmp(in_buf, "bye", 3) == 0)
        {
            send_message.type = 2;
            sprintf(send_message.data, "left the discussion");
            send(sockfd, &send_message, sizeof(struct message), 0);
            FD_CLR(i, master);
            close(i);
            close(sockfd);
            exit(0);
        }
        else
            send(sockfd, &send_message, sizeof(struct message), 0);
        bzero(in_buf, BUFSIZE);
    }
    else
    {
        nbyte_recvd = recv(sockfd, &recv_message, sizeof(struct message), 0);
        if (nbyte_recvd == 0) {
            close(sockfd);
            exit(1);
        }
        if (recv_message.type == 0)
        {
            printf("[%s]: %s\n", recv_message.name, recv_message.data);
        }
        else if (recv_message.type == 1)
        {
            printf("%s joined the chat!\n", recv_message.name);
        }
        else if (recv_message.type == 2)
        {
            printf("%s left the chat!\n", recv_message.name);
        }
        else if (recv_message.type == 3)
        {
            printf("%d. %s is present\n", ++cnt, recv_message.name);
        }
        else if (recv_message.type == 4) 
        {
            printf("Sorry Wrong Password. Try Again to Enter\n");
            close(sockfd);
            exit(0);
        }
    }
}

void trim_newline(char *arr, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}
