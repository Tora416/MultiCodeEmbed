#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    char a[100];
    char b[100];
    int i;
    int s;
    int ct=0;
    printf("enter string-1:");
    gets(a);
    printf("\nenter string-2");
    gets(b);
    s=(strlen(a)>strlen(b))?(strlen(a)):(strlen(b));
    for(i=0;i<s;i++)
    {
        if(a[i]==b[i])
        {
            ct++;
        }
        else
        {
            ct=-1;
            break;
        }
    }
    if(ct==-1)
    printf("\nstrings are not equal");
    else
    printf("\nstrings are same");
}
