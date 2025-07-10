

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int FileCapitalCount(char *name)
{
    int fd = 0, ret = 0,iCnt = 0, i = 0;
    char Mug[100];
    
    fd = open(name,O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open file\n");
        return -1;
    }
    
    while((ret = read(fd,Mug,sizeof(Mug))) != 0)
    {
        for(i = 0; i<ret; i++)
        {
            if((Mug[i] >= 'A') && (Mug[i] <= 'Z'))
            {
                iCnt++;
            }
        }
    }
    
    close(fd);
 
    return iCnt;
}

int main()
{
    char name[20];
 
    int ret = 0;
    
    printf("Enter file name\n");
 
    scanf("%s",name);
    
   ret = FileCapitalCount(name);
    
    printf("Number of capital characters are : %d\n",ret);
    
    return 0;
}
