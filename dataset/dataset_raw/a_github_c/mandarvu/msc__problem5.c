#include <stdio.h>
#define SIZE 5
void merge_array(int *, int *, int *);

int main() {
  int unsorted1[SIZE], unsorted2[SIZE], final[2*SIZE];

  printf("Enter %d numbers in 1st array: ", SIZE);
  for (int i = 0; i < SIZE; i++)
    scanf("%d",unsorted1 + i);

  printf("Enter %d numbers in 2nd array: ", SIZE);
  for (int i = 0; i < SIZE; i++)
    scanf("%d",unsorted2 + i);

  printf("\nArray 1:\n");
  for (int i = 0; i < SIZE; i++)
    printf("%d\t",  *(unsorted1 + i));

  printf("\nArray 2:\n");
  for (int i = 0; i < SIZE; i++)
    printf("%d\t",  *(unsorted2 + i));

  merge_array(unsorted1, unsorted2, final);

  printf("\nMerged array\n");

  for (int j = 0; j < (2 * SIZE); j++)
    printf("%d  ",*(final + j));
}

void merge_array(int *source1, int *source2, int *target) {
  int j = 0;

  for (j; j < (2*SIZE); j++) {
    if (j < SIZE) {
      *(target + j) = *(source1 + j);
    }
    else {
      *(target + j) = *(source2 + j - SIZE);
    }
  }
}
