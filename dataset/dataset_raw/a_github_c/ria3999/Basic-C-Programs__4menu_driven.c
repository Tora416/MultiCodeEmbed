# include<stdio.h>
void sumofdigits(void);
void sumofseries(void);
void perfectno(void);
void exit(void);
void main()
{
    char option;
    printf ("choose the option");
    scanf("%c",&option);
    switch(option)
    {
    case'A':
        sumofdigits();
        break;
    case'B':
        perfectno();
        break;
    case'C':
        sumofseries();
        break;
    case'D':
        exit();
        break;
    }
}
void sumofdigits(void)
{
    int n,sum=0,d;
    printf("enter a number");
    scanf("%d",&n);
    while(n>0)
    {
        d=n%10;
        sum+=d;
        n=n/10;
    }
    printf("%d",sum);
}
void sumofseries(void)
{
    int n,i,sum=0;
    printf("enter the limit");
    scanf("%d",&n);
    for(i=1;i<=n;i=i+2)
    {
        sum+=i;
    }
    printf("%d",sum);
}

void perfectno(void)
{

    int i,sum=0,r;
    printf("enter the number");
    scanf("%d",&r);
   for(i=1;i<=r/2;i++)
   {
       if(r%i==0)
        sum+=i;

   }
   if(sum==r)
   printf("perfect no.");
   else
    printf("not");

}

void exit(void)
{
    return;
}
