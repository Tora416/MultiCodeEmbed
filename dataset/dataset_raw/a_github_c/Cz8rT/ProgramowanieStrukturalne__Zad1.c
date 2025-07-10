#include <stdio.h>
#include <stdlib.h>
#include "months.c"
#define MAXNAME 20
#define MAXABB 3

int numberOfDays(string);

int main()
{
    char userMonth[MAXNAME];

    printf("Podaj nazwe miesiaca.\n");
    printf("Program wyswietli liczbe dni od poczatku roku do podanego miesiaca: ");
    scanf("%s", &userMonth);

    printf("Liczba dni: %d", numberOfDays(userMonth));

    getchar();
    return 0;
}

int numberOfDays(monthName){
    int error = 1; 
    int result = 0;
    for (int i = 0; i < 12; i++){
        result += months[i].days;
        if(strcmp(monthName, months[i].name) == 0){
            error = 0;
            break; 
        }
    }
    if(error == 1){
        result = 0;
    }
    return result;
};
