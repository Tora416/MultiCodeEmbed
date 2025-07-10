
#include <stdio.h>

void Columna(int pibote)
{
    int j = 1;
    while(j <= 20)
    {
        if(j >= (10 - pibote) && j <= (10 + pibote))
            printf("Z");
        else
            printf(" ");
        ++j;
    }
}

int main()
{
    int contador1 = 0;
    int contador2 = 7;
    while(contador1 < 8)
    {
    printf("\n");
    if(contador1 > 4)
        Columna(contador2 - 1);
    else
        Columna(contador1 - 1);
    --contador2;
    ++contador1;
    }
    return 0;

}