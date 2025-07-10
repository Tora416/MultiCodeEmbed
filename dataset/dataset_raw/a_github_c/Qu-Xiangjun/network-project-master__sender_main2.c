
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "UDP_sender.h"


void welcome(){
    printf("[INFO] Usage: sender process.\n");
    printf("\n");
}

int main(){
    welcome();
    printf("Please input your message:");
    
    int strSize = 20; 
    int payload_len = 0; 
    char input  = NULL; 
    unsigned char *payload = (unsigned char*)malloc(sizeof(char)*20);
    while((input=getc(stdin))!='\n') {
        payload[payload_len++] = input;
        if(payload_len%20==0) { 
            strSize+=20;    
            payload =(unsigned char*)realloc(payload,strSize);
        }
    }
    payload[payload_len] = '\0';
    
    udp_sender(payload,payload_len);
    printf("[INFO] message send successfully!\n");
    return 0;
}
