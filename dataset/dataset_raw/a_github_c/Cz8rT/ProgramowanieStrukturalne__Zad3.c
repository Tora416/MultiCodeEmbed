#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXTYT 40
#define MAXAUT 40
#define MAXKS 100

struct ksiazka {
    char tytul[MAXTYT];
    char autor[MAXAUT];
    float wartosc;
};

int main()
{
    struct ksiazka bibl[MAXKS]; 
    int licznik = 0;
    int index;
    float koszt = 0;

    printf("Podaj tytul ksiazki.\n");
    printf("Aby zakonczyc, wcisnij [enter] na poczatku wiersza.\n");

    while(licznik < MAXKS && gets(bibl[licznik].tytul) != NULL && bibl[licznik].tytul[0] != '\0'){
        printf("Teraz podaj autora.\n");
        gets(bibl[licznik].autor);
        printf("Teraz podaj wartosc.\n");
        scanf("%f", &bibl[licznik++].wartosc);
        while(getchar() != '\n')
            continue; 
        if(licznik < MAXKS)
            printf("Podaj kolejny tytul.\n");
    }

    printf("Oto posortowana lista Twoich ksiazek:\n");

    for(index = 0; index < licznik; index++){
        for(int j = 0; j < licznik; j++){
            if(strcmp(bibl[j].tytul,bibl[index].tytul)>0){
                struct ksiazka temp = bibl[index];
                bibl[index] = bibl[j];
                bibl[j] = temp;
            }
        }
    }

    for(index = 0; index < licznik; index++){
        printf("%s, autor: %s, cena: %.2f zl\n", bibl[index].tytul, bibl[index].autor, bibl[index].wartosc);
        koszt += bibl[index].wartosc;
    }

    printf("----------------------------------------------------------------\n");
    printf("Wartosc wszystkich ksiazek: %.2f zl\n", koszt);

    getchar();
    return 0;
}
