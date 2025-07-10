#include <stdio.h>
#include <stdlib.h>

int wypisz(int * array, int n);

int main()
{
    int tablica[10];
    int userNumber;
    int licznik = 0;
    int size = sizeof(tablica)/sizeof(tablica[0]);

    while(licznik < 10) {
        printf("Podaj liczbe nr %d do tablicy: ", licznik + 1);
        scanf("%d", &userNumber);
        tablica[licznik] = userNumber;
        licznik++;
    }

    printf("\n");
    wypisz(tablica, size);

    printf("\n");
    return 0;
}

int wypisz(int * array, int n){
   for(int i = 0; i < n; i++){
        if(array[i] % 2 == 0) {
            printf("Parzysta liczba %d o indeksie %d\n", array[i], i);
        }
    }
};
