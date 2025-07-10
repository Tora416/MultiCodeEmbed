#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *arq_1, *arq_2, *arq_3;
    int *vet_1, *vet_2, aux;
    int aux_1 = {1, 3, 5, 7, 10, 11}, aux_2 = {0, 2, 4, 6, 8, 10};

    if (argc < 4)
    {
        printf("\nErro! Não foram informados arquivos o suficiente\n\n");
        return 0;
    }

    arq_1 = fopen(argv[1], "w+b");
    arq_2 = fopen(argv[2], "w+b");
    arq_3 = fopen(argv[3], "wb");

    if (arq_1 == NULL || arq_2 == NULL || arq_3 == NULL)
    {
        printf("\nErro ao abrir algum arquivo\n\n");
        return 0;
    }

    fwrite(&aux_1, sizeof(int), 6, arq_1);
    fwrite(&aux_2, sizeof(int), 6, arq_2);

    fseek(arq_1, 0, SEEK_SET);
    fseek(arq_2, 0, SEEK_SET);

    int i = 0, j = 0;
    
    while (fread(&aux, sizeof(int), 1, arq_1) != 0)
    {
        i++;
    }

    while (fread(&aux, sizeof(int), 1, arq_2) != 0)
    {
        j++;
    }

    vet_1 = malloc(i * sizeof(int));
    vet_2 = malloc(j * sizeof(int));

    fseek(arq_1, 0, SEEK_SET);
    fseek(arq_2, 0, SEEK_SET);

    fread(vet_1, sizeof(int), i, arq_1);
    fread(vet_2, sizeof(int), j, arq_2);

    for (int i2 = 0, j2 = 0; i2 < i, j2 < j;)
    {
        if (vet_1[i2] < vet_2[j2])
        {
            fwrite(vet_1 + i2, sizeof(int), 1, arq_3);
            i2++;
        }

        else if (vet_2[j2] < vet_1[i2])
        {
            fwrite(vet_2 + j2, sizeof(int), 1, arq_3);
            j2++;
        }

        else if (vet_1[i2] == vet_2[j2])
        {
            fwrite(vet_1 + i2, sizeof(int), 1, arq_3);
            fwrite(vet_2 + j2, sizeof(int), 1, arq_3);
            i2++;
            j2++;
        }
    }

    fclose(arq_1);
    fclose(arq_2);
    fclose(arq_3);

    return 0;
}