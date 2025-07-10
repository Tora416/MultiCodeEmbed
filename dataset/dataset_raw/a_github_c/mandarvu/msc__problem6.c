#include <stdio.h>
#define MAX 5

int search(int *, int);

int main() {
  int numbers[MAX], val, pos;

  printf("Enter %d numbers: ", MAX);
  for (int i = 0; i < MAX; i++)
    scanf("%d",numbers + i);

  printf("\nArray 1:\n");
  for (int i = 0; i < MAX; i++)
    printf("%d\t",  *(numbers + i));

  printf("Enter the value to be searched\n" );
  scanf("%d",&val);

  pos = search(numbers, val);

  if (pos > 0)
    printf("%d is at position %d\n",val, pos);
  else
    printf("%d not found\n",val);
}

int search(int *array, int num) {
  for (int j = 0; j < MAX; j++)
  {
    if (*(array + j) == num)
    {
      
      return (j + 1);
    }
  }
  return 0;
}
