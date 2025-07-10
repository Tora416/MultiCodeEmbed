#include<stdio.h>
#include<stdlib.h>

typedef struct elemento{
    char nome;
    int agilidade;
    struct elemento* prox;
    struct elemento* ant;
}TipoElemento;

typedef struct listaCircular{
    TipoElemento* primeiro;
    int tamanho;
}TipoLista;

void iniciarLista(TipoLista* l){
    l->primeiro = NULL;
    l->tamanho = 0;
}

void inserirFim(TipoLista* l, char nome, int agilidade){
    TipoElemento* novoElemento = (TipoElemento*)malloc(sizeof(TipoElemento));
    novoElemento->nome = nome;
    novoElemento->agilidade = agilidade;

    if(l->tamanho == 0){
        novoElemento->prox = novoElemento;
        novoElemento->ant = novoElemento;
        l->primeiro = novoElemento;
        l->tamanho++;
    }else{
        novoElemento->prox = l->primeiro;
        novoElemento->ant = l->primeiro->ant;
        l->primeiro->ant->prox = novoElemento;
        l->primeiro->ant = novoElemento;
        l->tamanho++;
    }
}

int existeNaLista(TipoLista *l, char nome){
  int contador = l->tamanho;

  if(contador == 0)
    return 1;

  TipoElemento *p = l->primeiro;

  while(contador != 0)
  {
    if(p->nome == nome)
      return 2;

    p = p->prox;
    contador--;
  }
  return 1;
}

int existeNaListaII(TipoLista *l, char nome)
{
  int contador = l->tamanho;

  if(contador == 0)
    return 2;

  TipoElemento *p = l->primeiro;

  while(contador != 0)
  {
    if(p->nome == nome)
      return 1;

    p = p->prox;
    contador--;
  }
  return 3;
}

void imprimeLista(TipoLista* l){
  TipoElemento *aux = l->primeiro;
  int cont = 0;

  while(cont != l->tamanho){
    if(cont == 0)
      printf("| ");
    
    printf("soldado: %c ", aux->nome);
    aux = aux->prox;
    cont++;
    
    if(cont != l->tamanho)
      printf("-> ");
    
    else
      printf("|");
  }
}


void sortear(TipoLista *l, char nome){
  int rodada = 1;
  char nomeAux = nome;

  while(l->tamanho != 1){

    int contador = rand() % 10;
    int contadorAux = contador;

    TipoElemento *p = l->primeiro;

    printf("-> rodada %d: soldado %c, contagem %d\n", rodada, nomeAux, contador);

    while(p->nome != nomeAux){
      p = p->prox;
    }
    while(contadorAux != 0){
      p = p->prox;
      contadorAux--;
      nomeAux = p->nome;
    }

    imprimeLista(l);
    printf("\nremovido: soldado %c\n", nomeAux);

    if(p == l->primeiro){
      l->primeiro = p->prox;
    }
    nomeAux = p->prox->nome;
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    p = NULL;
    free(p);
    l->tamanho--;
    rodada++;

  }
  TipoElemento *n = l->primeiro;
  if(n->agilidade < 7)
    printf("soldado %c escolhido - ele nao tem agilidade suficiente -> vamos morrer!!", n->nome);
  else
    printf("soldado %c escolhido e vai nos salvar!",n->nome);

}

int main(){

    int op;
    int agilidade;
    int existe;
    char nome;

    TipoLista lista;
    iniciarLista(&lista);

    scanf("%d", &op);

    while(op==1){
        scanf(" %c %d", &nome, &agilidade);
        existe = existeNaLista(&lista, nome);
        
        if(existe == 1)
           inserirFim(&lista, nome, agilidade);
        
        else
            printf("soldado nao pode ser inserido duas vezes\n");
        
        scanf("%d", &op);
    }

    if(op == 2){
        scanf(" %c", &nome);
        existe = existeNaListaII(&lista, nome); 
        
        if(existe == 1){
            printf("|| sorteio iniciado ||\n");
            sortear(&lista, nome);
        }
        else{
            if(existe == 2)
                printf("grupo vazio");
            
            else
                printf("soldado nao pertence ao grupo");
        }
    }
    return 0;
}