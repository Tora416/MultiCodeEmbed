#include <stdio.h>
#include <stdlib.h>



char * gerarCaptcha(char captcha[6])
{
    int cont, num;
    srand(time(NULL));

    for(cont = 0; cont < 6; cont++)
    {
        num = rand() % 3;
        
        if(num == 0)
            captcha[cont] = 65 + (rand() % 26);
        else
            if(num == 1)
                captcha[cont] = 97 + (rand() % 26);
            else
                captcha[cont] = 48 + (rand() % 10);
    }
    return captcha;
}
int * compararCaptcha(char captcha[6], char vetor[6], int iguais)
{
    int cont;
    iguais = 0;
    
    for(cont = 0; cont < 6; cont++)
    {
        if(captcha[cont] == vetor[cont])
            iguais++;
    }
    
    if(iguais == 6)
        return iguais;
}
   
int main(int argc, char *argv[]) 
{
    char captcha[6];
    char vetor[6];
    int * retorno, * comparacao, cont;
    int iguais;
    
    printf("Verificacao de Seguranca.\n\n");
    retorno = gerarCaptcha(captcha);
    printf("%s\n", retorno);
    printf("\nEscreva os 6 caracteres que voce ve acima: \n");
    gets(vetor);
    
    comparacao = compararCaptcha(captcha, vetor, iguais);
    printf("", comparacao);
    
    iguais = 0;
    
    if(comparacao == 6)
        printf("\nOs caracteres sao iguais!\n");
    else
    {
        printf("\nOs caracteres sao diferentes. Tente novamente.\n");
        
        while(comparacao != 6)
        {
            retorno = gerarCaptcha(captcha);
            printf("%s\n", retorno);
            printf("\nEscreva os 6 caracteres que voce ve acima: \n");
            gets(vetor);
            
            for(cont = 0; cont < 6; cont++)
            {
                if(captcha[cont] == vetor[cont])
                iguais++;
            }
            
            comparacao = iguais;
            
            if(comparacao == 6)
            {
                printf("\nOs caracteres sao iguais!\n");
                break;
            }
            else
            {
                printf("\nOs caracteres sao diferentes. Tente novamente.\n");
            }
        }
    }
    return 0;
}
