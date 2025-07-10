#include <stdio.h>
#include<string.h>
void main()
{
int i,j,m,n;
char x[50];
char y[50];
int c[51][51];
char b[51][51];
printf("Enter the first string\n");
scanf("%s",x);
printf("Enter the second string\n");
scanf("%s",y);
m=strlen(x);
n=strlen(y);
for(i=1;i<=m;i++)
{
c[i][0]=0;
}
for(j=0;j<=n;j++)
{
c[0][j]=0;
}
for(i=1;i<=m;i++)
{
    for(j=1;j<=n;j++)
    {
        if(x[i-1]==y[j-1])
        {
        c[i][j]=c[i-1][j-1]+1;
        b[i][j]=92;
        }
        else if(c[i-1][j]>=c[i][j-1])
        {
            c[i][j]=c[i-1][j];
            b[i][j]='^';
        }
        else
        {
            c[i][j]=c[i][j-1];
            b[i][j]='<';   
        }
    }
}
for(i=0;i<=m;i++)
{
    for(j=0;j<=n;j++)
    {
        printf("%d ",c[i][j]);
    }
    printf("\n");
}
for(i=1;i<=m;i++)
{
    for(j=1;j<=n;j++)
    {
        printf("%c ",b[i][j]);
    }
    printf("\n");
}
        
}
