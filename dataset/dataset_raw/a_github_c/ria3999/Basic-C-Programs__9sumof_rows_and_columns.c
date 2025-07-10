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

}
void sumofrows(int b[][90],int r,int c)
{
    int sum=0,i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            sum=sum+b[i][j];
        }
        printf("hggh");
        printf("%d",sum);
    }

}
