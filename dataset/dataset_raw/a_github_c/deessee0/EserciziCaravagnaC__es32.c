#include<stdio.h>
#include <stdlib.h>

int minimo(int a[], int dim)
    {

    int valoreMinimo = a[0], locazione = 0;

    for(int i=0; i < dim; i++)
    {
        if ( a[i] < valoreMinimo ) 
        {
            valoreMinimo = a[i];
            locazione = i;
        }
    } 
    
    return locazione;
}

void delta_minimo(int a[], int n, int dim)
{
    int differenza[dim];
    int risultato;


    for(int i = 0; i<dim; i++)
    {
        if(abs(a[i]) > n)
        {
            differenza[i] = abs(a[i]) - n;
            
        }   else   {

            differenza[i] = n - abs(a[i]);
        }         
    }

    risultato = minimo(differenza, dim); 
    
    
    printf("----------------------------\nIntero in valore assoluto più vicino a quello fornito: %d", a[risultato]);

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
    int dim;
    int i = 0;
    int n, risultato;

    printf("Inserire dimensione array: "); 
    scanf("%d", &dim);
    int a[dim];

    
    for(int i=0; i<dim; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    
    printf("\n");

    printf("Inserisci il numero che vuoi ricercare nell'array: ");
    scanf("%d", &n);

    printf("----------------------------\nVettore inserito:\n");
    stampa_vettore(a, dim);
    printf("\n");
    delta_minimo(a, n, dim);
    
    

    return 0;

}