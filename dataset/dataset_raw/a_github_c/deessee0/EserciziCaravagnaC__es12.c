#include<stdio.h>

int main(void) {
    
    int dim; 
    printf("inserire dimensione array: "); 
    scanf("%d", &dim);
    int a[dim];
    int b[dim];

    
    for(int i=0; i<dim; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    printf("\n");
  
    
    for(int i=0; i<dim; i++)
    {
        printf("b[%d] = ", i);
        scanf("%d", &b[i]);
    }

    printf("\n");

    int c[dim];

    printf("Prodotto scalare dei due vettori: \n");
    for(int i=0; i<dim; i++)
    {
        c[i] = a[i] * b[i];
        printf("c[%d] = ", i );
        printf("%d", c[i]);
        printf("\n");
    }

}