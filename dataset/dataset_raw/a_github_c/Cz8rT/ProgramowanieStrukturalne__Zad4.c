#include <stdio.h>
#include <stdlib.h>

float ciag(int n);

int main()
{
    int N;

    printf("Podaj dodatnia wartosc liczby 'N': ");
    scanf("%d", &N);

    while(N <= 0){
        printf("Podano bledna wartosc\n");
        printf("Podaj dodatnia wartosc liczby 'N': ");
        scanf("%d", &N);
    }

    printf("N-ty wyraz ciagu to: %.2f", ciag(N));

    printf("\n");
    return 0;
}

float ciag(int n){
    float a_n;
    if(n == 1) return 1;
    if(n == 2) return 2;
    if(n == 3) return 3;
    a_n = (ciag(n-1) + ciag(n-2) + ciag(n-3))/3; 
    return a_n;
};
