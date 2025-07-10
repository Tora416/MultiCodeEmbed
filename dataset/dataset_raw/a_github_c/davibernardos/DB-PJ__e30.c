#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CAPTCHA 6


char * gerarCaptcha( char captchaSistema[CAPTCHA]){
    int cont, guardaValor, aleatorio[CAPTCHA], geradorCaptcha[CAPTCHA];
    srand(time(NULL));
    for (cont = 0;cont < CAPTCHA; cont++){
        guardaValor = rand();
        aleatorio[cont] = (guardaValor % 122);
        if((aleatorio[cont] >= 48 && aleatorio[cont] <= 57) || (aleatorio[cont] >= 65 && aleatorio[cont] <= 90) || (aleatorio[cont] >= 97 && aleatorio[cont] <= 122) ){
            captchaSistema[cont] = aleatorio[cont];
        }
        else{
            cont--;
        }
    }
    return captchaSistema;
}
int confirmacaoCaptcha(char *atribuicao, char captchaDigitado[CAPTCHA]){
    int comparaDigitado;
    comparaDigitado = strcmp(atribuicao, captchaDigitado);
    return comparaDigitado;
}

int main(int argc, char *argv[]) {
    char captchaDigitado[CAPTCHA], captchaSistema[CAPTCHA], *atribuicao;
    int comparaDigitado;
    do{
        atribuicao = gerarCaptcha(captchaSistema);
        printf("%s", atribuicao);
        printf("\nDigite o captcha para provar q nao e um robo\n");
        gets(captchaDigitado);
        comparaDigitado = confirmacaoCaptcha(atribuicao, captchaDigitado);
        if(comparaDigitado == 0){
            printf("\nSao iguais!! Voce nao e um robo\n");
        }
        else if(comparaDigitado < 0 || comparaDigitado > 0){
            printf("\nCaptcha errado, um novo sera redefinido\n");
        }

    }while(comparaDigitado < 0 || comparaDigitado > 0);

    return 0;
}
