#include <stdio.h>
#include <stdlib.h>

int letterCheck(char c);

int main()
{
    char wholeText[1000];

    FILE *f = fopen("testFile_Zad5.txt", "r");    
    if (f == NULL)
    {
        perror("Nie udalo sie otworzyc pliku testFile_Zad5.txt");
        return 1;
    }
    puts("Plik otwarty pomyslnie!");
    fscanf(f, "%[]", wholeText);
    printf("\nTekst z pliku:\n%s", wholeText);
    printf("\n\n");

    for(int i = 0; i < strlen(wholeText); i++){
        putchar(wholeText[i]);
        printf(" - ");
        if(letterCheck(wholeText[i]) == -1){
            printf("Znak nie jest liter\245.\n");
        } else {
            printf("Jest %d liter\245 alfabetu.\n", letterCheck(wholeText[i]));
        }
    }

    fclose(f);
    return 0;
}

int letterCheck(char c){
    int alphabetNumber;
    int asciiNumber = c;
    if(asciiNumber >= 65 && asciiNumber <= 90){
        alphabetNumber = asciiNumber - 64;
        return alphabetNumber;
    } else if(asciiNumber >= 97 && asciiNumber <= 122){
        alphabetNumber = asciiNumber - 96;
        return alphabetNumber;
    }
    return -1;
}
