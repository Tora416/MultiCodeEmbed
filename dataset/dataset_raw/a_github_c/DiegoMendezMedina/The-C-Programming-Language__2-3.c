#include <stdio.h>



int htoi(char s[]);
int hexa_to_int(char s);
int get_decimal(int hexa[], int cont);
int eleva(int base, int exp);

void main(){
  char s[100];
  int res;
  
  scanf("%s", s);
  res = htoi(s);
  if(res >= 0)
    printf("%d\n",res);
  else
    printf("Invalid Input\n");
}


int htoi(char s[]){
  int cont = 0;

  if(s[0] != '0' || (s[1] != 'x' && s[1] != 'X'))
     return -1;
    
  for(int i = 2; (s[i]>= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')
    || (s[i] >= 'A' && s[i] <= 'F'); i++, cont++)
    ;
  
  int hexa[cont];
  
  for(int i = 2; (s[i]>= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')
    || (s[i] >= 'A' && s[i] <= 'F'); i++)
    hexa[i-2] = hexa_to_int(s[i]);
  
  return get_decimal(hexa, cont);
}


int hexa_to_int(char s){
  if(s == 'a' || s == 'A')
    return 10;
  if(s == 'b' || s == 'B')
    return 11;
  if(s == 'c' || s == 'C')
    return 12;
  if(s == 'd' || s == 'D')
    return 13;
  if(s == 'e' || s == 'E')
    return 14;
  if(s == 'f' || s == 'F')
    return 15;
  return s - '0';
}


int get_decimal(int hexa[], int cont){
  int res = 0;
  int exp = cont-1;
  
  for(int i = 0; i < cont; i++){
    res += hexa[i] * eleva(16, exp--);
  }
  return res;
}


int eleva(int base, int exp){
  if(exp == 0)
    return 1;
  else
    return base * eleva(base, exp -1);
}
