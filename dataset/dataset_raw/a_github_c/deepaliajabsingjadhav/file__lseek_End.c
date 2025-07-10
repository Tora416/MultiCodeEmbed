

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int FileSize(char *name)
{
    int fd = 0, ret = 0;

    fd = open(name,O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open file\n");
        return -1;
    }
    
    ret = lseek(fd,0,SEEK_END); 
    
    close(fd);

    return ret;
}

int main()
{
    char name[20];
    int ret = 0;
    
    printf("Enter file name\n");
    scanf("%s",name);
    
   ret = FileSize(name);
    
    printf("File size is : %d\n",ret);
    
    return 0;
}
