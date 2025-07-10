#include <stdio.h>
#define MAX 20

void string_reverse(char *origin, char *rev) {
  int f = 0, cnt = 0, j = 0;
  while ( *(origin + f) != '\0' ) {
    cnt++;
    f++;
  }
  for (int i = cnt - 1; i >= 0; i--)
  {
    *(rev + j) = *(origin + i);
    j++;
  }
  *(rev + j) = '\0';
}

int pal_chk(char *norm, char *rev) {
  while (*(norm) != '\0') {
    if (*norm == *rev) {
      norm++;
      rev++;
    }
    else
      return 0;
  }
  return 1;
}

int main() {
  char origin[MAX], reverse[MAX];

  printf("Enter a string (20): ");
  scanf("%[^\n]%*c", origin);

  string_reverse(origin, reverse);

  if (pal_chk(origin, reverse))
    printf("The string ' %s ' is a Palindrome\n", origin);
  else
    printf("The string ' %s ' is not a Palindrome\n", origin);

  return 0;
}
