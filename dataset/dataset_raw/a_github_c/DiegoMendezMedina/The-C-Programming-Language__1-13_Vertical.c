#include <stdio.h>


#define IN 1
#define OUT 0
main(){
  int c, state, aux, cont;
  int wlong[10];
  state = OUT;
  cont  = aux = 0;
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


  aux = 0;
  int e = 9;
  for(int i = 0; i < 5; i++){
    if(wlong[i] > wlong[e] && wlong[i] > aux)
      aux = wlong[i];
    else if(wlong[e] > aux)
      aux = wlong[e];
    e--;
  }
  
  while(aux >= 1){
    for(int i = 0; i < 10; i++){
      if(wlong[i] >= aux)
    printf("  | ");
      else
    printf("    ");
    }
    printf("\n");
    aux--;
  }
  
  cont = 0;
  while(cont < 10){
    int r = cont+1;
    if(cont < 9)
      printf(" %2d ", r);
    else
      printf(" +%d \n", cont);
    cont++;
  }
  
}
