#include<stdio.h>
#include<conio.h>
int main()
{
    system("cls");
    int a[100];
    int n,i,j,k;
    printf("Enter the no. of elements:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(a[i] == a[j])
            {
                for(k=j;k<n;k++)
                {
                    a[k] = a[k+1];
                }
                n--;
                j--;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        printf("%d\t",a[i]);
    }
    getch();
}
