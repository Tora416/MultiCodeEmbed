#include <stdio.h>
int main() {
  int power(int x, int n){
    if (n ==1 ){
      return x;
    } else if(n == 0){
      return 1;
    }
    return (x*power(x,n-1));
  }
  int len(int number){
    int cnt = 0;
    while (number>0){
      cnt++;
      number /= 10;
    }
    return cnt;
  }

  int a = 0;
  int i = 0;
  int func(int number){
    if (len(number) >0){
      a+=number%10*power(10, i);
      number = number/100;
      i++;
      func(number);
    } else {
      return 0;
    }
  }

  int number = 0;
  scanf("%d", &number);
  func(number);
  printf("%d", a);
    return 0;
}
