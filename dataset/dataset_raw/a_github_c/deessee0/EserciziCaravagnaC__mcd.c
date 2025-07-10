#include <stdio.h>

int mcd(int a, int b)
{
    int r = a % b;

    if(r == 0){

        return b;

    } else { 
        
        return mcd(b, r);
    
    }
}

int main() {
  
    int a, b;
  int risultato;

  printf("Primo numero: ");
  scanf("%d", &a);

  printf("Secondo numero: ");
  scanf("%d", &b);
  
    risultato = mcd(a, b);
  printf( "Risultato: %d\n", risultato ); 

    return 0;
}
