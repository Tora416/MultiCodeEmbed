#include <stdio.h>
#define MAX 3

int main()
{
  int mat1[MAX][MAX], mat2[MAX][MAX], addition[MAX][MAX];

  printf("Give values in the matrix1 row-wise.\n");

  for (int i = 0; i < MAX; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      scanf("%d",&mat1[i][j]);
    }
  }

  printf("Give values in the matrix2 row-wise.\n");

  for (int ii = 0; ii < MAX; ii++)
  {
    for (int jj = 0; jj < MAX; jj++)
    {
      scanf("%d", &mat2[ii][jj]);
    }
  }

  printf("\nThe matrix1 is\n");
  for (int ii = 0; ii < MAX; ii++)
  {
    for (int jj = 0; jj < MAX; jj++)
    {
      printf("%d\t",mat1[ii][jj]);
    }
    printf("\n");
  }

  printf("\nThe matrix2 is\n");
  for (int ii = 0; ii < MAX; ii++)
  {
    for (int jj = 0; jj < MAX; jj++)
    {
      printf("%d\t",mat2[ii][jj]);
    }
    printf("\n");
  }


  printf("\nThe matrix1 + matrix2 is\n");
  for (int ii = 0; ii < MAX; ii++)
  {
    for (int jj = 0; jj < MAX; jj++)
    {
      printf("%d\t",mat1[ii][jj] + mat2[ii][jj]);
    }
    printf("\n");
  }

  return 0;
}
