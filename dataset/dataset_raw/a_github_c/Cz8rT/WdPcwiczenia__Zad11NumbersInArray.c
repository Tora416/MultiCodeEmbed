#include <stdio.h>
#include <stdlib.h>

int main()
{
    double userNumber;
    double numbersArray[3][5];
    char letterCollection;

    int licznik1 = 0;
    int licznik2 = 0;

    double sum, sumAll, biggestNumber;

    while(licznik1 < 3) {
        switch (licznik1){
            case 0:
                letterCollection = 'A';
            break;
            case 1:
                letterCollection = 'B';
            break;
            case 2:
                letterCollection = 'C';
            break;
        }
        printf("Podaj liczbe nr %d dla zbioru %c: ", licznik2 + 1, letterCollection);
        scanf("%lf", &userNumber);
        numbersArray[licznik1][licznik2] = userNumber;
        licznik2++;
        if(licznik2 >= 5){
            licznik1++;
            licznik2 = 0;
        }
    }

    printf("\n");

    licznik1 = 0;
    licznik2 = 0;

    for(licznik1; licznik1 < 3; licznik1++){
            switch (licznik1){
            case 0:
                letterCollection = 'A';
            break;
            case 1:
                letterCollection = 'B';
            break;
            case 2:
                letterCollection = 'C';
            break;
        }
        for(licznik2; licznik2 < 5; licznik2++){
            printf("%d liczba w zbiorze %c: %.2f\n", licznik2 + 1, letterCollection, numbersArray[licznik1][licznik2]);
            sum += numbersArray[licznik1][licznik2];
            if(biggestNumber < numbersArray[licznik1][licznik2]){
               biggestNumber = numbersArray[licznik1][licznik2];
            }
        }
        licznik2 = 0;
        printf("Srednia zbioru %c: %.2lf\n\n", letterCollection, sum/5);
        sumAll += sum;
        sum = 0;
    }

    printf("Srednia wszystkich zbior\242w: %.2lf\n", sumAll/15);
    printf("Najwi\251ksza liczba: %.2lf\n\n", biggestNumber);
    return 0;
}
