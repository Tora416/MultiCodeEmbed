#include<stdio.h>
int main()
{
  int salary;
  float bonus;
  char gender;







  printf("Enter the Gender");
  scanf("%c",&gender);
  printf("Enter Salary");
  scanf("%d",&salary);

  if(gender == 'M' || gender == 'm')
  {
    if(salary > 10000)
    {
      bonus = (salary * .05);
    }
    else
    {
      bonus = (salary * .07);
    }
  }
  if(gender == 'F' || gender == 'f')
  {
    if(salary > 10000)
    {

      bonus = (float)(salary * .10);
    }
    else
    {
      bonus = (float)(salary * .12);
    }
  }
  salary = salary + bonus;
  printf("Salary is %d", salary);
}
