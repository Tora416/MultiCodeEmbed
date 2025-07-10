#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getNChars(int);

int main()
{
    int userNum;
    printf("Podaj liczbe znakow.\n");
    scanf("%d", &userNum);

    getNChars(userNum);

    printf("\n------------------------------------------");
    printf("\nDziekuje. Dobranoc! To juz jest koniec!\n");

    getchar();
    return 0;
}

void getNChars(int numOfChars) {
    char stringArray[numOfChars];
    fflush(stdin);
    printf("Podaj znaki.\n");
    for(int i = 0; i < numOfChars; i++) {
        stringArray[i] = getchar();
        if (strcmp(&stringArray[i], " ") == 0 || strcmp(&stringArray[i], "\t") == 0 || strcmp(&stringArray[i], "\n") == 0) {
            printf("\nNapotkano spacje, tabulator lub znak nowej linii!\n");
            break;
        }
    }
    printf("\nPodane znaki to: ");
    puts(stringArray);
};
