

#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


void sys_err(const char* str)
{
    perror(str);
    exit(1);
}

void catch_child(int signo)
{
    pid_t wpid;
    int status;

    
    while((wpid = waitpid(-1, &status, 0)) != -1)      
    {
        if(WIFEXITED(status))
            printf("catch child, pid = %d, ret = %d\n", wpid, WEXITSTATUS(status));
    }

    
    
    
    return;
}

int main()
{
    
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    pid_t pid;
    int i;
    for(i = 0; i < 10; i++)
    {
        if((pid =fork()) == 0)          
            break;
    }

    if(i == 10)
    {
        struct sigaction act;               
        act.sa_handler = catch_child;       
        sigemptyset(&act.sa_mask);          
        act.sa_flags = 0;                   
        sigaction(SIGCHLD, &act, NULL);     

        
        sigprocmask(SIG_UNBLOCK, &set, NULL);   

        printf("I'm parent, pid = %d\n", getpid());
        
        int num = 0;
        while(1)
        {
            printf("num = %d\n", num++);
            sleep(1);
        }
    }
    else
    {
        printf("I'm child, pid = %d\n", getpid());
        return i;
    }

    return 0;
}