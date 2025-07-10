# include<stdio.h>
void main()
{
    int a[90],i,n;
    printf("enter the limit");
    scanf("%d",&n);
    printf("enter the array elements");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    sorting(a,n);
}
void sorting(int a[],int n)
{
    int i,j,t;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }

    }
    for(i=0;i<n;i++)
        printf("%d",a[i]);

}
