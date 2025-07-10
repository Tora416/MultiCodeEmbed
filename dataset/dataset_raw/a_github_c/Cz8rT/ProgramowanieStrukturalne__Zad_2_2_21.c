#include <stdio.h>
#include <stdlib.h>

int sequenceA(int);

int main()
{
    int userNumber;
    printf("Podaj nieujemna liczbe calkowita 'n': ");
    scanf("%d", &userNumber);

    while(userNumber < 0 ){
        printf("Podano nieprawidlowe dane!\n");
        printf("Podaj nieujemna liczbe calkowita 'n': ");
        scanf("%d", &userNumber);
    }

    printf("Wyraz '%d' ciagu wynosi: %d\n", userNumber, sequenceA(userNumber));

    getchar();
    return 0;
}

int sequenceA(int n){
    int a_n = 1;
    if(n > 0){ 
        a_n = 2 * sequenceA(n - 1) + 5;
    }
    return a_n;
}
