#include <stdio.h>
#include <stdlib.h>

void rimuoviDuplicati(int a[], int* dim_a)
{
    for(int i=0;i<*dim_a;i++)
    {
        for(int j=i+1; j<*dim_a; j++)
        {
            if(a[i]==a[j])
            {
                for(int k=j; k<*dim_a-1;j++)
                {
                    a[k] = a[k+1];
                }

                *dim_a -= 1;
                j--;
            }
        }
    }
}

int main(void) {
    
    int dim_a = 7;
    int *a = malloc(sizeof(int)*dim_a);

    for(int i=0; i<dim_a; i++)
    {
        printf("a[%d]=", i);
        scanf("%d", &a[i]);
    }
    printf("\n");

    rimuoviDuplicati(a, &dim_a);

    for(int i=0; i<dim_a; i++)
    {
        printf("a[%d]=", i);
        scanf("%d", &a[i]);
    }

    free(a);

    return 0;
}