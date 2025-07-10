#include <stdio.h>
#include <stdlib.h>

typedef enum Bool
{
    false, true

} bool;

typedef struct Ponto
{
    double x;
    double y;

} ponto_t;

typedef struct Retangulo
{
    ponto_t sup_esq;
    ponto_t inf_dir;

} rect_t;

void le_retangulo(rect_t *retangulo)
{
    printf("\nDigite as coordenadas do retângulo:\n");
    
    printf("\n\tPonto superior esquerdo:\n");
    printf("\t-> Coordenada x: ");
    scanf("%lf", &retangulo->sup_esq.x);
    getchar();
    printf("\t-> Coordenada y: ");
    scanf("%lf", &retangulo->sup_esq.y);
    getchar();

    printf("\n\tPonto inferior direito:\n");
    printf("\t-> Coordenada x: ");
    scanf("%lf", &retangulo->inf_dir.x);
    getchar();
    printf("\t-> Coordenada y: ");
    scanf("%lf", &retangulo->inf_dir.y);
    getchar();
}

void le_retangulos(rect_t *retangulo_1, rect_t *retangulo_2)
{
    printf("\nDigite as coordenadas do 1º retângulo:\n");
    
    printf("\n\tPonto superior esquerdo:\n");
    printf("\t-> Coordenada x: ");
    scanf("%lf", &retangulo_1->sup_esq.x);
    getchar();
    printf("\t-> Coordenada y: ");
    scanf("%lf", &retangulo_1->sup_esq.y);
    getchar();

    printf("\n\tPonto inferior direito:\n");
    printf("\t-> Coordenada x: ");
    scanf("%lf", &retangulo_1->inf_dir.x);
    getchar();
    printf("\t-> Coordenada y: ");
    scanf("%lf", &retangulo_1->inf_dir.y);
    getchar();

    printf("\nDigite as coordenadas do 2º retângulo:\n");
    
    printf("\n\tPonto superior esquerdo:\n");
    printf("\t-> Coordenada x: ");
    scanf("%lf", &retangulo_2->sup_esq.x);
    getchar();
    printf("\t-> Coordenada y: ");
    scanf("%lf", &retangulo_2->sup_esq.y);
    getchar();

    printf("\n\tPonto inferior direito:\n");
    printf("\t-> Coordenada x: ");
    scanf("%lf", &retangulo_2->inf_dir.x);
    getchar();
    printf("\t-> Coordenada y: ");
    scanf("%lf", &retangulo_2->inf_dir.y);
    getchar();
}

double area(rect_t retangulo)
{
    double area = (retangulo.sup_esq.x - retangulo.inf_dir.x) * (retangulo.sup_esq.y - retangulo.inf_dir.y);

    return (area < 0) ? area*(-1) : area;
}

bool intersecao(rect_t retangulo_1, rect_t retangulo_2)
{
    bool sup_esq = false, inf_dir = false;

    if ((((retangulo_2.sup_esq.x > retangulo_1.sup_esq.x) && (retangulo_2.sup_esq.x < retangulo_1.inf_dir.x)) || ((retangulo_2.sup_esq.y < retangulo_1.sup_esq.y) && (retangulo_2.sup_esq.y > retangulo_1.inf_dir.y))) == true)
    {
        sup_esq = true;
    }

    if ((((retangulo_2.inf_dir.x < retangulo_1.inf_dir.x) && (retangulo_2.inf_dir.x > retangulo_1.sup_esq.x)) || ((retangulo_2.inf_dir.y > retangulo_1.inf_dir.y) && (retangulo_2.inf_dir.y < retangulo_1.sup_esq.y))) == true)
    {
        inf_dir = true;
    }

    if ((sup_esq || inf_dir) == true)
    {
        return true;
    }

    else return false;
}

int contido(rect_t retangulo_1, rect_t retangulo_2)
{
    if (((retangulo_2.sup_esq.x > retangulo_1.sup_esq.x && retangulo_2.sup_esq.x < retangulo_1.inf_dir.x) && (retangulo_2.sup_esq.y < retangulo_1.sup_esq.y && retangulo_2.sup_esq.y > retangulo_1.inf_dir.y)) &&\
        ((retangulo_2.inf_dir.x < retangulo_1.inf_dir.x && retangulo_2.inf_dir.x > retangulo_1.sup_esq.x) && (retangulo_2.inf_dir.y > retangulo_1.inf_dir.y && retangulo_2.inf_dir.y < retangulo_1.sup_esq.y)) == true)
    {
        return 2;
    }

    else if (((retangulo_1.sup_esq.x > retangulo_2.sup_esq.x && retangulo_1.sup_esq.x < retangulo_2.inf_dir.x) && (retangulo_1.sup_esq.y < retangulo_2.sup_esq.y && retangulo_1.sup_esq.y > retangulo_2.inf_dir.y)) &&\
             ((retangulo_1.inf_dir.x < retangulo_2.inf_dir.x && retangulo_1.inf_dir.x > retangulo_2.sup_esq.x) && (retangulo_1.inf_dir.y > retangulo_2.inf_dir.y && retangulo_1.inf_dir.y < retangulo_2.sup_esq.y)) == true)
    {
        return 1;
    }

    else if (((retangulo_1.sup_esq.x == retangulo_2.sup_esq.x && retangulo_1.sup_esq.y == retangulo_2.sup_esq.y) && (retangulo_1.inf_dir.x == retangulo_2.inf_dir.x && retangulo_1.inf_dir.y == retangulo_2.inf_dir.y)) == true)
    {
        return 3;
    }

    else return 0;
}

double intersecao_area(rect_t retangulo_1, rect_t retangulo_2)
{
    rect_t retangulo;

    if (retangulo_2.sup_esq.x >= retangulo_1.sup_esq.x && retangulo_2.sup_esq.x <= retangulo_1.inf_dir.x)
    {
        retangulo.sup_esq.x = retangulo_2.sup_esq.x;
    }

    else retangulo.sup_esq.x = retangulo_1.sup_esq.x;

    if (retangulo_2.sup_esq.y <= retangulo_1.sup_esq.y && retangulo_2.sup_esq.y >= retangulo_1.inf_dir.y)
    {
        retangulo.sup_esq.y = retangulo_2.sup_esq.y;
    }

    else retangulo.sup_esq.y = retangulo_1.sup_esq.y;

    if (retangulo_2.inf_dir.x <= retangulo_1.inf_dir.x && retangulo_2.inf_dir.x >= retangulo_1.sup_esq.x)
    {
        retangulo.inf_dir.x = retangulo_2.inf_dir.x;
    }

    else retangulo.inf_dir.x = retangulo_1.inf_dir.x;

    if (retangulo_2.inf_dir.y >= retangulo_1.inf_dir.y && retangulo_2.inf_dir.y <= retangulo_1.sup_esq.y)
    {
        retangulo.inf_dir.y = retangulo_2.inf_dir.y;
    }

    else retangulo.inf_dir.y = retangulo_1.inf_dir.y;

    printf("\nsup_esq (%lf,%lf)\ninf_dir(%lf,%lf)\n", retangulo.sup_esq.x, retangulo.sup_esq.y, retangulo.inf_dir.x, retangulo.inf_dir.y);
    
    return area(retangulo);
}


int main()
{
    rect_t retangulo_1, retangulo_2;
    int escolha;

    do
    {
        do
        {
            printf("\n\t(1) Calcular a área de um retângulo\n");
            printf("\t(2) Verificar interseção de retangulos\n");
            printf("\t(3) Verificar se um retângulo está contido em um outro\n");
            printf("\t(4) Calcular a área da interseção entre dois retangulos\n");
            printf("\t(5) Sair\n");
            printf("\n\tDigite sua escolha: ");
            scanf("%i", &escolha);
            getchar();

            if (escolha < 1 || escolha > 5) system("clear");

        } while (escolha < 1 || escolha > 5);

        switch (escolha)
        {
            case 1:
                le_retangulo(&retangulo_1);
                printf("\nÁrea = %lf\n", area(retangulo_1));
                break;
            
            case 2:
                le_retangulos(&retangulo_1, &retangulo_2);

                if ((intersecao(retangulo_1, retangulo_2) || intersecao(retangulo_2, retangulo_1)) == true)
                {
                    printf("\nOs retângulos dados se intersectam!\n");
                }

                else printf("\nOs retângulos dados não se intersectam!\n");

                break;

            case 3:
                le_retangulos(&retangulo_1, &retangulo_2);

                switch (contido(retangulo_1, retangulo_2))
                {
                    case 1:
                        printf("\nO retângulo 1 está contido no retângulo 2\n");
                        break;

                    case 2:
                        printf("\nO retângulo 2 está contido no retângulo 1\n");
                        break;
                    
                    case 3:
                        printf("\nOs retângulos são identicos\n");
                        break;
                    
                    case 0:
                        printf("\nNenhum retângulo está contido no outro\n");
                        break;
                }

                break;

            case 4:
                le_retangulos(&retangulo_1, &retangulo_2);

                if ((intersecao(retangulo_1, retangulo_2) || intersecao(retangulo_2, retangulo_1)) == false)
                {
                    printf("\nOs retângulos dados não se intersectam!\n");
                }

                else
                {
                    printf("\nÁrea da interseção = %lf\n", intersecao_area(retangulo_1, retangulo_2));
                }

                break;
            
            case 5:
                return 0;
        }

        printf("\nPressione ENTER para continuar: ");
        getchar();
        system("clear");
    
    } while (escolha != 5);

    return 0;

}