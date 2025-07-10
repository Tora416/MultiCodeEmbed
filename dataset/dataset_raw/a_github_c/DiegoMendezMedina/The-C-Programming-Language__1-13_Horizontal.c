#include <stdio.h>



#define IN 1
#define OUT 0
main(){
  int c, state, aux, cont;
  int wlong[10];
  state = OUT;
  cont = aux = 0;
  for(int i = 0; i < 10; i++)
    wlong[i] = 0;
  
  while((c = getchar()) != EOF){
    if(c == 11 || c == 32 || c == 10){
      state = OUT;
      if(cont < 10){
    aux = cont - 1;
    wlong[aux]++;
      }
      else
    wlong[9]++;
    }
    else {
      if(state == OUT){
      state = IN;
      cont = 0;
      }
      cont++;
    }
  }
  
  for(int i = 0; i < 10; i++){
    int r = i+1;
    if(i < 9)
      printf(" %2d :", r);
    else
      printf(" +%d :", i);
    for(int l = 0; l < wlong[i]; l++)
    printf( "-");    
    printf("\n");
  }
}
