#include<stdio.h>
long int static count=0;
void TOH(int n,char A,char B,char C)
{
if(n==1)
{
count++;
printf("\nMove %c to %c",A,B);
count++;
}
else
{
TOH(n-1,A,C,B);
count++;
printf("\nMove %c to %c",A,B);
count++;
TOH(n-1,C,B,A);
count++;
}
}
int main()
{
int n = 0;
char A='A',B='B',C='C';
printf("Enter the number of disc:");
scanf("%d",&n);
TOH(n,A,B,C);
printf("\n\nCount=%ld",count);
printf("\n");
return 0;
}
