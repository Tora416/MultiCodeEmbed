#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SIZE 10

void choice_zero(char b[SIZE]);
void choice_one(char b[SIZE]);

int n;

int main(int argc,char *argv [])
{
    char s[SIZE],b[SIZE];
    int a,i;
    if (argc<2)
    {printf("enter the format ./'name',stringFFF,choice'1 or 0'");}
    strcpy(s,argv[1]);
    n=strlen(s);
    
    
    strcpy(b,s);
    a=atoi(argv[2]);
    if (a==0)
    {choice_zero(b);}
    else if(a==1)
    {choice_one(b);}
    else
    {printf("\nthe length of the given string is %d",(n-3));}
    return 0;
}

void choice_one(char b[SIZE])
{
    char p[4]="SIOS";
    

        if (strncmp(b,p,4)==0)
        {printf("the value is matching with SIOS\n");}
        else{
        printf("the  string is not matching with SIOS\n");
        printf("the length of given string is %d",n-3);}
}
    
void choice_zero(char b[SIZE])
{
        char r[4]="MCIS";
        if (strncmp(b,r,4)==0)
        {printf("the value is matching with MCIS\n");}
        else{
        printf("the  string is not matching with MCIS\n");
        printf("the length of given string is %d",n-3);}
}   
        