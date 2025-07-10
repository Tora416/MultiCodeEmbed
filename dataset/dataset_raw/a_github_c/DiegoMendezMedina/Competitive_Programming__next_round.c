#include <stdio.h>



int main(){
  int n, k, aux, aux2;
  int cont = 0;
  
  scanf("%d", &n);
  scanf("%d", &k);
  
  if(k < 1 || k > 50 ||n < 1
     || n > 50 || k > n)
    return 0;
 
  for(int i = 1; i <= n; i++){

    if(i <= k){
      scanf("%d", &aux);
      if(aux >0)
    cont++;
      else
    break;
    }
    
    else if(i>k){
      scanf("%d", &aux2);
      if(aux2 == aux)
    cont++;
    }
    
  }
  
  printf("%d\n", cont);
}
