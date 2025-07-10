#include <stdio.h>
#define MAX 5

void insertion(int *,int *, int, int);

int main() {
  int nums[MAX] = {5, 4, 7, 9, 2}, target[MAX + 1], pos, input; 

  printf("The array is\n");

  for (int i = 0; i < MAX; i++)
    printf("%d\t",  *(nums + i));

  printf("\nEnter a number and position:");
  scanf("%d %d", &input, &pos );

  insertion(nums, target, input, pos);

  printf("The array is\n");

  for (int i = 0; i < MAX + 1; i++)
    printf("%d\t",  *(target + i));

  return 0;
}

void insertion(int *source, int *target, int number, int position) {
  int j = 0;

  for (j = 0; j < MAX + 1; j++) { 
    if (j < position - 1){
      *(target + j) = *(source + j);
      continue;
    }
    else if (j == position - 1) 
      *(target + j) = number;
    else { 
      *(target + j) = *(source + j - 1);
    }
  }
}
