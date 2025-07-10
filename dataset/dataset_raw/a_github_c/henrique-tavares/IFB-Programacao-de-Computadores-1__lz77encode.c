#include <stdio.h>
#include "lz77encode.h"
#define true 1
#define false 0

void compress(char *str, int k)
{
    int pos,         
        tam_maior,   
        tam,         
        pos_aux,     
        indice = 0,  
        i_aux,       
        end = false; 

    
    printf("(-1,0,%c)", *str); 

    str++;
    indice++;
    

    
    while (*str) 
    {

        
        tam_maior = 0;

        
        pos = 0;

        
        for (int i = indice - 1; i >= (indice - k) && i >= 0; i--)
        {
            
            if (*(str - indice + i) == *(str))
            {
                tam = 0;
                i_aux = i;

                
                for (int j = 0; *(str - indice + i_aux + j) == *(str + j); j++)
                {
                    
                    if (j == 0) 
                    {
                        pos_aux = -(-indice + i_aux + j);
                    }

                    
                    if ((-indice + i_aux + j) >= 0)
                    {
                        i_aux = i - j;
                    }

                    tam++;
                }

                
                if (tam > tam_maior)
                {
                    tam_maior = tam;
                    pos = pos_aux;
                }
            }
        }
        
        str += tam_maior;
        
        indice += tam_maior;
        

        
        
        
        if (*str == '\0')
        {
            printf("(%i,%i,\\0)", pos, tam_maior);
            end = true;
        }
        else
        {
            printf("(%i,%i,%c)", pos, tam_maior, *str);
        }
        

        
        str++;
        indice++;
    }

    if (end == false) 
    {
        printf("(0,0,\\0)");
    }
    putchar('\n');
}