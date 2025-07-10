

#include<stdio.h>
#include<stdlib.h>


int somma(int a[], int dim){
  int s = 0; 
  for(int i=0; i<dim; i++){
    s+=a[i];
  }
  return s;
}


int check(int a[], int dim_a, int b[], int dim_b){
  int i = 0; 
  int trovato = 0; 
  
  int somma_b = somma(b, dim_b);
  
  
  while(i<dim_a && !trovato){
    
    if(a[i]==somma_b){
      
      trovato = 1;
    }
    
    i++;
  } 
  return trovato;
}

int main(){
  
  int dim_a, dim_b;
  printf("Inserire dimensione a: ");
  scanf("%d", &dim_a);
  printf("Inserire dimansione b: ");
  scanf("%d", &dim_b);

  
  int *a;
  a = malloc(sizeof(int)*dim_a);
  int *b;
  b = malloc(sizeof(int)*dim_b);

  
  for(int i=0; i<dim_a; i++){
    printf("a[%d] = ", i);
    scanf("%d", &a[i]);
  }
  printf("\n");

  
  for(int i=0; i<dim_b; i++){
    printf("b[%d] = ", i);
    scanf("%d", &b[i]);
  }
  printf("\n");

  int verifica = check(a, dim_a, b, dim_b);

  if(verifica==1){
    printf("In a esiste un elemento uguale alla somma degli elementi di b\n");
  }

  if(verifica==0){
    printf("In a NON esiste un elemento uguale alla somma degli elementi di b\n");
  }

  free(a);
  free(b);

  return(0);

}