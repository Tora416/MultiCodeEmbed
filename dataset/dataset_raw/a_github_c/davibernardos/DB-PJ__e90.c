#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char * gercaptcha (char captcha [6]) {
    int cont;
        
    for (cont = 0; cont < 6; cont ++)
    {
        if (cont== 0 || cont==3|| cont ==5)
        {
            captcha [cont] = 65 + (rand() % 26);
            
        }else {
            if (cont==1 || cont == 2|| cont==4)
            {
                captcha [cont] = 48 + (rand() % 10);
            }
        }
    }
    return captcha;
    
}
int comparar (char captchalido [6], char captchaescrito [6])
{
    int cont;
    int diferenca;
    
    diferenca = 0;
    
    for ( cont = 0; cont <6; cont++)
    {
        if (captchalido [cont]   != captchaescrito [cont])
        {
            diferenca ++;
        }
    }
        if (diferenca > 0){
            return 1;
            
        }
        else {
            return 0;
        }
}


int main (int argc, char *argv[]) {
    char captchaG [6];
    char *captcha;
    char leitura [6];
    int result;
    
    srand (time (NULL));
    
    
    printf ("Digite conforme o Captcha \n");
    captcha = gercaptcha (captchaG);
    printf ("Captcha: %s \n", captcha);
    
    gets (leitura);
    
    result = comparar (captcha, leitura); 
    
    if (result == 1)
    {
        printf ("Deu ruim");
        }
        if (result ==0)
        {printf ("Deu bom");
            }   
    
    
    
    return 0;
}








