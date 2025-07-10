#include <stdio.h>
#include <stdlib.h>

int main()
{

    float number1, number2;
    int endProgram = 0;

    while(!endProgram){

        printf("Podaj pierwsz\245 liczb\251: ");
        if(scanf("%f", &number1) == 1) {

            printf("Podaj drug\245 liczb\251: ");

            if(scanf("%f", &number2) == 1) {

                float wynik = (number1 - number2) / (number1 * number2);
                printf("\nWynik: %3f\n\n", wynik);

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
