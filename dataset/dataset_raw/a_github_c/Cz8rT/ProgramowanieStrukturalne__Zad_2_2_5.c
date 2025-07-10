#include <stdio.h>
#include <stdlib.h>

float powerOfTwo(int);

int main()
{
    int userNumber;
    printf("Podaj liczbe calkowita 'n': ");
    scanf("%d", &userNumber);

    printf("2 do potegi %d to: %.3f\n", userNumber, powerOfTwo(userNumber));

    getchar();
    return 0;
}

float powerOfTwo(int n){
    float result = 1;
    if(n >= 0){
        for(int i = 0; i < n; i++){
            result = result * 2;
        }
    } else {
        for(int i = 0; i > n; i--){
            result = result * 2;
        }
        result = 1 / result;
    }
    return result;
}
