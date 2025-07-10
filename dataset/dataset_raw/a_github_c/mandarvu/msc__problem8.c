#include <stdio.h>

int main()
{
  int rows, cols;
  int x, y;
  printf("Enter matrix dimension(row * col): ");
  scanf("%d %d",&rows, &cols);

  int mm[rows][cols];

  printf("Give values in the %d * %d matrix row-wise.\n", rows, cols);

  for (int ii = 0; ii < rows; ii++)
  {
    for (int jj = 0; jj < cols; jj++)
    {
      scanf("%d",&mm[ii][jj]);
    }
  }

  printf("\nThe array is\n");
  for (int ii = 0; ii < rows; ii++)
  {
    for (int jj = 0; jj < cols; jj++)
    {
      printf("%d\t",mm[ii][jj]);
    }
    printf("\n");
  }


  printf("Enter (row * col) of element needed: ");
  scanf("%d %d",&x, &y);
  if (x > rows || y > cols)
    printf("Array index out of range\n");
  else
    printf("Value at %d * %d in the given array is: %d\n",x, y, mm[x - 1][y - 1]);
    
  return 0;
}
