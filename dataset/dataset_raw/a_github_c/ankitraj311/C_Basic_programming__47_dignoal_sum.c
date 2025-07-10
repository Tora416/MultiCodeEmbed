#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2,row_sum = 0, col_sum = 0, diagnoal1 = 0, diagnoal2 = 0;
  printf("Enter Value of r1, c1\n");
  scanf("%d%d",&r1,&c1);
  int m1[r1][c1], sum = 0;



  printf("Enter value of Matrix1\n");
  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      scanf("%d",&m1[i][j]);
    }
  }

  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      printf("%d ",m1[i][j]);
    }
    printf("\n");
  }

  for(i=0; i<r1; i++)
  {
    diagnoal1 = diagnoal1 + m1[i][i];
    diagnoal2 = diagnoal2 + m1[i][c1];
    c1--;
  }
  printf("\n\nValue of Diagnoal1 is %d & Diagnoal2 is %d",diagnoal1,diagnoal2);

 }

