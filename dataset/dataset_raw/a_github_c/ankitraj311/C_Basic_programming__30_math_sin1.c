#include<stdio.h>
#include<math.h>

int factorial(int);
int main()
{
  float i,j,degree,radian,result, sine = 0;
  int count = 0, k = 1, accurate;
  printf("Enter the degree to find it by sin value by it");
  scanf("%f",&degree);



  radian = (float)degree * (3.1415/180);
  printf("Minimum is 3.Enter the value of the accurate, upto which you want to find the result");
  scanf("%d",&accurate);
  do
  {
    if(count % 2 == 0)
    {
      sine = (float)sine + (pow(radian,k)/factorial(k));
    }
    if(count % 2 == 1)
    {
      sine = (float)sine - (pow(radian,k)/factorial(k));
    }
    count++;
    k = k + 2;
  }
  while(count <= accurate);
  printf("\nValue of sine %f", sine);
  printf("\nValue of sine %f", sin(radian));

}

int factorial(int val)
{
  int  fact= 1, i;
  for(i=1; i<=val; i++)
  {
    fact = fact * i;
  }
  return fact;
}

