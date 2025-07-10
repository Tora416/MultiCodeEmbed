

#include<stdio.h>
#include<stdlib.h>



void rimuovi(int a[], int *dim){
  
  for(int i=0; i<*dim; i++){
    
    for(int j=i+1; j<*dim; j++){
      
      if(a[i]==a[j]){
        
        for(int k=j; k<*dim-1; k++){
          a[k] = a[k+1];
        }
        
        *dim -=1;
        
        
        j--;
      }
    }
  }
}

int main(void) {
    int dim_a;
    printf("Inserire dimensione a: ");
    scanf("%d", &dim_a);
    int *a = malloc(sizeof(int)*dim_a);

    
    for(int i=0; i<dim_a; i++){
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    printf("\n");

    
    rimuovi(a, &dim_a);

}