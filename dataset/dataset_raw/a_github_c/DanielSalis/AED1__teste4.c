#include<stdio.h>
#include<stdlib.h>


typedef struct elemento{
    int IDcidade;
    int distancia;
    struct elemento* ant;
    struct elemento* prox;
}TipoElemento;

typedef struct lista_dinamica{
    TipoElemento* primeiro;
    TipoElemento* ultimo;
    int tamanho;
}TipoLista;

void iniciarLista(TipoLista* l){
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->tamanho = 0;
}

int existeNaLista(TipoLista*l, int IDcidade){
    TipoElemento* aux = l->primeiro;
    while(aux!=NULL){
        if(aux->IDcidade == IDcidade){
            return 1;
        }
        aux = aux->prox;
    }

    return 0;
}

void inserir(TipoLista*l , int IDcidade, int distancia){
    TipoElemento* novoElemento = (TipoElemento*)malloc(sizeof(TipoElemento));
    novoElemento->IDcidade = IDcidade;
    novoElemento->distancia = distancia;

    if(l->tamanho == 0){
        l->primeiro = novoElemento;
        l->ultimo = novoElemento;
        novoElemento->prox = NULL;
        novoElemento->ant = NULL;               
    }else{
        l->ultimo->prox = novoElemento;
        novoElemento->ant = l->ultimo;
        l->ultimo = novoElemento;
        novoElemento->prox = NULL;
    }
    l->tamanho++;
}

int jaPercorri(TipoLista*l ,int IDcidade){
    int existe = existeNaLista(l, IDcidade);
    if(existe){
        int somaDistancia = 0;
        int contCidades = 0;
        
        TipoElemento* aux = l->primeiro;
        
        while(aux->IDcidade != IDcidade){
            somaDistancia = somaDistancia + aux->distancia;
            contCidades++;
            aux = aux->prox;
        }

        printf("estou na cidade %d:\n", IDcidade);
        printf("ja percorri %d km, passando por %d cidades", somaDistancia, contCidades);
        return 1;
    }else{
        printf("cidade nao existe no percurso");
        return 0;
    }
}

int faltamPercorrer(TipoLista*l, int IDcidade){
    int existe = existeNaLista(l, IDcidade);
    int Distancia = 0;
    int contCidades=1;
    
    if(existe){
        TipoElemento* aux = l->ultimo;
        
        while(aux->IDcidade != IDcidade){
            Distancia = Distancia + aux->distancia;
            contCidades++;
            aux = aux->ant;
        }
        Distancia = Distancia + aux->distancia;
        aux = aux->ant;

        printf("estou na cidade %d:\n", IDcidade);
        printf("faltam percorrer %d km, passando por %d cidades", Distancia, contCidades-1);
        return 1;
    }else{
        printf("cidade nao existe no percurso");
        return 0;
    }
}

void calculaTrajetoTotal(TipoLista* l){
    int distanciaTotal = 0;
    int contCidades=0;
    TipoElemento* aux = l->primeiro;

    while(aux!=NULL){
        distanciaTotal = distanciaTotal + aux->distancia;
        contCidades++;
        aux = aux->prox;
    }
    printf("o trajeto total tem %d kms, passando\n", distanciaTotal);
    printf("por %d cidades\n", contCidades);
}

int main(){
    int flag;
    int op = 1;
    int IDcidade;
    int distancia;

    TipoLista lista;
    iniciarLista(&lista);

    while(op==1){
        scanf("%d", &op);
        

        
        if(op==1){
            scanf("%d %d", &IDcidade, &distancia);
            inserir(&lista, IDcidade, distancia);
        }

            else if(distancia != 0){
                printf("trajeto invalido");
                return 0;
            }
            
        
        else if(op==2){
            scanf("%d", &IDcidade);
            flag = jaPercorri(&lista, IDcidade);
            if(flag==0){
                break;
            }
        }

        
        else if(op==3){
            scanf("%d", &IDcidade);
            flag = faltamPercorrer(&lista, IDcidade);
            if(flag==0){
                break;
            }
        }

        
        else if(op==4){
            calculaTrajetoTotal(&lista);
            break;
        }

        else{
            printf("opcao invalida");
            break;
        }
    }
    return 0;    
}