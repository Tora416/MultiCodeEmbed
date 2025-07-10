#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int srandString(int vetorCaptcha[6])
{
    int contador;
    int recebe;
    

    for(contador = 0; contador < 6; contador ++)
    {
        recebe = rand() % 3;
        if(recebe == 0);
        {
            vetorCaptcha[contador] = (rand() % 10) + (48);
        }
        if(recebe == 1)
        {
            vetorCaptcha[contador] = (rand() % 25) + (65);  
        }
        if(recebe == 2)
        {
            vetorCaptcha[contador] = (rand() % 25) + (97);
        }
        
        printf("%c", vetorCaptcha[contador]);
    }
    
    
}


int cmpString(char vetorUsuario[6], int vetorCaptcha[6])
{
    int contador;
    
    for(contador = 0; contador < 6; contador ++)
    {
        if(strlen(vetorUsuario) != 6)
        {
            if(vetorUsuario[contador] == vetorCaptcha[contador])
            {
                printf("Digite novamente!!\n"); 
                return 0;
            }
        }
        else
        {   
            printf("Voce digitou corretamente!!");  
            return 1;
        }
            
    }
                
} 



int main(int argc, char *argv[]) 
{
    int vetorCaptcha[6];
    char vetorUsuario[6];
    
    int teste = 0;
    
    srand(time(NULL));
        
    srandString(vetorCaptcha);
    
    printf("\n\n");
    
    do
    {
        printf("Digite corretamente o CAPTCHA acima: ");
        gets(vetorUsuario);
        
        teste = cmpString(vetorUsuario, vetorCaptcha);
        
        
    }
    while(teste == 0);
    
    
    
    return 0;
}
