#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PESEL 12

typedef struct personalInfo {
    char pesel[PESEL];
    struct person {
        char firstName[21];
        char middleName[21];
        char lastName[21];
    };
} PERSONINFO;

int main()
{
    PERSONINFO persons[] = {
        "23232323232", "Adam", "Rick", "Melix",
        "11111111111", "Morty", "Eric", "Willis",
        "88833388822", "Tom", "George", "Brady"
    };

    int counter = 0;
    int size = sizeof(persons)/sizeof(*persons);
    while(counter < size){
        printf("%7s, %7s %7s -- %s\n", persons[counter].lastName, persons[counter].firstName, persons[counter].middleName, persons[counter].pesel);
        counter++;
    }


    getchar();
    return 0;
}
