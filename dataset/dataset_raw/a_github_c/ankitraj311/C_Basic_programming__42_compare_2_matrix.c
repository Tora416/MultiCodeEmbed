#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2, flag = 0;
  printf("Enter Value of r1, c1, r2, c2\n");
  scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
  int m1[r1][c1], m2[r2][c2], sum = 0, mul[r1][c2];





  if( c1==c2 && r1==r2)
  {
    printf("Enter value of Matrix1\n");
    for(i=0; i<r1; i++)
    {
      for(j=0; j<c1; j++)
      {
        scanf("%d",&m1[i][j]);
      }
    }
  
    printf("Enter value of Matrix2\n");
    for(i=0; i<r2; i++)
    {
      for(j=0; j<c2; j++)
      {
        scanf("%d",&m2[i][j]);
      }
    }
  
    for(i=0; i<r1; i++)
    {
      for(j=0; j<c1; j++)
      {
        if(m1[i][j] == m2[i][j])
    {
      flag = 1;
    }
    else
        {
          flag = 2;         
      break;
      }
    }
  }
 }
 else
 {
   printf("Comparison is Not Possible");
 }

    if(flag == 1)
    {
      printf("Matrix Matched");
    }  
    else
    {
      printf("Matrix didn't Matched");
    }
}
