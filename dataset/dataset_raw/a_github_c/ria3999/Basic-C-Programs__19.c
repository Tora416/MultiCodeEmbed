# include<stdio.h>
void main()
{
    int a[90][90],r,c,i,j;
    printf("enter no. of rows and columns");
    scanf("%d%d",&r,&c);
    printf("enter array elements");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    sumofrows(a,r,c);
    sumofcolumns(a,r,c);

}
void sumofrows(int a[][90],int r,int c)
{
    int i,j,sumofrows;
    for(i=0;i<r;i++)
    {
        sumofrows=0;
        for(j=0;j<c;j++)
        {
            sumofrows=sumofrows+a[i][j];
        }
        printf("%d",sumofrows);

    }
}
void sumofcolumns(int a[][90],int r,int c)
{
    int i,j,sumofcolumns;
    for(i=0;i<r;i++)
    {
        sumofcolumns=0;
        for(j=0;j<c;j++)
        {
            sumofcolumns=sumofcolumns+a[j][i];
        }
        printf("%d",sumofcolumns);
    }
}
