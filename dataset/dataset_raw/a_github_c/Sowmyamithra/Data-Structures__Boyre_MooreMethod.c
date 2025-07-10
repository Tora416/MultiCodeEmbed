#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int Last_Occurence(char P[],int m,char c)
{
    int i,k=0;
    for(i=m-1;i>=0;i--)
    {
        if(P[i]==c)
        k=i;
    }
    return(k);
}
int Boyre_Moore(char S[],char P[],int n,int m)
{
    int i=m-1,j=m-1,l;
    while(i<n && i>=0)
    {
        if(P[j]==S[i])
        {
            if(j==0)
            return(i);
            else
            {
                i=i-1;
                j=j-1;
            }
        }
        else
        {
            l=Last_Occurence(P,m,S[i]);
            i=i+m-(l+1);
            j=m-1;
        }
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
    i=Boyre_Moore(S,P,n,m);
    printf("\nThe pattern is found at position %d",i);
}