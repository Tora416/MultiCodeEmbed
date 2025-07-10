#include <stdio.h>

void lettura(int v[], int dim)
{
    int i=0;
    for(i=0;i<dim;i++)
    {
        scanf("%d", &v[i]);
    }
}

int somma(int v[], int dim)
    {
        int tot=0;
        int i=0;
        
        for(i=0;i<dim;i++)
        {
            tot += v[i]; 
        }

        return tot;
    }

int main(void) 
{
    int a[5];
    int tot;

    lettura(a,5);

    somma(a,5);

    printf("Somma totale dell'array: %d", tot);

}