#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[10];
    int userNumber;
    int licznik = 0;
    int smallestNum;
    int smallestIndex;

    while(licznik < 10) {
        printf("Podaj liczbe nr %d do tablicy: ", licznik + 1);
        scanf("%d", &userNumber);
        array[licznik] = userNumber;
        licznik++;
    }

    smallestNum = array[0];
    smallestIndex = 0;

    for(int i = 1; i < 10; i++){
        if(array[i] < smallestNum) {
            smallestNum = array[i];
            smallestIndex = i;
        }
    }

    printf("\nNajmniejsza liczba w tablicy: %d\n", smallestNum);
    printf("Indeks najmniejszej liczby w tablicy: %d\n", smallestIndex);

    printf("\n");
    return 0;
}
