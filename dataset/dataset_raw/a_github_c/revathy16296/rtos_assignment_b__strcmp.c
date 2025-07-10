#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>

#define SIZE 10

int n;
void choice_zero(char b[SIZE]);
void choice_one(char b[SIZE]);

int main(int argc,char *argv [])
{
    char s[SIZE],b[SIZE];
    int a,p[2],pid;
    pipe(p);
    if (argc<2)
    {printf("enter the format ./'name',stringFFF,choice'1 or 0'");}
    strcpy(s,argv[1]);
    strcpy(b,s);
    a=atoi(argv[2]);
    if (a==0)
    {choice_zero(b);}
    else if(a==1)
    {choice_one(b);}
    else
    {return 1;}
    printf("writing to child\n");

    pid=fork();
    if(pid==0)
    {printf("inside  child-------\n");
    char c[SIZE];
    close(p[1]);
    read(p[0],c,10);
    n=strlen(c);
    printf("the string count is %d\n",(n-3));
    close(p[0]);
    }
    else{
    close(p[0]);
    write(p[1],s,10);
    close(p[1]);
    printf("writed\n");
        wait(NULL);
    }
    return 0;
}

void choice_one(char b[SIZE])
{
    char p[SIZE]="SIOSFFF";
    

        if (strcmp(b,p)==0)
        {printf("the value is matching with SIOS\n");}
        else{
        printf("the  string is not matching with SIOS\n");}
        
}
    
void choice_zero(char b[SIZE])
{
        char r[SIZE]="MCISFFF";
        if (strcmp(b,r)==0)
        {printf("the value is matching with MCIS\n");}
        else{
        printf("the  string is not matching with MCIS\n");
        }
}   
        