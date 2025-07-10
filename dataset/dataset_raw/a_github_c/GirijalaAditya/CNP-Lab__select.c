#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include<sys/select.h>
#include <unistd.h>

void main() 
{
    fd_set readfd;
        char ch;
    FD_ZERO(&readfd);
    FD_SET(0,&readfd);
    struct timeval tm;
    tm.tv_sec=5;
    tm.tv_usec=3000000;
    
    int ret=select(1,&readfd,NULL,NULL,&tm);
    if(ret==-1)
    {
        printf("SEL-ERR");
        exit(0);
    }
    else if(ret==0)
    {
    printf("Timeout Occured");
    }
    else
    {   
        if(FD_ISSET(0,&readfd))
        {
            scanf("%c",&ch);
            printf("The character is %c\n",ch);
    
        }
    }   
}
