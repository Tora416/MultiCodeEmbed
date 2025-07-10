#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    int id;
    struct elemento* prox;
}TipoElemento;

typedef struct fila{
    TipoElemento* primeiro;
    TipoElemento* ultimo;
    int tamanho;
    int tamMod;
}TipoLista;

void iniciarLista(TipoLista* l){
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->tamanho = 0;
    l->tamMod = 0;
}

void remover(TipoLista* l){
    if(l->tamanho == 0){
        printf("lista vazia\n");
    }else{
        TipoElemento* aux = l->primeiro;
        l->primeiro = l->primeiro->prox;
        free(aux);
        l->tamanho--;
    }
}

int existeNalista(TipoLista* l, int id){
    TipoElemento* aux = l->primeiro;
    while(aux!=NULL){
        if(aux->id == id){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void inserir(TipoLista* l, int id){
    TipoElemento* novoElemento = (TipoElemento*)malloc(sizeof(TipoElemento));
    novoElemento->id = id;

    if(existeNalista(l, id) == 1){
        printf("processo ja esta na fila\n"); 
    }
    else{
        if(l->tamanho == 0){
            l->primeiro = novoElemento;
            l->ultimo = novoElemento;
            novoElemento->prox = NULL;
            l->tamanho++;
            l->tamMod++;
        }else{
            l->ultimo->prox = novoElemento;
            l->ultimo = novoElemento;
            novoElemento->prox = NULL;
            l->tamanho++;
            l->tamMod++;
        }
        
        if(l->tamMod == 3){
            printf("removendo processo %d em espera a muito tempo...\n", l->primeiro->id); 
            remover(l);
            l->tamMod = 0;
        }
    }
        
}

void imprimir(TipoLista* l){

    
    if(l->tamanho == 0){
        printf("lista vazia\n");
    }

    else{
        TipoElemento* aux = l->primeiro;
        TipoElemento* auxProx = l->primeiro->prox;
        printf("| ");
        
        while(auxProx){
            printf("%d -> ", aux->id);
            aux = auxProx;
            if(auxProx==NULL){
                break;
            }
            auxProx = auxProx->prox;
        }
        printf("%d |\n", aux->id);
    }
}

int main(){
    int op;
    int IDprocesso;
    TipoLista lista;

    iniciarLista(&lista);
    
    while(op != -1){
        scanf("%d", &op);

        if(op == -1){
            break;
        }
        
        if(op == 1){
            scanf("%d", &IDprocesso); 
            inserir(&lista, IDprocesso);
        }

        else if(op == 2){
            remover(&lista);
        }

        else if(op == 3){
            imprimir(&lista);
        }

        else{
            printf("opcao invalida\n");
            break;
        }
    }
    
    return 0;
}