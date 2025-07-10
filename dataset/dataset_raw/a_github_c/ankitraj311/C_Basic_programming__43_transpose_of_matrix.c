#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2, flag = 0;
  printf("Enter Value of r1, c1, r2, c2\n");
  scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
  int m1[r1][c1], m2[r2][c2], sum = 0, mul[r1][c2];





  printf("Enter value of Matrix1\n");
  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      scanf("%d",&m1[i][j]);
    }
  }

  printf("Value Befor Transpose\n"); 
  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      printf("%d",m1[i][j]);
    }
    printf("\n");
  }

  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      m2[j][i] = m1[i][j];
    }
    printf("\n");
  }

  printf("Value after Transpose\n"); 
  for(i=0; i<c1; i++)
  {
    for(j=0; j<r1; j++)
    {
      printf("%d ",m2[i][j]);
    }
    printf("\n");
  }
}
