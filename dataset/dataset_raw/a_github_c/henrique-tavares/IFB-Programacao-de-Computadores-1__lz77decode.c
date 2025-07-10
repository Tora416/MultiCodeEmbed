#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lz77decode.h"

void decompress(char *compressed_str)
{
    

    int pos,             
        tam,             
        tam_d,           
        tam_total = 1;   

    char letra,          
        *decom = NULL;   

    decom = malloc(1 * sizeof(char)); 

    while (*compressed_str)           
    {
        if (*compressed_str == '(')   
        {
            compressed_str++;
            
            

            
            if (*compressed_str == '-')
            {
                pos = -1;
            }

            
            else
            {
                pos = atoi(compressed_str);
            }


            
            while (*compressed_str != ',')
            {
                compressed_str++;
            }
            compressed_str++;


            tam = atoi(compressed_str);                       
            tam_total += tam + 1;                             
            decom = realloc(decom, tam_total * sizeof(char)); 
            

            
            while (*compressed_str != ',')
            {
                compressed_str++;
            }
            compressed_str++;


            
            if (*compressed_str == '\\' && *(compressed_str + 1) == '0')
            {
                letra = '\0';
            }

            
            else
            {
                letra = *compressed_str; 
            }
            compressed_str++;
            


            

            tam_d = strlen(decom);

            
            if (pos == -1)
            {
                *decom = letra;
                *(decom + 1) = '\0';
            }
            
            else if (pos == 0) 
            {
                *(decom + tam_d) = letra;
                *(decom + tam_d + 1) = '\0';
            }
            
            else
            {
                int i, 
                    j; 

                for (i = tam_d - pos, j = 0; j < tam; i++, j++)
                {
                    
                    if (i == tam_d)
                    {
                        i = tam_d - pos;
                    }
                    *(decom + j + tam_d) = *(decom + i);
                }

                
                *(decom + tam_d + tam) = letra;

                
                *(decom + tam_d + tam + 1) = '\0';
            }
            
        }
        compressed_str++;
    }

    
    tam_d = strlen(decom);
    
    for (int i = 0; i < tam_d; i++)
    {
        printf("%c", *(decom + i));
    }
    putchar('\n');
    
    

    free(decom); 
}