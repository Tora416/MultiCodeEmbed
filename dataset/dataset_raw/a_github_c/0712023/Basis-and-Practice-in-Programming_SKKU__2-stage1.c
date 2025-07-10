#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char input[512] = "3 * x ^ 1 + 5 * x ^ 1 + 12 * x ^ 13 + 1 * x ^ 0 + 4 * x ^ 2 + 7 * x ^ 2";
  strcat(input," +");
  int coeff[40]= {};
  int *pc;
  pc = coeff;
  int indice[40]={};
  int *pi;
  pi = indice;
  int cnt_c = 0;
  int *pnt_c;
  pnt_c = &cnt_c;
  int cnt_i = 0;
  int *pnt_i;
  pnt_i = &cnt_i;
  int plus =0;
  int *pplus;
  pplus = &plus;
  int cnt = 0;
    int *pnt = &cnt;
  for(int i = 0; i<512; i++){
    if(input[i] == '+'){
      *pplus+=1;
    }
    if(input[i+1]==' ' && input[i+2] == '*'){
      if(input[i-1]>47 && input[i-1] < 58){
        *(pc+*pnt_c) = (input[i-1]-48)*10+input[i]-48;
      } else{
        *(pc+*pnt_c) = input[i]-48;
      }
            *pnt_c+=1;
    }

    if(input[i+1]==' ' && input[i+2] == '+'){
      if(input[i-1]>47 && input[i-1] < 58){
        *(pi+*pnt_i) = (input[i-1]-48)*10+input[i]-48;
      } else {
        *(pi+*pnt_i) = input[i]-48;
      }
      *pnt_i+=1;
    }
  }
  for(int i = 0; i<*pplus; i++){
    for(int j = 0;j<*pplus-1;j++){
      if(indice[j]<indice[j+1]){
        char tmp1;
        tmp1 = indice[j];
        indice[j] = indice[j+1];
        indice[j+1] = tmp1;
        char tmp2;
        tmp2 = coeff[j];
        coeff[j] = coeff[j+1];
        coeff[j+1] = tmp2;
      }
    }
  }

  for(int k = 0; k<*pplus;k++){
        for(int i = 0; i< *pplus-1; i++){
            if(indice[i] == indice[i+1]){
        coeff[i] += coeff[i+1];
                *pnt+=1;
        for(int j = i+1; j< *pplus-1 ; j++){
                    char tmp;
                    tmp = coeff[j];
                    coeff[j] = coeff[j+1];
                    coeff[j+1] = tmp;
                }
        coeff[*pplus-1] = 0;
                for(int j = i+1; j< *pplus-1 ; j++){
                    char tmp;
                    tmp = indice[j];
                    indice[j] = indice[j+1];
                    indice[j+1] = tmp;
                }
        indice[*pplus-1] = 0;
            }
        }
    }
  *pnt =0 ;
  for(int i = 0; i<40; i++){
    if(coeff[i]==0){
      break;
    }
    *pnt+=1;
  }
  char result[512] = {};
  for(int i =0; i<*pnt-1;i++){
    char tmp[100] = {};
    sprintf(tmp,"%d * x ^ %d + ", coeff[i], indice[i]);
    strcat(result,tmp);
  }
  char tmp[50] ={};
  sprintf(tmp,"%d * x ^ %d", coeff[*pnt-1], indice[*pnt-1]);
  strcat(result, tmp);
  printf("%s\n", result);
}
