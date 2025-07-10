#include <stdio.h>
#include <stdlib.h>
#define FREE 17850
#define HEAD 23900
#define MARRIEDT 29750
#define MARRIEDS 14875
#define TAX1 0.15
#define TAX2 0.28

int main()
{
    int endProgram = 0;

    while(!endProgram) {

        int userCategory;
        float userIncome;
        float userTax;
        int userChoice;
        int valueOK = 0;

        while(!valueOK) {
            printf("********************************************************************\n");
            printf("Wybierz odpowiednia opcje:\n");
            printf("1) Stan wolny\t\t\t2) Glowa rodziny\n");
            printf("3) Malzenstwo, wspolnie\t\t4) Malzenstwo, osobno\n");
            printf("5) wyjscie\n");
            printf("********************************************************************\n");
            userChoice = getchar();

            switch (userChoice) {
                case '1' : {
                    userCategory = FREE;
                    printf("Wybrano [Stan wolny]\n");
                    valueOK = 1;
                    break;
                }
                case '2' : {
                    userCategory = HEAD;
                    printf("Wybrano [Glowa rodziny]\n");
                    valueOK = 1;
                    break;
                }
                case '3' : {
                    userCategory = MARRIEDT;
                    printf("Wybrano [Malzenstwo, wspolnie]\n");
                    valueOK = 1;
                    break;
                }
                case '4' : {
                    userCategory = MARRIEDS;
                    printf("Wybrano [Malzenstwo, osobno]\n");
                    valueOK = 1;
                    break;
                }
                case '5' : {
                    valueOK = 1;
                    endProgram = 1;
                    break;
                }
                default : fflush(stdin);
            }

        }

        if (!endProgram) {
            printf("Podaj dochod podlegajacy opodatkowaniu: ");
            scanf("%f", &userIncome);
            if(userIncome <= userCategory){
                userTax = TAX1 * userIncome;
            } else {
                userTax = TAX1 * userCategory + (userIncome - userCategory) * TAX2;
            }
            printf("Wysokosc naleznego podatku: %.2f$\n\n", userTax);
            getchar();
        }
    }
    return 0;
}
