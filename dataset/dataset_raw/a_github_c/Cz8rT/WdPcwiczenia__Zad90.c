#include <stdio.h>
#include <stdlib.h>

int main()
{
    char userChar;
    char userNumberString[255];
    int userNumber;
    int counter = 0;

    printf("Podaj liczbe calkowita: ");

    while((userChar = getchar()) != '\n') {
        userNumberString[counter] = userChar;
        counter++;
    }
    userNumber = atoi(userNumberString); 

    printf("Liczby pierwsze podanej liczby: ");
    for(int i = 2; i <= userNumber; i++) {
        int primeCounter = 0;
        for(int j = 1; j <= i; j++){
            if(i % j == 0 ) {
                primeCounter++;
            }
        }
        if(primeCounter == 2){
            printf(" [%d]; ", i);
        }
    }

    getchar();
    return 0;
}
