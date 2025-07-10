

#include <stdio.h>
#include <stdlib.h>

int main()

{

    float maior_tam_aluno = 0;
    int num_maior_aluno = 0;

    float menor_tam_aluno = 100000;
    int num_menor_aluno = 0;

    int num_aluno[3];
    float altura_aluno[3];
    int i;
    int j = 0;

    for(i = 0; i <3; i++){



            printf("Digite o numero do aluno %d: ",i);
            scanf("%d",&num_aluno[i]);

            printf("Digite a altura do aluno %d: ",j);
            scanf("%f",&altura_aluno[i]);



        }
            for(j = 0; j <3; j++){

            if(altura_aluno[j] > maior_tam_aluno){

                maior_tam_aluno = altura_aluno[j];
                num_maior_aluno = num_aluno[j];
            }

            if(altura_aluno[j] < menor_tam_aluno){
                menor_tam_aluno = altura_aluno[j];
                num_menor_aluno = num_aluno[j];
            }



    }

    printf("\n O maior aluno eh: %d %.2f \n",num_maior_aluno, maior_tam_aluno);
    printf("\n O menor aluno eh: %d %.2f \n",num_menor_aluno, menor_tam_aluno);



    system("PAUSE");
    return 0;
}
