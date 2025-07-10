#include <stdio.h>
#include <stdlib.h>




char gerarCaptcha[6];

char gerado()
{
    int cont=0;
    int num=0;
    
    srand(time(NULL));
    while(cont<6)
    {
        if (cont == 4 || cont == 5)
        {
            gerarCaptcha[cont] = 48 + rand() % 9;
        }
        else if(cont == 1 || cont == 3)
        {
            gerarCaptcha[cont] = 97 + rand() % 26;
        }
        else if(cont == 0 || cont == 2)
        {
            gerarCaptcha[cont] = 65 + rand() % 26;
        }

        cont++;
    }
    
    
    printf("%s\n", gerarCaptcha);
}


int main(int argc, char *argv[]) {
    
    char captchaDigitado[6];
    int continuar = 1;
    
    while(continuar = 1)
    {
        printf("CAPTCHA\n\n");
        printf("Captcha gerado:\n");
        gerado();
        printf("\n");
        printf("Digite o Captcha gerado:\n");
        gets(captchaDigitado);
        printf("\n");
        
        if(strcmp (captchaDigitado, gerarCaptcha) == 0)
        {
            printf("Captcha correto.\n\n");
        }else{
            printf("Captcha incorreto.\n\n");
        }
        system("pause");
        system("cls");
    }
    
    
    return 0;
}
