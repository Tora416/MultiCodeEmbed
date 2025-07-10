#include<stdio.h>
int sum(int n)
{
    int ans=0,f;
    if(n<0)
        n=-n;
    if (n>0)
    {
        while(n>0)
        {
            f=n%10;
            ans+=f;
            n=n/10;
        }
    }
    return ans;
}
int evensum(int n)
{
    int ans=0,f;
    if(n<0)
        n=-n;
    if (n>0)
    {
        while(n>0)
        {
            f=n%10;
            if(f%2==0)
                ans+=f;
            n=n/10;
        }
    }
    return ans;
}
int oddsum(int n)
{
    int ans=0,f;
    if(n<0)
        n=-n;
    if (n>0)
    {
        while(n>0)
        {
            f=n%10;
            if(f%2!=0)
                ans+=f;
            n=n/10;
        }
    }
    return ans;
}
int main()
{
    int ch;
    while(1)
    {
        int n,ans=0;
        printf("\n1. Sum of the digits of a given number\n");
        printf("2. Sum of even digits of a given number\n");
        printf("3. Sum of the odd digits of a given number\n");
        printf("4. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            printf("\nEnter the integer: ");
            scanf("%d",&n);
            ans=sum(n);
            printf("Sum of digits of %d = %d\n",n,ans);
        }
        else if(ch==2)
        {
            printf("\nEnter the integer: ");
            scanf("%d",&n);
            ans=evensum(n);
            printf("Sum of even digits of %d = %d\n",n,ans);
        }
        else if(ch==3)
        {
            printf("\nEnter the integer: ");
            scanf("%d",&n);
            ans=oddsum(n);
            printf("Sum of odd digits of %d = %d\n",n,ans);
        }
        else if(ch==4)
        {
            printf("\nExitting program. Thank you.\n");
            break;
        }
        else
            printf("\nINVALID CHOICE. TRY AGAIN!\n");
    }
    return 0;
}