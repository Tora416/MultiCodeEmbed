#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2;
  printf("Enter Value of r1, c1, r2, c2\n");
  scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
  int m1[r1][c1], m2[r2][c2], sum = 0, mul[r1][c2];





  if( c1 == r2)
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
        printf("%d ",m1[i][j]);
      }
      printf("\n");
    }
  
    printf("\n") ;
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
      for(j=0; j<c2; j++)
      {
        for(k=0; k<r2; k++)
        {
          sum = sum + m1[i][k] * m2[k][j];  
        }  
        mul[i][j] = sum;
        sum = 0;
      }
      printf("\n");
    } 
    printf("Mutiplication of Matrix is -: \n");
    for(i=0; i<r1; i++)
    {
      for(j=0; j<c1; j++)
      {
       printf("%d ",mul[i][j]);
      }
      printf("\n");
    }
  }
  else
  {
    printf("Multiplication is Not Possible");
  } 

}
