#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    char c[100];
    int length,i,n,j,temp;
    printf("Enter the string:");
    gets(c);
    length=strlen(c);
    printf("\nEnter the number of shifts:");
    scanf("%d",&n);
    while(n!=0)
    {
        i=length-1;
        j=i;
        temp=c[i];
        while(j>=0)
        {
            i--;
             c[j]=c[i];
             j--;

        }
        c[0]=temp;
        n--;
    }
    printf("\nAfter shifting:");
    puts(c);
}

