#include <stdio.h>
#include <stdlib.h>

int main()
{
    float array[10];
    float userNumber;
    float sumPlus = 0;
    float sumMinus = 0;
    int licznik = 0;
    int licznikPlus = 0;
    int licznikMinus = 0;

    while(licznik < 10) {
        printf("Podaj liczbe nr %d do tablicy: ", licznik + 1);
        scanf("%f", &userNumber);
        array[licznik] = userNumber;
        licznik++;
    }

    for(int i = 0; i < 10; i++){
        if(array[i] > 0){
            sumPlus += array[i];
            licznikPlus++;
        }
        if(array[i] < 0){
            sumMinus += array[i];
            licznikMinus++;
        }
    }

    if (licznikPlus != 0) {
        printf("Srednia arytmatyczna dodatnich elementow: %.2f\n", sumPlus/licznikPlus);
    } else {
        printf("Srednia arytmatyczna dodatnich elementow wynosi 0\n");
    }

    if (licznikMinus != 0) {
        printf("Srednia arytmatyczna ujemnych elementow: %.2f\n", sumMinus/licznikMinus);
    } else {
        printf("Srednia arytmatyczna ujemnych elementow wynosi 0\n");
    }

    printf("\n");
    return 0;
}
