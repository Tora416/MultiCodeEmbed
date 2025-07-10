#include <stdio.h>
#include <stdlib.h>

void rzad_zn(char ch, int i, int j);

int main()
{
    char userChar;
    int columnStart;
    int columnEnd;

    printf("Podaj znak: ");
    scanf("%c", &userChar);
    printf("Podaj pocz\245tkow\245 kolumn\251: ");
    scanf("%d", &columnStart);
    printf("Podaj ko\344cow\245 kolumn\251: ");
    scanf("%d", &columnEnd);

    rzad_zn(userChar,columnStart, columnEnd);

    return 0;
}

void rzad_zn(char ch, int i, int j) {
    char space = ' ';
    for(int k = i; k > 1; k--){
        putchar(space);
    }
    for(int k = i; k <= j; k++){
        putchar(ch);
    }
    return;
}
