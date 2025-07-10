#include<stdio.h>
int main()
{
    int l,n,i;
    scanf("%d",&l);
    scanf("%d",&n);
    for(i=l;i<=n;i++)
    {
        if(i==1)
     {
        printf("One\n");
     }
    else if(i==2)
     {
        printf("Two\n");
     }
    else if(i==3)
     {
        printf("Three\n");
     }
    else if(i==4)
     {
        printf("Four\n");
     }
    else if(i==5)
     {
        printf("Five\n");
     }
    else if(i==6)
     {
        printf("Six\n");
     }
    else if(i==7)
     {
        printf("Seven\n");
     }
    else if(i==8)
     {
        printf("Eight\n");
     }
    else if(i==9)
     {
        printf("Nine\n");
     }
     else if(i%2==0)
     {
        printf("even\n");
     }
     else
     printf("odd\n");
    }
    return 0;
}
