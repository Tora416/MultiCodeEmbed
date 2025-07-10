#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Brute_Force(char S[],char P[],int n,int m)
{
    int i=0,j=0,k;
    while(i<n && j<m)
    {
        k=i-m+1;
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
    }
    if(j==m)    
    {
        printf("pattern found at %d",k);
    }
    else
    {
        printf("pattern not found");
    }
}
void main()
{
    int n,m,i;
    char S[100],P[100];
    printf("\nEnter String:");
    scanf("%s",S);
    printf("\nEnter Pattern:");
    scanf("%s",P);
    n=strlen(S);
    m=strlen(P);
    Brute_Force(S,P,n,m);
}