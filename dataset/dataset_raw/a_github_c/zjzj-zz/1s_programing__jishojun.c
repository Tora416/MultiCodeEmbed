#include <stdio.h>

int strcmp(char *, char *);

int main(){
 char *str[] = {"aoki", "aoki"};
 int x;

 printf("%sと%sの辞書順を調べると\n", str[0], str[1]);

 x = strcmp(str[0], str[1]);

 printf("%d\n", x);

 return 0;
}

int strcmp(char *str1, char *str2){
 int r, i, a, b, c;
 char *ptr;

 for(ptr = str1; *ptr != '\0'; ptr++){
  a +=1;
 }
 for(ptr = str2; *ptr != '\0'; ptr++){
  b +=1;
 }
 if(a>b){
  c=a;
 }else{
  c=b;
 }

 for(i=0; i<=c; i++){
  if(str1[i] != str2[i]){
   if(str1[i] < str2[i]){
    r = -1;
    break;
   }
   else{
    r = 1;
    break;
   }
  }
 r = 0;
 }
 return r;
}
