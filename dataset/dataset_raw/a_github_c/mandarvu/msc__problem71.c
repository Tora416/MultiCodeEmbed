#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int prime(int n) {
  if (n % 2 == 0)
    return 1;
  else
  {
    for (int ii = 1; ii <= sqrt(n); ii++)
    {
      if (n % ii == 0)
       return 1;
    }
  return 0;
  }
}

int Armstrong(int num) {
    int sum = 0, target = 0, tmp;
    tmp = num;
    while (num > 0)
    {
        sum += pow(num%10, 3);
        num /= 10;
    }
    
    return  (tmp == sum ? 1 : 0);
}

int perf_check(int n) {
  int summ = 0;
  for (int ii = 1; ii <= sqrt(n) + 1; ii++)
  {
    if (n % ii == 0)
      summ += ii;
  }
  return (summ == n ? 1 : 0);
}

int main() {
  int v1, num;
  printf("1...Prime Check\n");
  printf("2...Armstrong Check\n");
  printf("3...Perfect number Check\n");
  scanf("%d",&v1);
  switch (v1) {
    case 1:
      printf("Enter a number.\n");
      scanf("%d",&num);
      printf("%d is a %s\n",num, prime(num) ? "not prime" : "prime");
      break;
    case 2:
      printf("Enter a number.\n");
      scanf("%d",&num);
      printf("%d is a %s\n",num, Armstrong(num) ? "Armstrong number." : "not Armstrong number.");
      break;
    case 3:
      printf("Enter a number.\n");
      scanf("%d",&num);
      printf("%d is a %s\n",num, perf_check(num) ? "perfect" : "not perfect");
      break;
    default:
      printf("ERROR (invalid input)\n");
      exit(1);
  }
  return 0;
}







