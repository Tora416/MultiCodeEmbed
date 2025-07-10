
 
#include<stdio.h>
#include<math.h>
void main()
 {
  float r1,r2;
  int a,b,c,d;
  printf("Enter value of a,b and c:");
  scanf("%d%d%d",&a,&b,&c);
  d=b*b-4*a*c;
  if(d>0)
   {
    printf("root are real");
    r1=(-b+sqrt(d))/2*a;
    r2=(-b-sqrt(d))/2*a;
    printf("root are %f and %f\n",r1,r2);
    }
  else if(d==0)
   {
    printf("root are equal");
    r1=-b/2*a;
    r2=-b/2*a;
    printf("root are %f and %f\n",r1,r2);
    }
  else
   {
    printf("root are imaginary!");
    printf("root are not real !!");
    }
  }

