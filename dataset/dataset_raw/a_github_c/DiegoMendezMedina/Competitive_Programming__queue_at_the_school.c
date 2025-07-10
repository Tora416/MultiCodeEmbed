#include <stdio.h>



void change(char s[], int i, int j);

int main(){
  int n, t;
  
  scanf("%d", &n);
  scanf("%d", &t);

  char s[n];
  
  if(n < 1 || t < 1
     || n > 50 || t > 50)
    return 0;
  
  scanf("%s", s);
  for(int j = 1; j <=t; j++)
    for(int i = 0; i < n; i++)
      if(i+1 < n)
    if(s[i] == 'B' && s[i+1] == 'G'){
      change(s, i, i+1);
      i = i+1;
    }
  printf("%s\n", s);
}

void change(char s[], int i, int j){
  char aux = s[i];
  s[i] = s[j];
  s[j] = aux;
}
