# include<stdio.h>
void main()
{
    int ar[90],n,i;
    printf("enter the limit");
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&ar[i]);
    largest(ar,n);
    sumaverage(ar,n);
    sorting(ar,n);
}
void largest(int ar[],int n)
{
    int max,i;
    max=ar[0];
    for(i=0;i<n;i++)
    {
        if(max<ar[i])
            max=ar[i];
    }
    printf("%d",max);
}
void sumaverage(int ar[],int n)
{
    int i,sum=0;
    float avg;
    for(i=0;i<n;i++)
        sum=sum+ ar[i];
        avg=(float)sum/n;
    printf("%d%f",sum,avg);
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
    printf("\n%d",a[i]);
}
