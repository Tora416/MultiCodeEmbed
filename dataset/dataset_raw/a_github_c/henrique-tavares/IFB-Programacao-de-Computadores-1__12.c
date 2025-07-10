#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *arq_1, *arq_2, *arq_3;
    char aux;

    if (argc < 4)
    {
        printf("\nErro! Não foram informados arquivos o suficiente\n\n");
        return 0;
    }

    arq_1 = fopen(argv[1], "r");
    arq_2 = fopen(argv[2], "r");
    arq_3 = fopen(argv[3], "w");

    if (arq_1 == NULL || arq_2 == NULL || arq_3 == NULL)
    {
        printf("\nErro ao abrir algum arquivo\n\n");
        return 0;
    }

    while ((fscanf(arq_1, "%c", &aux) != EOF))
    {        
        fprintf(arq_3, "%c", aux);   
    }
    
    while ((fscanf(arq_2, "%c", &aux) != EOF))
    {        
        fprintf(arq_3, "%c", aux);   
    }

    fclose(arq_1);
    fclose(arq_2);
    fclose(arq_3);

    return 0;
}