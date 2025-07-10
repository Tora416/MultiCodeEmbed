#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2, flag = 0;
  printf("Enter Value of r1, c1\n");
  scanf("%d%d",&r1,&c1);
  int m1[r1][c1], sum = 0;




  if(r1 == c1)
  {
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
        if( i == j && m1[i][j] == 1)
    {
          flag++;
    }
    if( i != j && m1[i][j] == 0)
    {
      flag++;
    }
      }
    }  
 
  }
  else
  {
    printf("Identical Matrix Should be a Square Matrix\n");
  }
  if(flag == (r1*c1))
  {
    printf("Matrix is Identical\n");
  }
  else
  {
    printf("Matrix is Not Identical");
  }
  printf("\nValue of flag is %d",flag);
}

