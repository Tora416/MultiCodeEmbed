#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int a[50], b[50];
    printf("The elements are\n");
    int i,j;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        b[i] = -1;
    }
    for(i=0;i<n;i++)
    {
        int count = 1;
        for(j=i+1;j<n;j++)
        {
            if(a[i] == a[j])
            {
                count++;
                b[j] = 0;
            }
        }
        if(b[i]!=0)
        {
            b[i] = count;
        }
    }
    printf("Frequencies are:\n");
    for(i=0;i<n;i++)
    {
        if(b[i]!=0)
        {
            printf("%d occurence is : %d\n", a[i],b[i]);
        }
    }
    return 0;
}
