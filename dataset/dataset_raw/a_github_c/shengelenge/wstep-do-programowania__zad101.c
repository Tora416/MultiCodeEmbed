#include <stdio.h>

int main()
{
    long double min, max, kolejna, suma = 0, srednia;

    printf("Podaj liczby rzeczywsite, po wpisaniu 0 program zakonczy wczytywanie.\nLiczby:\n");
    scanf("%Lf", &kolejna);

    suma += kolejna;


    if (kolejna != 0)
    {
        int i = 1;
        min = kolejna;
        max = kolejna;
        scanf("%Lf", &kolejna);
        suma += kolejna;
        srednia = suma / i++;
        while (kolejna)
        {
            if (kolejna > max)
                max = kolejna;
            else {
                if (kolejna < min)
                    min = kolejna;
            }
            scanf("%Lf", &kolejna);
            suma += kolejna;
            srednia = suma / i++;
        }

        printf("min = %.2Lf, max = %.2Lf\n", min, max);
        printf("suma = %.2Lf, ", suma);
        printf("srednia = %.2Lf, ", srednia);
    }
    else
        printf("Ciag wejsciowy jest pusty.\n");

    return 0;
}
