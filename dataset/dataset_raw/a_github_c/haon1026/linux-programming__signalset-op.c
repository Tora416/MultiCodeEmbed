

#define _POSIX_SOURCE

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sys_err(const char* str)
{
    perror(str);
    exit(1);
}

void print_set(sigset_t *pset)
{
    for(int i = 1; i < 32; i++)
    {
        if(sigismember(pset, i))
            putchar('1');
        else
            putchar('0');
    }
    printf("\n");
}

int main()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGKILL);   
    sigaddset(&set, SIGBUS);

    sigset_t oldset;
    int ret = sigprocmask(SIG_BLOCK, &set, &oldset);
    if(ret == -1)
        sys_err("sigprocmask error");
    
    sigset_t pendset;
    while(1)
    {
        ret = sigpending(&pendset);
        if(ret == -1)
            sys_err("sigpending error");

        print_set(&pendset);
        sleep(1);
    }

    return 0;
}