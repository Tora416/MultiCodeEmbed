#include <stdio.h>
#include <math.h>

int idk(double x1, double y1);

int main(void) {

  double x, y;
    int risultato;

  printf("Inserisci il primo numero: ");
  scanf("%lf", &x);

    printf("Inserisci il secondo numero: ");
  scanf("%lf", &y);


  risultato = idk(x, y);
  printf( "Risultato: %d\n", risultato ); 

  return 0;
}

int idk(double x, double y){

    double randomNumber = pow(1/10, 9);

        if ((x - y) <= (randomNumber))
            return 1;
        else return 0; 
        
}

