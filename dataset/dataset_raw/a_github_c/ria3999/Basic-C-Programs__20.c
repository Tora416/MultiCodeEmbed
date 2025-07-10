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
    sum(a,r,c);
}
void sum(int a[][90],int r,int c)
{
    int i,j,sum=0;
    if(r!=c)
        printf("not a square matrix");
    else
    {
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if(j<i)
                    sum=sum+a[i][j];
            }
        }
    }
    printf("%d",sum);
}
