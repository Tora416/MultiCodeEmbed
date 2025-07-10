#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char * gerarCaptcha(char captcha[6] )
 {
   
   int cont;
   
   for (cont = 0 ; cont < 4 ; cont++)
    {
       captcha[cont] = 97 + (rand() % 25);
    }
    
    
    for (cont = 4 ; cont < 6 ; cont++)
    {
       captcha[cont] = 48 + (rand() % 9);
    }
    
    captcha[0] = (captcha[0] - 32);
    
    return captcha;
}


char * lerDigitado(char digitado[50])
{
    gets(digitado);
    
    return digitado;
}


int compararCaptcha(char digitado[6] , char captcha[6])
{
  int cont;
  int resultadoComparacao;  
  
  resultadoComparacao = strcmp(digitado,captcha);
  
  return resultadoComparacao;
}



int main(int argc, char *argv[]) {
    
    srand(time(NULL));
    
    int cont;
    int resultado;
    
    char * captcha;
    char vetorCaptcha[7];
    
    char * digitado;
    char vetorDigitado[50];
    
    resultado = 1;
    
    printf("\n =========\n |CAPTCHA| \n =========\n\nDite o codigo abaixo corretamente para continuar: \n\n");
    
    do{
        captcha = gerarCaptcha(vetorCaptcha);
        printf("%s\n" , captcha);
            
        digitado = lerDigitado(vetorDigitado);
        
        resultado = compararCaptcha(digitado , captcha);
        
        if (resultado != 0)
        {
          printf("\nIncorreto! Tente novamente:\n\n");
        }
        
    }while(resultado != 0);
    
    printf("\nCORRETO!!!\Agora ja pode prosseguir...");
        
    return 0;
    
}
