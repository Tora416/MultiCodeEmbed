#include <stdio.h>
#include <stdlib.h>

int wynik(float, float);

int main()
{

    float number1, number2;
    int endProgram = 0;

    while(!endProgram){

        printf("Podaj pierwsz\245 liczb\251: ");
        if(scanf("%f", &number1) == 1) {

            printf("Podaj drug\245 liczb\251: ");

            if(scanf("%f", &number2) == 1) {

                wynik(number1, number2);

            } else {
            printf("Podano b\210\251dne dane. Zako\344czenie pracy programu!\n");
            endProgram = 1;
            }
        } else {
            printf("Podano b\210\251dne dane. Zako\344czenie pracy programu!\n");
            endProgram = 1;
        }
    }

    getchar();
    return 0;
}

wynik(float x, float y) {
    float result = (x - y) / (x * y);
    printf("\nWynik: %3f\n\n", result);
    return 0;
}
