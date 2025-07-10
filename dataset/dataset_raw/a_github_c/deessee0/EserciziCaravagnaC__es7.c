

#include<stdio.h>
#include<stdlib.h>

struct numero_complesso {
  float reale; 
  float immaginaria; 
};

typedef struct numero_complesso NumeroComplesso;


NumeroComplesso somma(NumeroComplesso x, NumeroComplesso y){
  
  NumeroComplesso s;
  
  s.reale = x.reale + y.reale;
  
  s.immaginaria = x.immaginaria + y.immaginaria;
  
  return s;
}

 
NumeroComplesso prodotto(NumeroComplesso x, NumeroComplesso y){
  
  NumeroComplesso p;
  
  p.reale = x.reale*y.reale - x.immaginaria*y.immaginaria;
  
  p.immaginaria = x.reale*y.immaginaria + x.immaginaria*y.reale;
  
  return p;
}


NumeroComplesso somma_array(NumeroComplesso z[],int dim){
  
  NumeroComplesso s;
  
  s.reale = z[0].reale;
  s.immaginaria = z[0].immaginaria;

  for(int i=1; i<dim; i++){
    
    s = somma(s, z[i]);
  }

  
  return s;
}


void stampa_complesso(NumeroComplesso x){
  
  printf("%.2f + %.2f i\n", x.reale, x.immaginaria);
}

int main() {
  
  NumeroComplesso x;
  printf("Inserire parte reale e immaginaria di x: ");
  scanf("%f %f", &x.reale, &x.immaginaria);
  NumeroComplesso y;
  printf("Inserire parte reale e immaginaria di y: ");
  scanf("%f %f", &y.reale, &y.immaginaria);

  
  printf("\nx = ");
  stampa_complesso(x);

  
  printf("\ny = ");
  stampa_complesso(y);

  
  NumeroComplesso s = somma(x, y);

  
  printf("\nx + y = ");
  stampa_complesso(s);

  
  NumeroComplesso p = prodotto(x, y);

  
  printf("\nx*y = ");
  stampa_complesso(p);

  
  
  int n = 5; 
  NumeroComplesso z[n];
  
  for(int i=0; i<n; i++){
    z[i].reale = i;
    z[i].immaginaria = i+3;
  }

 NumeroComplesso s1 = somma_array(z, n); 
 
 printf("\nLa somma di tutti gli elementi nell'array è:\ns1 = ");
 stampa_complesso(s1);


  return(0);
}
