#include<stdio.h>
#include<process.h>
struct time
{int h,m,s;
}x,y,z;
int main()
{
printf("____________________________________________________________________\n");
printf("\nEnter Duration 1");
printf("\nin sec:");
scanf("%d",&x.s);
printf("\nin min:");
scanf("%d",&x.m);
printf("\nin hours:");
scanf("%d",&x.h);

printf("\nEnter Duration 2");
printf("\nin sec:");
scanf("%d",&y.s);
printf("\nin min:");
scanf("%d",&y.m);
printf("\nin hours:");
scanf("%d",&y.h);
z.h=x.h+y.h;
z.m=x.m+y.m;
z.s=x.s+y.s;

if(z.s>=60)
{z.s=z.s-60;
z.m=z.m+1;
}
if(z.m>=60)
{z.m=z.m-60;
z.h=z.h+1;
}
printf("Final Value of time:");
printf("in hours:%d",z.h);
printf("in min:%d",z.m);
printf("in sec:%d",z.s);

return 0;
}

