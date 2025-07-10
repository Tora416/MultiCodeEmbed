#include<stdio.h>
int main()
{

   int a[2][2];
   int r1, c1;
   for(r1=0; r1<=1; r1++)
   {
       for(c1=0; c1<=1; c1++)
       {
           scanf("%d", &a[r1][c1]);
       }
   }
   for(r1=0; r1<=1; r1++)
   {
       for(c1=0; c1<=1; c1++)
       {
           printf("%d ", a[r1][c1]);
       }
       printf("\n");
   }
   int b[2][2];
   int r2, c2;
   for(r2=0; r2<=1; r2++)
   {
       for(c2=0; c2<=1; c2++)
       {
           scanf("%d", &b[r2][c2]);
       }
   }
   for(r2=0; r2<=1; r2++)
   {
       for(c2=0; c2<=1; c2++)
       {
           printf("%d ", b[r2][c2]);
       }
       printf("\n");
   }
   for(r1=0; r2)


    return 0;
}
