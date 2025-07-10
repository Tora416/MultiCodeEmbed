#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

#define SIZE 30

int main()
{
    char str[SIZE];
    int i,n=0,pid,fd[2],f1[2];
    pipe(fd);
    
    printf("enter the string with in 30 letter or else change the string size  in pgm:\n");
    fgets(str,sizeof(str),stdin);
    
    for(i=1;str[i]!='\0';i++)
        {
        n++;
        }
    printf("the number of character in the string is %d\n",n);
    
    
    
    pid=fork();
    if (pid==0)
    {
        
        printf("inside the child process--------\n");
        char b[SIZE],ch;
        int n,vowel=0,i=0;
        close(fd[1]);
        read(fd[0],b,sizeof(b));
        close(fd[0]);
        
        
        
        n=strlen(b);
        printf("the string gets to the child using pipes is :%s\n",b);
        while(i<=n)
        {
            ch=b[i];
            if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'||ch=='A'||ch=='E'||ch=='I'||ch=='O'||ch=='U')
            {vowel++;}
            i++;
        }
        printf("the vowel count in the given string is %d",vowel);
    }
    else{
        close(fd[0]);
    write(fd[1],str,sizeof(str));
    close(fd[1]);
        wait(NULL);
        printf("\n********back to parent process******!");
    }
        return 0;
}       
    
    

