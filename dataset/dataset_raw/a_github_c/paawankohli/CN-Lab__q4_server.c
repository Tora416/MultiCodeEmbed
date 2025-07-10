


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PORT 9734

void main() {
    
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    
    if (serverfd == -1) {
        printf("Couldn't create socket. Exiting!\n");
        exit(0);
    } else {
        printf("Socket created \n");
    }

    
    struct sockaddr_in server_address, client_address;
    int len = sizeof(server_address);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = PORT;

    
    if (bind(serverfd, (struct sockaddr *)&server_address, len) == -1) {
        exit(0);
    } else {
        printf("Binding successful!\n");
    }

    
    if (listen(serverfd, 5) == -1) {
        printf("Couldn't start listening. Exit.\n");
        exit(0);
    } else {
        printf("Server listening.\n\n");
    }

    while (1) {
        int clientfd = accept(serverfd, (struct sockaddr *)&client_address, &len);

        
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        char* time_to_output = malloc(strlen(asctime (timeinfo)) + 1);
        strcpy(time_to_output, asctime (timeinfo));

        
        write(clientfd, time_to_output, 100);

        
        char process_id_to_output[100];
        sprintf(process_id_to_output, "%d", getpid());
        write(clientfd, &process_id_to_output, 100);

        
        close(clientfd);
    }
}