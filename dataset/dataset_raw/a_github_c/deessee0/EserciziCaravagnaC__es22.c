#include<stdio.h>

void scambia(int v[], int dim, int i, int j){

    if(dim > 0)
    {
        if((i >= 0) && (i <= dim) && (j >= 0) && (j <= dim))
        {
            int tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }
    }
}

int minimo(int a[], int dim)
    {

    int valoreMinimo = a[0], locazione = 0, i;

    for(i=0; i < dim; i++)
    {
        if ( a[i] < valoreMinimo ) 
        {
            valoreMinimo = a[i];
            locazione = i;
        }
    } 
    
    return locazione;
}

void stampa_vettore(int a[], int dim)
{

    for(int i=0; i<dim; i++)
    {
        printf("a[%d] = ", i);
        printf("%d\n", a[i]);
    }
}

int main(void) {
    int dim, indice;
    int i = 0;

    printf("Inserire dimensione array: "); 
    scanf("%d", &dim);
    int a[dim];

    
    for(int i=0; i<dim; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    
    printf("\n");

    indice = minimo(a, dim);
    printf("-------------------------------\n");
    printf("L'indice minore è: %d\n", indice);
    
    scambia(a,dim, 0, indice);

    printf("\nQuesto è l'array con il valore minimo in testa:\n");

    stampa_vettore(a, dim);
    
    return 0;

}