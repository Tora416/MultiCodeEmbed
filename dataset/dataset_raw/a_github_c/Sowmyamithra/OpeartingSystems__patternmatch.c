#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Brute_Force(char S[],char P[],int n,int m)
{
    int i=0,j=0;
    int flag=-1;
    while(i<n && j<m)
    {
        if(P[j]==S[i])
        {
            i=i+1;
            j=j+1;
        }
        else
        {
            i=i+1;
            j=0;
        }
    if(j==m)
    {
        flag=1;
        printf("\npattern found at %d",(i-j+1));
        j=0;
    }
}
    if(flag==-1)
    {
        printf("pattern not found");
    }
}
void main()
{
    int n,m,i;
    char S[100],P[100];
    printf("\nEnter String:");
    gets(S);
    printf("\nEnter Pattern:");
    gets(P);
    n=strlen(S);
    m=strlen(P);
    Brute_Force(S,P,n,m);
}
