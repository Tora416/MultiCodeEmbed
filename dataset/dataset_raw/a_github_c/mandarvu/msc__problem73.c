#include <stdio.h>
#define MAX 5

void reverse_array(int *origin, int *rev) {
  int j = 0;
  for (int i = MAX - 1; i >= 0; i--)
    {
        *(rev + j) = *(origin + i);
        j++;
    }
}

int main() {
  int source[MAX], target[MAX];

  printf("Enter %d numbers: ", MAX);

  for (int i = 0; i < MAX; i++)
    scanf("%d", source + i);

  printf("\nThe Array is\n");
  for (int i = 0; i < MAX; i++)
    printf("%d\t",  *(source + i));

  reverse_array(source, target);

  printf("\nThe reversed Array is\n");
  for (int i = 0; i < MAX; i++)
    printf("%d\t",  *(target + i));
  printf("\n");
  return 0;
}
