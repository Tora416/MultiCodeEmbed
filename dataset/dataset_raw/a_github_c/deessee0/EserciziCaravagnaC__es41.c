#include<stdio.h>

int calcolaFattoriale(int n)
{
    if (n == 1)
        return 1;
    else
        return n * calcolaFattoriale(n - 1);
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

    printf("Inserire dimensione array: "); 
    scanf("%d", &dim);
    int a[dim];

    
    for(int i=0; i<dim; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    
    printf("---------------------------------\n");

    for(int i=0; i<dim; i++)
    {
        a[i] = calcolaFattoriale(a[i]);
        printf("Il fattoriale di a[%d] è: %d\n", i, a[i]);
    }   

    return 0;

}