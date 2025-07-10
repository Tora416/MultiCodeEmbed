# include<stdio.h>
void largest(int a[][90],int ,int);
void main()
{
    int a[90][90],r,c,i,j;
    printf("enter no of rows and columns");
    scanf("%d%d",&r,&c);
    printf("enter ele");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    largest(a,r,c);
}
void largest(int a[][90],int r,int c)
{
    int max=a[0][0],i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(max<a[i][j])
                max=a[i][j];
        }
    }
    printf("%d",max);
}
