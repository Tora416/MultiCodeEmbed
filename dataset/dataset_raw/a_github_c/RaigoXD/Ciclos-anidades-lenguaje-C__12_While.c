
#include <stdio.h>

int main()
{
    char letra;
    int i = 0;
    int j;
    while( i< 7){
    switch (i){
            case 0: letra = 'P';break;
            case 1: letra = 'N';break;
            case 2: letra = 'L';break;
            case 3: letra = 'J';break;
            case 4: letra = 'H';break;
            case 5: letra = 'F';break;
            case 6: letra = 'D';break;
    }
    j = 0;
    while(j <= 13){
        if(j >= (1 + i) && j <= (13-i))
            printf("%c", letra);
        else
        printf(" ");
        ++j;
    }
        printf("\n");
        ++i;
    }
    return 0; 
}