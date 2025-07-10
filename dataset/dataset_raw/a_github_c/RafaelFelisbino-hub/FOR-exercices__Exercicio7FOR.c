#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <ctype.h>

int main() 
{
    float altura = 0,maioralt = 0,menoralt = 999,mediamulher = 0,mediaalt = 0,maiorhomem = 0,menorhomem = 999,quantF = 0;
    char sexo;
    int i;

    system("color 17");

    for (i = 0; i < 4; i++) 
    {
        
        printf("Digite sua altura separado por ponto:Ex: 1.00  ");
        scanf_s("%f", &altura);
        (void)getchar();
        

        printf("Digite seu sexo: M ou F:  ");
        scanf_s("%c", &sexo,1);
        sexo = toupper(sexo);
        
        if (altura < menoralt) 
        {
            menoralt = altura;
        }
        if (altura > maioralt) 
        {
            maioralt = altura;
        }

        if (sexo == 'F') 
        {
            quantF++;
            mediamulher += altura;
        }

        if (sexo == 'M' && altura < menorhomem) 
        {
            menorhomem = altura;
        }
        if (sexo == 'M' && altura > maiorhomem)
        {
            maiorhomem = altura;
        }

        mediaalt += altura;
    }
    
    if (mediamulher != 0)
    {
        mediamulher = mediamulher / quantF;
    }
    
    mediaalt = mediaalt / i;
    
    printf("\n\n");
    printf("A maior altura da turma e:  %.2f\n", maioralt);
    printf("A maior altura da turma e:  %.2f\n", menoralt);
    printf("A media de altura das mulheres e:  %.2f\n", mediamulher);
    printf("A maior altura dos homens e:  %.2f\n", maiorhomem);
    printf("A menor altura dos homens e:  %.2f\n", menorhomem);
    printf("A media de altura da turma e:  %.2f\n", mediaalt);




}