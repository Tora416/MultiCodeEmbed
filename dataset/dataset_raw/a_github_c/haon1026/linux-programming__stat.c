

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat buf;
    
    int ret = lstat(argv[1], &buf);
    if(ret == -1)
    {
        perror("stat error");
        exit(1);
    }

    printf("file size:%d\n", buf.st_size);
    printf("inode number:%d\n", buf.st_ino);

    if(S_ISREG(buf.st_mode))
        printf("%s is a regular file\n", argv[1]);
    else if(S_ISDIR(buf.st_mode))
        printf("%s is a directory\n", argv[1]);
    else if(S_ISLNK(buf.st_mode))
        printf("%s is a symbolic link\n", argv[1]);      
    

    return 0;
}