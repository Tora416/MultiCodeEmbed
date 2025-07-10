#include <stdio.h>
int potenza(int base, int esponente);

int main(void) {
  int a, b;
  int risultato;

  printf("Base: ");
  scanf("%d", &a);

  printf("Esponente: ");
  scanf("%d", &b);

  if (b > 0) {
    risultato = potenza(a,b);
    printf( "Risultato: %d\n", risultato ); 
  } else {
    printf("Inserisci una potenza maggiore di 0");
  }
 
  return 0;
}

int potenza(int base, int esponente){
  int risultato = 1;

  for(int i = 0; i < esponente; i++){
    risultato = risultato * base;
  }

    return (risultato);
}  