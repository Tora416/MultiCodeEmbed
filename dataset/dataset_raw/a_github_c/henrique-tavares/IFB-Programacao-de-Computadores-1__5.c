#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *arq_1, *arq_2;
    char aux, *str_1, *str_2;
    int n, m;
    float **matriz, aux_2, *texto;

    if (argc < 3)
    {
        printf("\nErro! Não foram informados arquivos o suficiente\n\n");
        return 0;
    }

    arq_1 = fopen(argv[1], "r");
    arq_2 = fopen(argv[2], "w");

    if (arq_1 == NULL || arq_2 == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n\n");
        return 0;
    }

    int i = 0;
    
    while (fscanf(arq_1, "%f", &aux_2) != EOF)
    {
        i++;
    }

    printf("\ni = %i\n", i);

    texto = malloc(i * sizeof(float));

    rewind(arq_1);

    for (int j = 0; j < i; j++)
    {
        fscanf(arq_1, "%f", texto+j);
        
    }

    n = texto[0];
    m = texto[1];

    

    matriz = malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++)
    {
        matriz[i] = malloc(m * sizeof(float));
    }


    for (int i = 0, k = 0; i < n; i++)
    {
        for (int  j = 0; j < m; j++)
        {
            matriz[i][j] = texto[k+2];
            k++;
            
        }
        
    }
    

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(arq_2, "%f ", matriz[j][i]);
            
        }
        fprintf(arq_2, "%c", '\n');
        
    }


    return 0;
}