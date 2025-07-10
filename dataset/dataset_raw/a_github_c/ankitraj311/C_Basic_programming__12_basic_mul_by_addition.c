#include<stdio.h>
#include<math.h>
int main()
{

  int a,b,i,j,flag=-1,small,large,mul=0,sum;
  printf("Enter the value of the a and b");
  scanf("%d%d",&a,&b);
  





  if( (a<0 && b<0) || (a>0 && b>0) )
  {
    flag = 0;
  }
  else if((a>0 && b<0) || (a<0 && b>0))
  {
    flag = 1;
  }
 

  if(a<0)
  { 
    a = -1 * a;
  }
  else if(b < 0)
  {
    b = -1 * b;
  }

  printf("a is %d, b is %d",a,b);
  if(a>b)
  {
    large = a;
    small = b;
  }
  else
  {
    large = b;
    small = a;
  }

  for(i=1;i<=small;i++)
  {
    mul = mul + large;
  }

  if(flag == 0)
  {
    printf("multiplication is %d",mul);
  }
  else if(flag == 1)
  {
    printf("multiplication is -%d",mul);
  }

}
