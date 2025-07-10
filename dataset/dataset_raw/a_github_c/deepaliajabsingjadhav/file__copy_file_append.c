

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

void FileCopyAppend(char *src,char *dest)
{
    int fdscr = 0, fddest = 0, ret = 0, i = 1;
    char Mug[100] = {'\0'};
    
    fdscr = open(src,O_RDONLY);
    if(fdscr == -1)
    {
        printf("Unable to open source file\n");
        return;
    }
    fddest = open(dest, O_WRONLY | O_APPEND);
    if(fddest == -1)
    {
        printf("Unable to open destination file\n");
        close(fdscr);
        return;
    }
    
    while((ret = read(fdscr,Mug,sizeof(Mug))) != 0)
    {
        printf("Iteration : %d Size Read : %d\n", i, ret);
        i++;
        write(fddest, Mug,ret);
    }
    
    close(fdscr);
    close(fddest);
}

int main()
{
    char name1[20];
    char name2[20];
    
    printf("Enter source file name\n");
    scanf("%s",name1);
    
    printf("Enter destination file name\n");
    scanf("%s",name2);
    
    FileCopyAppend(name1,name2);
    
    return 0;
}
