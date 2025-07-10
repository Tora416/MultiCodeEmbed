#include<stdio.h>
int main()
{
  int i,j,k,r1,c1,r2,c2,flag = 0;
  printf("Enter Value of r1, c1, r2, c2\n");
  scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
  int m1[r1][c1], m2[r2][c2], add_array[r1][c1], mul[r1][c2];





  printf("Enter value of Matrix1\n");
  for(i=0; i<r1; i++)
  {
    for(j=0; j<c1; j++)
    {
      scanf("%d",&m1[i][j]);
    }
  }
 
  do
  {
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
        add_array[i][j] = m2[i][j] - m1[i][j];
      }
    }

    for(i=0; i<r2; i++)
    {
      for(j=0; j<c2; j++)
      {
        printf("%.2d ",add_array[i][j]);
      }
      printf("\n");
    }

    for(i=0; i<r2; i++)
    {
      for(j=0; j<c2; j++)
      {
        m1[i][j] = add_array[i][j];
    add_array[i][j] = 0;
      }
    }
    printf("Enter 1 To Add more Matrix\n");
    scanf("%d",&flag);
  }while(flag);

}
