#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define logico int
#define TRUE 1
#define FALSE 0



char captchaLido[6];
char captchaGerado[6];

char * gerarCaptcha (char captchaGerado[6]) {

    int contadorLetras;
    int padraoCaptcha;

    padraoCaptcha = rand() % 3;
    switch (padraoCaptcha) {

        case 0: {
            for (contadorLetras=0; contadorLetras < 6 ; contadorLetras++) {
                if(contadorLetras == 0 || contadorLetras == 3) {
                    captchaGerado[contadorLetras] = 65 + (rand() % 26);
                } else {
                    if(contadorLetras == 1 || contadorLetras == 4) {
                        captchaGerado[contadorLetras] = 48 + (rand() % 10);
                    } else {
                        if(contadorLetras == 2 || contadorLetras == 5 ) {
                            captchaGerado[contadorLetras] = 97 + (rand() % 26);
                        }
                    }
                }
            }
            break;
        }
        case 1: {
            for (contadorLetras=0; contadorLetras < 6 ; contadorLetras++) {
                if(contadorLetras == 1 || contadorLetras == 3) {
                    captchaGerado[contadorLetras] = 65 + (rand() % 26);
                } else {
                    if(contadorLetras == 0 || contadorLetras == 5) {
                        captchaGerado[contadorLetras] = 48 + (rand() % 10);
                    } else {
                        if(contadorLetras == 2 || contadorLetras == 4 ) {
                            captchaGerado[contadorLetras] = 97 + (rand() % 26);
                        }
                    }
                }
            }
            break;
        }
        case 2: {
            for (contadorLetras=0; contadorLetras < 6 ; contadorLetras++) {
                if(contadorLetras == 0 || contadorLetras == 5) {
                    captchaGerado[contadorLetras] = 65 + (rand() % 26);
                } else {
                    if(contadorLetras == 2 || contadorLetras == 3) {
                        captchaGerado[contadorLetras] = 48 + (rand() % 10);
                    } else {
                        if(contadorLetras == 1 || contadorLetras == 4 ) {
                            captchaGerado[contadorLetras] = 97 + (rand() % 26);
                        }
                    }
                }
            }
            break;
        }
    }
    return captchaGerado;
}

logico validarCaptcha ( char captchaLido[6], char captchaGerado [6]) {
    int contador, contIguais;

    contIguais=0;
    for (contador=0; contador<6; contador++) {
        if( captchaLido[contador] == captchaGerado[contador]) {
            contIguais++;
        } else {
            contIguais = 0;
            break;
        }
    }

    if ( contIguais == 6) {
        return TRUE;
    } else {
        if(contIguais == 0) {
            return FALSE;
        }
    }
}

int main(int argc, char *argv[]) {
    char novamente;
    char *captcha;
    logico result;

    srand(time(NULL));


    do {
        novamente = 'N';
        captcha = gerarCaptcha(captchaGerado);
        printf(" --Por Favor, digite o CAPTCHA abaixo, respeitando maiusculas e minusculas:\n\n   %s  \n\n", captcha);
        gets(captchaLido);

        result = validarCaptcha ( captchaLido , captcha);

        if(result == TRUE) {
            printf("   --Captcha Correto! Acesso Permitido!");
        } else {
            if (result == FALSE) {
                printf(" --Voce nao digitou o Captcha corretamente. Por favor, tente novamente.\n\n");
                novamente = 'S';
            }
        }

    } while (novamente == 'S');


    return 0;
}
