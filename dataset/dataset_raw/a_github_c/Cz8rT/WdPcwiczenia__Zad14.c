#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define GODZINA 60

bool nextCalculation(void); 

int main()
{
    int godziny, minuty, czasWMinutach;
    bool endProgram = false;

    while(!endProgram){
        printf("Podaj ilo\230\206 minut do przeliczenia.\n");
        scanf("%d", &czasWMinutach);

        godziny = czasWMinutach / GODZINA;
        minuty = czasWMinutach % GODZINA;

        printf("%d minut to %d godzin i %d minut\n\n", czasWMinutach, godziny, minuty);
        fflush(stdin);

        endProgram = nextCalculation();
    }

    return 0;
}

bool nextCalculation(void) {

    char userResponse;
    printf("Czy chcesz przeliczyc czas ponownie? y/n: ");
    scanf("%c", &userResponse);
    if (userResponse != 121) {
            return true;
    }
    fflush(stdin);
    return false;
}
