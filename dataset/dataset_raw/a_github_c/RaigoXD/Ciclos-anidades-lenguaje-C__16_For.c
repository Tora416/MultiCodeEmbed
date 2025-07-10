
#include <stdio.h>

void Columna(int pibote)
{
    for(int j = 1; j <= 20; ++j)
    {
        if(j >= (10 - pibote) && j <= (10 + pibote))
        printf("Z");
    else
        printf(" ");
    }
}

int main()
{
    int contador1 = 0;
    int contador2 = 7;
    for(contador1 = 1; contador1 < 8; ++contador1)
    {
    printf("\n");
    if(contador1 > 4)
        Columna(contador2 - 1);
    else
        Columna(contador1 - 1);
    --contador2;
    }
    return 0;

}

