

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

int val = 100;

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    int fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd == -1)
        sys_err("open error");

    ftruncate(fd, 4); 

    
    int *p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(p == MAP_FAILED)
        sys_err("mmap error");

    close(fd);              
    pid_t pid = fork();
    if(pid < 0)
        sys_err("fork error");
    else if(pid == 0)
    {
        *p = 2000;          
        val = 1000;
        printf("child, *p = %d, var = %d\n", *p, val);
    }
    else
    {
        sleep(1);
        printf("parent, *p = %d, var = %d\n", *p, val);     
        wait(NULL);
        
        int ret = munmap(p, 4);
        if(ret == -1)
            perror("munmap error");
    }

    return 0;
}