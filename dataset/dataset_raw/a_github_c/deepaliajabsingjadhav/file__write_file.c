

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
    
    fd = open(name,O_RDWR | O_CREAT, 0777); 
    if(fd == -1)
    {
        printf("Unable to create file\n");
    }
    else
    {
        printf("File succesfully created with fd %d\n",fd);
    }
    printf("Enter the data that you want to write in the file\n");
    scanf(" %[^'\n']s",arr);
    length = strlen(arr);
    
    ret = write(fd,arr,length);
    if(ret == -1)
    {
        printf("Unable to write in the file\n");
    }
    else
    {
        printf("Data succesfully written in the file %d\n",ret);
    }
    
    close(fd);
    return 0;
}

