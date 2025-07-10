#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM 6





char validarDados (char vetorUsuario[TAM])
{
    int resultado = 0;
    
    if (strlen(vetorUsuario) > TAM)
    {
        system ("COLOR C");
        printf ("\n\nERRO! Caracteres digitados em excesso. Tente novamente.");
        sleep(3);
        resultado = 1;
        system("cls");
    }
    return resultado;
}



char compararCaptcha (char vetorCaptcha[TAM], char vetorUsuario[TAM])
{
    int resultado;
    
    resultado = strcmp (vetorCaptcha, vetorUsuario);
    return resultado;
}



int exibirResultado (int comparacao)
{
    if (comparacao == 0)
    {
        printf ("\n\nCaracteres digitados corretamente!");
    }else
    {
        system ("COLOR C");
        printf ("\n\nERRO! Caracteres digitados de forma incorreta. Tente novamente.\n\n");
        sleep(3);
        comparacao = 1;
        system("cls");
    }
    return comparacao;
}



int main(int argc, char *argv[]) {
    char vetorCaptcha[TAM];
    char vetorUsuario[TAM];
    int captcha;
    int validacaoDados;
    int comparacao;
    int resultado;
    int cont;
    
    srand(time(NULL));
    do 
    {
        system ("COLOR F");
        system ("cls");
        printf ("Teste de Turing.\n\n");
        for (cont = 0; cont < 6; cont++)
        {
            do
            {
                captcha = (rand() % 122);
            }
            while (captcha <= 48 || captcha >= 57 && captcha <= 97 || captcha >= 122);
            vetorCaptcha[cont] = captcha;
            printf ("%c ", vetorCaptcha[cont]);
        }
        system ("COLOR F");
        printf ("\n\nDigite os caracteres acima: ");
        gets(vetorUsuario);
        validacaoDados = validarDados (vetorUsuario);
        if (validacaoDados == 0)
        {
            comparacao = compararCaptcha (vetorCaptcha, vetorUsuario);
            resultado = exibirResultado (comparacao);
            if (resultado == 1)
            {
                validacaoDados = resultado;
                printf ("%d", validacaoDados);
            }   
        }
    }
    while (validacaoDados != 0);
    return 0;
}
