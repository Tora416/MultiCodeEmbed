#include <stdio.h>
#include <stdlib.h>

void wiersz_zn(char ch, int i, int j);

int main()
{
    char userChar;
    int charsInRow;
    int numberOfRows;

    printf("Podaj znak: ");
    scanf("%c", &userChar);
    printf("Podaj ilo\230\206 znak\242w w wierszu: ");
    scanf("%d", &charsInRow);
    printf("Podaj liczb\251 wierszy: ");
    scanf("%d", &numberOfRows);

    wiersz_zn(userChar,charsInRow, numberOfRows);

    return 0;
}

void wiersz_zn(char ch, int i, int j) {
    putchar('\n');
    for(j; j > 0; j--){
        for(int k = i; k > 0; k--){
            putchar(ch);
        }
        putchar('\n');
    }
    return;
}
