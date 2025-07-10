#include <stdio.h>
#define MAX 40

 
void merge_string(char *source1, char *source2, char *target) {
  while (*source1 != '\0') {
    *target = *source1;
    source1++;
    target++;
  }

  while (*source2 != '\0') {
    *target = *source2;
    source2++;
    target++;
  }

  *target = '\0';
}

int main() { 
  char source1[MAX], source2[MAX], target[MAX];
  printf("Enter a string (Max %d characters)\n", MAX);
  scanf("%[^\n]%*c", source1); 
  printf("Enter another string (Max %d characters)\n", MAX);
  scanf("%[^\n]%*c", source2); 
  merge_string(source1, source2, target);
  printf("%s\n", target);
  return 0;
}
