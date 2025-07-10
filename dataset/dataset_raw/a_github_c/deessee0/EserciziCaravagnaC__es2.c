#include <stdio.h>

void isPrime(int dim, int a[])
{
    int contatore = 0, prime;
    int b[dim];

    
    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
        {
            prime = 0;
            
            if((i != j) && (a[i] % a[j] != 0))
            {
                prime = 1;
                break;                     
            }
        }

        if(prime == 1)
        {
            b[i] = a[i];
        } else {
            b[i] = 0;
        }

        printf("b[%d] = %d\n",i, b[i]);          
    }

   
}


int main(void) {
    int dim; 
    printf("inserire dimensione array: "); 
    scanf("%d", &dim);
    int a[dim];

    
    for(int i=0; i<dim; i++){
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    printf("\n");
    printf("----------------------------\n");
    isPrime(dim,a);

  return 0;
}