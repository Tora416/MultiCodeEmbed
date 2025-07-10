#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CAPTCHA 6



int loop = 1;


char * gerarCaptcha(char valor[CAPTCHA]) {
    
    int cont;
    int randomico;
    
    srand(time(NULL));
    
    for(cont = 0; cont < CAPTCHA; cont++){
        
        randomico = ((rand() % 122) + 1);
        
        if ((randomico >= 48 && randomico <= 57) || (randomico >= 65 && randomico <= 90) || (randomico >= 97 && randomico <= 122)) {
            
            valor[cont] = randomico;
            
        }else{
            
            cont--;
            
        }
        
    }
    
    return valor;
    
}


void trasformarCaptcha(char novaString[CAPTCHA], char digitado[CAPTCHA]) {
    
    strcpy(novaString, digitado);
    
}


void comparaCaptcha(char valor[CAPTCHA], char digitado[CAPTCHA]){
    
    if (strcmp(valor, digitado) == 0) {
        
        printf("Obrigado, esta confirmado que voce nao e um robo!\n");
        
        loop = 0;
        
    } else {
        
        printf("CAPTCHA digitado incorretamente, por favor tente novamente.\n");
        
    }
    
}


int main(void) {
    
    char valor[CAPTCHA], *retorno, digitado[CAPTCHA], copia[CAPTCHA + 1];
    
    while (loop == 1) {
        
        retorno = gerarCaptcha(valor);
        
        trasformarCaptcha(copia, retorno);
        
        printf("%s", retorno);
        
        printf("\nDigite a CAPTCHA: ");
        gets(digitado);
        
        comparaCaptcha(copia, digitado);
        
    }
    
    return 0;
    
}
