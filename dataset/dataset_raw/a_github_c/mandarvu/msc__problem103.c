#include <stdio.h>

void main() {
  int mat1[2][2], mat2[2][2], mat[2][2];

  printf("Enter values in matrix 1(2*2) row-wise (a11, a12, a21, a22): ");
  for (int i = 0; i < 2; i++)
    scanf("%d %d",*(mat1 + i) + 0, *(mat1 + i) + 1 );

  printf("Enter values in matrix 2(2*2) row-wise (a11, a12, a21, a22): ");
  for (int i = 0; i < 2; i++)
    scanf("%d %d",*(mat2 + i) + 0, *(mat2 + i) + 1 );

  printf("\nMatrix 1(2*2)\n");
  for (int i = 0; i < 2; i++) {
    printf("%d %d",*(*(mat1 + i) + 0), *(*(mat1 + i) + 1));
    printf("\n");
  }

  printf("\nMatrix 2(2*2)\n");
  for (int i = 0; i < 2; i++) {
    printf("%d %d",*(*(mat2 + i) + 0), *(*(mat2 + i) + 1));
    printf("\n");
  }

  printf("\nMatrix1 + Matrix2 = \n");
  for (int i = 0; i < 2; i++) {
    printf("%d %d",mat1[i][0] + mat2[i][0], mat1[i][1] + mat2[i][1]);
    printf("\n");
  }
}
