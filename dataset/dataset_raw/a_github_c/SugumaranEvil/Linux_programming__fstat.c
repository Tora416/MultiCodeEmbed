







#include "fstat.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int main()
{
    int fst,file_des;
    struct stat detail;

    file_des = open("./text",O_RDONLY);
    perror("open");
    printf("fd %d\n",file_des);

    fst = fstat(file_des,&detail);
    perror("fstat");
    printf("fst %d\n",fst);

    printf("inode number %lu\n",detail.st_ino);
    printf("hard link  %lu\n",detail.st_nlink);
    printf("user id %lu\n",detail.st_uid);
    printf("group id %lu\n",detail.st_gid);
    printf("size %lu\n",detail.st_size);
}
