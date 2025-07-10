#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "months.c"
#define MAXNAME 20
#define MAXABB 3

int numberOfDays(int, int, int);

int main()
{
    int userYear;
    int userDay;
    char userMonth[MAXNAME];

    printf("Program wyswietli liczbe dni od poczatku roku do podanego dnia miesiaca.\n");
    printf("Podaj numer dnia.\n");
    scanf("%d", &userDay);
    printf("Podaj (nazwe, numer lub skrot) miesiaca.\n");
    scanf("%s", &userMonth);
    printf("Podaj rok.\n");
    scanf("%d", &userYear);

    printf("Liczba dni: %d", numberOfDays(userMonth, userDay, userYear));

    getchar();
    return 0;
}

int numberOfDays(month, day, year){
    int error = true; 
    int leapYear = false;
    int result = day;
    if((year%4==0) && ((year%400==0) || (year%100!= 0)))
        leapYear = true; 
    for (int i = 0; i < 12; i++){
        if(strcmp(month, months[i].name) == 0 || strcmp(month, months[i].abb) == 0 || atoi(month) == months[i].order){
            error = false;
            break; 
        }
        result += months[i].days;
        if(leapYear && months[i].order == 2)
            result += 1;
    }
    if(day <= 0 || day > 31){
        error = true; 
    }
    if(error == true){
        result = 0;
    }
    return result;
};
