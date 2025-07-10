#include <stdio.h>

int main()
{
    int n, imaior, imenor, tempm;
    float temp[100000], maior, menor, media = 0;

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%f", &temp[i]);

        if (i == 0)
        {
            maior = temp[i];
            imaior = i;
            menor = temp[i];
            imenor = i;
        }

        else if (temp[i] > maior)
        {
            maior = temp[i];
            imaior = i;
        }

        else if (temp[i] < menor)
        {
            menor = temp[i];
            imenor = i;
        }

        media += temp[i];
    }

    media /= n;

    printf("%i %.1f\n%i %.1f\n%.1f\n", imenor, menor, imaior, maior, media);

    for (int i=0; i<n; i++)
    {
        if (temp[i] >= media)
        {
            printf("%i ", i);
        }
    }
    putchar('\n');

    return 0;
}