#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2,row_sum = 0, col_sum = 0, diagnoal1 = 0, diagnoal2 = 0;
  float expo= 0.0;
  printf("Enter Value of r1, c1 and Exponential\n");
  scanf("%d%d%f",&r1,&c1,&expo);
  int m1[r1][c1], m2[r1][c1], mul[r1][c1], sum = 0;



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
    for(j=0; j<c1; j++)
    {
      m2[j][i] = m1[i][j];
    }
  }
  printf("\n");
  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      printf("%d ",m2[i][j]);
    }
    printf("\n");
  }
  
  for(i=0; i<r1; i++)
  {
    for(j=0; j<r1; j++)
    {
      for(k=0; k<r1; k++)
      {
        sum = sum + m1[i][k]*m2[k][j];
      }
      mul[i][j] = sum;
      sum = 0;
    }
  }
  printf("\n");
  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      printf("%d ",mul[i][j]);
    }
    printf("\n");
  }

}

