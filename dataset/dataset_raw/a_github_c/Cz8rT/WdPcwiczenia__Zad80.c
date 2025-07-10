#include <stdio.h>
#include <stdlib.h>
#define BASICHOUR1 35
#define BASICHOUR2 37
#define BASICHOUR3 40
#define BASICHOUR4 45
#define OVERTIME 1.5
#define TAX1 0.15
#define TAX2 0.20
#define TAX3 0.25

int main()
{
    int userBasicHour;
    int workHours;
    float brutto;
    float podatek;
    int userChoice;
    int valueOK = 0;
    int endProgram = 0;

    while(!valueOK) {
        printf("********************************************************************\n");
        printf("Podaj liczb\251 odpowiadaj\245c\245 zadanej stawce wynagrodzenia lub opcji:\n");
        printf("1) 35zl/godz.\t\t2) 37zl/godz.\n");
        printf("3) 40zl/godz.\t\t4) 45zl/godz.\n");
        printf("5) wyjscie\n");
        printf("********************************************************************\n");
        userChoice = getchar();

        switch (userChoice) {
            case '1' : {
                userBasicHour = BASICHOUR1;
                printf("Wybrano stawk\251 45zl/godz.\n");
                valueOK = 1;
                break;
            }
            case '2' : {
                userBasicHour = BASICHOUR2;
                printf("Wybrano stawk\251 45zl/godz.\n");
                valueOK = 1;
                break;
            }
            case '3' : {
                userBasicHour = BASICHOUR3;
                printf("Wybrano stawk\251 45zl/godz.\n");
                valueOK = 1;
                break;
            }
            case '4' : {
                userBasicHour = BASICHOUR4;
                printf("Wybrano stawk\251 45zl/godz.\n");
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
        printf("Podaj liczb\251 przepracowanych godzin w tygodniu: ");
        scanf("%d", &workHours);

        if(workHours >= 40) {
            brutto = 40 * userBasicHour + (workHours - 40) * userBasicHour * OVERTIME;
        } else {
            brutto = workHours * userBasicHour;
        }

        if (brutto <= 1200) {
            podatek = brutto * TAX1;
        } else if (brutto > 1200 && brutto <= 1800) {
            podatek = 1200 * TAX1 + (brutto - 1200) * TAX2;
        } else {
            podatek = 1200 * TAX1 + (600) * TAX2 + (brutto - 1800) * TAX3;
        }

        printf("\nWynagrodzenie brutto: %.2fz\210\n", brutto);
        printf("Podatek: %.2fz\210\n", podatek);
        printf("Wynagrodzenie netto: %.2fz\210\n", brutto - podatek);

        getchar();
    }
    return 0;
}
