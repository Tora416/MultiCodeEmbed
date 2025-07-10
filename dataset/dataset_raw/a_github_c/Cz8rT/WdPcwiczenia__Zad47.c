#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

int main()
{
    char ch;
    int changeCounter = 0;

    printf("Podaj znaki. '#' zako\344czy program!\n");
    while((ch = getchar()) != '#') {
        if(ch == '!') {
            putchar(ch);
            putchar(ch);
            changeCounter++;
            continue;
        }
        if(ch == '.') {
            ch = '!';
            putchar(ch);
            changeCounter++;
            continue;
        }
        putchar(ch);
    }
    printf("\nLiczba wykonanych zmian: %d\n", changeCounter);
    getchar();
    return 0;
}

