#include <stdio.h>



int main(){
  int n, aux;
  int cont = 0;
  
  scanf("%d", &n);
  
  if(n < 1 || n > 1000000)
    return 0;


  while(n>0){
    
    if(n - 5  >= 0)
      aux = 5;

    else if(n - 4 >= 0)
      aux = 4;

    else if(n - 3 >= 0)
      aux = 3;

    else if(n - 2 >= 0)
      aux = 2;

    else if(n - 1 >= 0)
      aux = 1;
    

    n -= aux;
    cont++;
  }

  printf("%d\n", cont);
  
}
