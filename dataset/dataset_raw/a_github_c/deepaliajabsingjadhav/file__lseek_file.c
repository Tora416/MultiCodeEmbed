





#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

void FileRead(char *name, int position)
{
    int fd = 0, ret = 0;
    char Mug[10] = {'\0'};
    fd = open(name,O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open file\n");
        return;
    }
    
    ret = lseek(fd,position,SEEK_SET);
    printf("Return value of lseek : %d\n",ret);
    
    ret = read(fd,Mug,10);
    printf("Data from the file is : \n");
    
    printf("Return value of read : %d\n",ret);
    write(1,Mug,ret);
    
    printf("\n");
    close(fd);
}
int main()
{
    char name[20];
    int value = 0;
    
    printf("Enter file name\n");
    scanf("%s",name);
    
    printf("Enter the position\n");
    scanf("%d",&value);
    
    FileRead(name,value);
    
    return 0;
}
