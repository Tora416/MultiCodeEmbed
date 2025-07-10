#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2,row_sum = 0, col_sum = 0;
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
    for(j=0; j<c1; j++)
    {
      row_sum = row_sum + m1[i][j];
    }
    printf("Sum of Row[%d] is %d\n",i,row_sum);
    row_sum = 0;
  }

  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      col_sum = col_sum + m1[j][i];
    }
    printf("Sum of col[%d] is %d\n",i,col_sum);
    col_sum = 0;
  }
 }

