

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
    struct student stu;
    int fd = open("temp", O_RDONLY);
    if(fd == -1)
        sys_err("open error");

    struct student *p = mmap(NULL, sizeof(stu), PROT_READ, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED)
        sys_err("mmap error");

    close(fd);
    
    while(1)
    {
        printf("id = %d, name = %s, age = %d\n", p->id, p->name, p->age);
        sleep(1);
    }

    munmap(p, sizeof(stu));

    return 0;
}