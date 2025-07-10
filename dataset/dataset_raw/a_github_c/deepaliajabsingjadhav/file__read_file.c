
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
    char name[20] = {'\0'};
    char arr[50] = {'\0'};
    int fd = 0;     
    int ret = 0, length = 0;
    char temp;
    
    printf("Enter file name\n");
    scanf("%s",name);
    
    fd = open(name,O_RDWR); 
    if(fd == -1)
    {
        printf("Unable to open file\n");
    }
    else
    {
        printf("File succesfully opened with fd %d\n",fd);
    }
    
    ret = read(fd,arr,10);
    if(ret == -1)
    {
        printf("Unable to read from the file\n");
    }
    else
    {
        printf("Data succesfully read\n");
    }
    printf("Data from file is : %s\n",arr);
    
    close(fd);
    return 0;
}


