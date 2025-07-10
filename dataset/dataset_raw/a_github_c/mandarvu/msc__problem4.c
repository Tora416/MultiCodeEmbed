#include <stdio.h>
#define MAX 5

void deletion(int *,int *, int);

int main() {
  int nums[MAX] = {5, 4, 7, 9, 2}, target[MAX - 1], pos, input; 

  printf("The array is\n");
  
  for (int i = 0; i < MAX; i++)
    printf("%d\t",  *(nums + i));

  printf("\nEnter the position:");
  scanf("%d", &pos );

  deletion(nums, target, pos);

  
  

  printf("The array is\n");

  for (int i = 0; i < MAX - 1; i++)
    printf("%d\t",  *(target + i));

  return 0;
}

void deletion(int *source, int *target, int position) {
  int j = 0;

  for (j = 0; j < MAX + 1; j++) { 
    if (j < position - 1){
      *(target + j) = *(source + j);
      continue;
    }
    else { 
      *(target + j) = *(source + j + 1);
    }
  }
}
