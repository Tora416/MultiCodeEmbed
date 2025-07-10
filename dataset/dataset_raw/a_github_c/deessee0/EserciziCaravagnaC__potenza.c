#include <stdio.h>
int pot_ricorsivo(int base, int esponente);

int main(void) {
  int a, b;
  int risultato;

  printf("Base: ");
  scanf("%d", &a);

  printf("Esponente: ");
  scanf("%d", &b);

  if (b > 0) {
    risultato = pot_ricorsivo(a,b);
    printf( "Risultato: %d\n", risultato ); 
  } else {
    printf("Inserisci una potenza maggiore di 0");
  }
 
  return 0;
}

int pot_ricorsivo(int base, int esponente)
{

    if (esponente == 1)
          return base;
 
    return base*pot_ricorsivo(base, esponente-1);
}