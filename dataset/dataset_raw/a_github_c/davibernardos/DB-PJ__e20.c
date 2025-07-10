#include <stdio.h>
#include <stdlib.h>
#define TOTAL 6
#define bool int
#define TRUE 1
#define FALSE 0

struct Palavra {
    char nome[20];
    int tipo;
};
struct Palavra palavras[15];

int numeroAleatorio(int min, int max){
    int dif;
    max++;
    dif=max-min;
    return (rand()%dif)+min;
}
char * gerarCaptchaSimples(){
    
    int cont, tipo, min, max;
    char novoCaptcha[TOTAL], caractere;
    
    for(cont=0;cont<TOTAL;cont++){
        tipo=numeroAleatorio(1,3);
        
        switch(tipo){
            case 1:
                min=65;
                max=90;
            break;
            case 2:
                min=97;
                max=122;
            break;
            case 3:
                min=48;
                max=57;
            break;
        }
        
        caractere=numeroAleatorio(min,max);
        novoCaptcha[cont]=caractere;
        
    }
    novoCaptcha[TOTAL]=0;
    
    return novoCaptcha;
    
}
bool verificarCaptchaSimples(char stringA[TOTAL], char stringB[TOTAL]){
    if (strcmp(stringA,stringB)==0){
        return TRUE;
    } else {
        return FALSE;
    }   
}

char * gerarCaptchaMatematico(){
    
    int cont, tipo, caractere;
    char captcha[3];
    
    captcha[0]=numeroAleatorio(48,57);
    tipo=numeroAleatorio(1,2);
        switch(tipo){
            case 1:
                caractere=43;
            break;
            case 2:
                caractere=42;
            break;
        }
    captcha[1]=caractere;
    captcha[2]=numeroAleatorio(48,57);
    captcha[3]=0;
    
    return captcha;
    
}
int real(char caractere){
    int numero;
    
    switch(caractere){
        case 48:
        numero=0;
        break;
        case 49:
        numero=1;
        break;
        case 50:
        numero=2;
        break;
        case 51:
        numero=3;
        break;
        case 52:
        numero=4;
        break;
        case 53:
        numero=5;
        break;
        case 54:
        numero=6;
        break;
        case 55:
        numero=7;
        break;
        case 56:
        numero=8;
        break;
        case 57:
        numero=9;
        break;
    }
    return numero;
}
bool verificarCaptchaMatematico(char *conta, int resultado){
    
    int resultadoReal, valorA, valorB, simbolo;
    
    valorA=real(conta[0]);
    valorB=real(conta[2]);
    simbolo=conta[1];
    
    if (conta[1]==42){
        resultadoReal=valorA*valorB;
    } else {
        resultadoReal=valorA+valorB;
    }
    
    if (resultadoReal==resultado) {
        return TRUE;
    } else {
        return FALSE;
    }

}
char ** gerarCaptchaLogico(char verificador[7][20]){
    int tipo, cont, randPalavra, min, max, baseTipo;
    char novoCaptcha[7][20];
    
    for(cont=1;cont<6;cont++){
        tipo=numeroAleatorio(1,3);
        switch(tipo){
            case 1:
                min=0;
                max=4;
                break;
            case 2:
                min=5;
                max=9;
                break;
            case 3:
                min=10;
                max=14;
                break;
        }
        randPalavra=numeroAleatorio(min,max);
        strcpy(verificador[cont],palavras[randPalavra].nome);
    }
    
    baseTipo=buscaTipo(verificador[numeroAleatorio(1,5)]);
    switch(baseTipo){
        case 1:
            strcpy(verificador[0],"cor");
            strcpy(verificador[6],"1");
            break;
        case 2:
            strcpy(verificador[0],"animal");
            strcpy(verificador[6],"2");
            break;
        case 3:
            strcpy(verificador[0],"objeto");
            strcpy(verificador[6],"3");
            break;
    }
    
    return novoCaptcha;
}
int buscaTipo(char palavra[20]){
    int tipo, cont;
    
    for(cont=0;cont<15;cont++){
        if (strcmp(palavras[cont].nome,palavra)==0) {
            return palavras[cont].tipo;
            break;
        }
    }
    
    return FALSE;
}
bool verificarCaptchaLogico(char captcha[7][20],int alternativa){
    int tipo,numero;
    tipo=buscaTipo(captcha[alternativa]);
    numero=captcha[6][0]-48;
    
    if (tipo==numero) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int main() {
    char captcha[TOTAL], entrada[TOTAL], verificador[7][20];
    int verificacao, entradaNumerica, cont;
    
    strcpy(palavras[0].nome,"Amarelo");
    palavras[0].tipo=1;
    strcpy(palavras[1].nome,"Azul");
    palavras[1].tipo=1;
    strcpy(palavras[2].nome,"Roxo");
    palavras[2].tipo=1;
    strcpy(palavras[3].nome,"Verde");
    palavras[3].tipo=1;
    strcpy(palavras[4].nome,"Cinza");
    palavras[4].tipo=1;
    
    strcpy(palavras[5].nome,"Porco");
    palavras[5].tipo=2;
    strcpy(palavras[6].nome,"Cavalo");
    palavras[6].tipo=2;
    strcpy(palavras[7].nome,"Rato");
    palavras[7].tipo=2;
    strcpy(palavras[8].nome,"Cachorro");
    palavras[8].tipo=2;
    strcpy(palavras[9].nome,"Gato");
    palavras[9].tipo=2;
    
    strcpy(palavras[10].nome,"Garfo");
    palavras[10].tipo=3;
    strcpy(palavras[11].nome,"Faca");
    palavras[11].tipo=3;
    strcpy(palavras[12].nome,"Prato");
    palavras[12].tipo=3;
    strcpy(palavras[13].nome,"Copo");
    palavras[13].tipo=3;
    strcpy(palavras[14].nome,"Panela");
    palavras[14].tipo=3;
    
    srand(time(NULL));
    
    do {
        system("cls");
        strcpy(captcha,gerarCaptchaSimples());
        printf("\n%s",captcha);
        printf("\nDigite os caracteres da linha anetior: ");
        gets(entrada);
        verificacao=verificarCaptchaSimples(captcha,entrada);
        if (verificacao) {
            printf("\nCaptcha correto!\n");
        } else {
            printf("\nCaptcha incorreto!\n");
        }
        system("pause");
    }while(verificacao==FALSE);
    
    do{
        system("cls");
        strcpy(captcha,gerarCaptchaMatematico());
        printf("\n%s",captcha);
        printf("\nDigite o resultado da operacao anterior: ");
        scanf("%d",&entradaNumerica);
        verificacao=verificarCaptchaMatematico(captcha,entradaNumerica);
        if (verificacao) {
            printf("\nCaptcha correto!\n");
        } else {
            printf("\nCaptcha incorreto!\n");
        }
        system("pause");
    }while(verificacao==FALSE);
    
    do{
        system("cls");
        gerarCaptchaLogico(verificador);
        for(cont=1;cont<6;cont++){
            printf("\n%d - %s",cont,verificador[cont]);
        }
        printf("\nSelecione um(a) %s da lista anterior:",verificador[0]);
        scanf("%d",&entradaNumerica);
        while(entradaNumerica<1 || entradaNumerica>5){
            printf("\nOpcao invalida. Digite novamente: ");
            scanf("%d",&entradaNumerica);
        }
        verificacao=verificarCaptchaLogico(verificador,entradaNumerica);
        if (verificacao) {
            printf("\nCaptcha correto!\n");
        } else {
            printf("\nCaptcha incorreto!\n");
        }
        system("pause");
    }while(verificacao==FALSE);

}

