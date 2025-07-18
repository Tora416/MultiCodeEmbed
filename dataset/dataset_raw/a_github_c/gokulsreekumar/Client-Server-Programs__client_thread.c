#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     

#include <sys/socket.h>
#include <arpa/inet.h>  

#include <pthread.h>
#include <signal.h>

#define PORT 8080       
#define LO "127.0.0.1"  

#define LENGTH 2048

char name[32];
char new_entry_message[42];


volatile sig_atomic_t flag = 0;

void str_overwrite_stdout();
void str_trim_lf(char *arr, int length);
void catch_ctrl_c_and_exit(int sig);


void* send_msg_handler(void*);
void* recv_msg_handler(void*);


void communication(int);
void block();

int main(int argc, char const *argv[])
{
    int socket_client = 0, n;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    

    printf("Please enter your name: ");
    fgets(name, 32, stdin);
    str_trim_lf(name, strlen(name));

    if (strlen(name) > 32 || strlen(name) < 2)
    {
        printf("Name must be less than 30 and more than 2 characters.\n");
        return EXIT_FAILURE;
    }

    
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

    
    strcpy(new_entry_message, name);
    strcat(new_entry_message, " joined! \n");

    send(socket_client, new_entry_message, 32, 0);

    
    printf("\n--------------------- WELCOME TO THE CHATROOM ---------------------\n");

    
    communication(socket_client);

    close(socket_client);

    return EXIT_SUCCESS;
}

void communication(int socket_client) {

    int* pclient = malloc(sizeof(int));
    *pclient = socket_client;
    
    pthread_t send_msg_thread;
    if (pthread_create(&send_msg_thread, NULL, (void *)send_msg_handler, pclient) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    
    pthread_t recv_msg_thread;
    if (pthread_create(&recv_msg_thread, NULL, (void *)recv_msg_handler, pclient) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    
    block();
}

void* send_msg_handler(void* pclient)
{
    int sockfd = *((int* ) pclient);
    char message[LENGTH] = {};
    char buffer[LENGTH + 32] = {};
    while (1)
    {
        str_overwrite_stdout();
        fgets(message, LENGTH, stdin);
        str_trim_lf(message, LENGTH);

        if (strcmp(message, "exit") == 0)
        {
            break;
        }
        else
        {
            sprintf(buffer, "%s: %s\n", name, message);
            send(sockfd, buffer, strlen(buffer), 0);
        }

        bzero(message, LENGTH);
        bzero(buffer, LENGTH + 32);
    }
    catch_ctrl_c_and_exit(2);
    return NULL;
}

void* recv_msg_handler(void* pclient)
{
    int sockfd = *((int* ) pclient);
    char message[LENGTH] = {};
    while (1)
    {
        int receive = recv(sockfd, message, LENGTH, 0);
        if (receive > 0)
        {
            printf("%s", message);
            str_overwrite_stdout();
        }
        else if (receive == 0)
        {
            break;
        }
        memset(message, 0, sizeof(message));
    }
    return NULL;
}

void str_trim_lf(char *arr, int length) {
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

void str_overwrite_stdout()
{
    printf("%s", "> ");
    fflush(stdout);
}

void block()
{
    while (1)
    {
        if (flag)
        {
            printf("\nBye.\n");
            return;
        }
    }
}

void catch_ctrl_c_and_exit(int sig)
{
    flag = 1;
}