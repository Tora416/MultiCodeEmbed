#include <stdio.h>

void strCopy(char *source, char* destin)
{
    if (*source == '\0')
    {
        *destin = '\0';
        return;
    }

    *destin = *source;
    strCopy(source + 1, destin + 1);
}


int main()
{
    char a[50] = "", b[50] = "";

    printf("Enter string:\n");
    scanf("%s", a);
    
    printf("\nstring 1: %s string2 2: %s\n", a, b);
    printf("\nCopying strings...\n");

    strCopy(a, b);

    printf("\nstring 1: %s string2 2: %s\n", a, b);

}