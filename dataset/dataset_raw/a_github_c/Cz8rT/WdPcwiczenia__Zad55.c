#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

int main()
{
    char ch;
    int oddSum = 0;
    int evenSum = 0;
    int oddCounter = 0;
    int evenCounter = 0;

    printf("Podaj liczby ca\210kowite. '0' zako\344czy program!\n");
    while((ch = getchar()) != '0') {
        if (isdigit(ch)){
            switch (ch % 2) {
                case 0 :
                evenCounter++;
                evenSum += ch - '0'; 
                break;
            default :
                oddCounter++;
                oddSum += ch - '0';
                break;
            }
        }
    }
    printf("Liczb parzystych: %d\nSrednia warto\230\206: %d\n\n", evenCounter, evenSum / evenCounter);
    printf("Liczb nieparzystych: %d\nSrednia warto\230\206: %d\n", oddCounter, oddSum / oddCounter);

    getchar();
    return 0;
}

