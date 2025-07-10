

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

struct student
{
    int id;
    char name[256];
    int age;
};

int main()
{
    struct student stu = {1, "zhangsan", 18};
    int fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd == -1)
        sys_err("open error");

    ftruncate(fd, sizeof(stu)); 

    struct student *p = mmap(NULL, sizeof(stu), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED)
        sys_err("mmap error");

    close(fd);
    
    while(1)
    {
        memcpy(p, &stu, sizeof(stu));
        stu.id++;
        sleep(1);
    }

    munmap(p, sizeof(stu));

    return 0;
}