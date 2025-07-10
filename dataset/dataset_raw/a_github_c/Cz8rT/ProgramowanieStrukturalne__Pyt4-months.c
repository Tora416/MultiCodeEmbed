#include <stdio.h>
#include <stdlib.h>
#define MAXNAME 20
#define MAXABB 3

typedef struct month { 
    char name[MAXNAME];
    char abb[MAXABB];
    int days;
    int order;
} MONTH;

int main()
{
    MONTH months[12] = {
        {"Styczen", "JAN", 31, 1},
        {"Luty", "FEB", 28, 2},
        {"Marzec", "MAR", 31, 3},
        {"Kwiecien", "APR", 30, 4},
        {"Maj", "MAY", 31, 5},
        {"Czerwiec", "JUN", 30, 6},
        {"Lipiec", "JUL", 31, 7},
        {"Sierpien", "AUG", 31, 8},
        {"Wrzesien", "SEP", 30, 9},
        {"Pazdziernik", "OCT", 31, 10},
        {"Listopad", "NOV", 30, 11},
        {"Grudzien", "DEC", 31, 12},
    }; 

    puts(months[10].name);
    puts(months[10].abb);
    printf("Liczba dni: %d\n", months[10].days);
    printf("Numer w roku: %d\n", months[10].order);

    getchar();
    return 0;
}
