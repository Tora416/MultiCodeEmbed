#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lz77encode.h" 
#include "lz77decode.h" 
#define true 1
#define false 0

int main()
{
    char *str = NULL;
    int tam, k = 6, i0;

    str = malloc(10002 * sizeof(char)); 

    fgets(str, 10002, stdin);
    tam = strlen(str);

    if (*(str + tam - 1) == '\n') 
    {
        *(str + tam - 1) = '\0';
    }

    
    if (*str == '(')
    {
        decompress(str); 
    }
    


    
    else
    {
        
        
        
        
        
        
        

        
        
        
        
        
        

        
        
        
        
        

        compress(str, k); 
    }
    

    free(str); 

    return 0;
}