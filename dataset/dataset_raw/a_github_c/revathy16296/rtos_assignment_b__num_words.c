#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

#define FILE_SIZE 100

int read_lines(char s[FILE_SIZE]);
int read_char();
char s[FILE_SIZE];
int main()
{
    FILE *f;
    int pid,c_cnt,fd[2];
    pipe(fd);
    printf("enter the source file path\n");
    scanf("%s",s);
    
    pid=fork();
    if(pid==0)
    {
        int c_cnt=0;
        printf("------inside the child process--------\n");
        close(fd[0]);
        c_cnt=read_char();
        printf("readed the character\n");
        printf("character :%d\n",c_cnt);
        write(fd[1],&c_cnt,sizeof(c_cnt));
        close(fd[1]);
    }
    else
    {
        wait(NULL);
        
        printf("-----back to parent process-----\n");
        int cnt;
        read_lines(s);
        close(fd[1]);
        read(fd[0],&cnt,sizeof(cnt));
        printf("The count of character in the file is :%d\n",cnt);
        close(fd[0]);
    }
    
    return 0;
}

int read_char()
{
    FILE *f;
    int character=0;
    char ch;
    f=fopen(s,"r");
    if (f == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    }
    while ((ch = fgetc(f)) != EOF)
    {
        if (ch != ' ' || ch != '\t' || ch != '\n' || ch != '\0'|| ch!='.')
        character++;
    }
    return(character);
}



int read_lines(char s[FILE_SIZE])
{
    FILE *f;
    int words;
    char ch;
    f=fopen(s,"r");
    if (f == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    }
    words = 0;
    while ((ch = fgetc(f)) != EOF)
    {
        

        
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0'|| ch=='.')
            words++;
    }
    
    printf("\tthe number of words are :%d\n",words);    
    fclose(f);
    return (1);
}
    