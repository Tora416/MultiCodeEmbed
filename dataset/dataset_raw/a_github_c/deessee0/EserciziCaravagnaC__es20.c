#include <stdio.h>
int max_finder(int a, int b, int c);

int main(void) {
  int a, b, c;
  int risultato;

  printf("Primo numero: ");
  scanf("%d", &a);

  printf("Secondo numero: ");
  scanf("%d", &b);

  printf("Terzo numero: ");
  scanf("%d", &c);

  risultato = max_finder(a,b,c);
  printf( "Risultato: %d\n", risultato ); 

  return 0;
}

int max_finder(int a, int b, int c){

  if(a > b){
        if( a > c){
            return a;
        } else return c;
    } else if (b > c){
        return b;

    } else return c;

}  