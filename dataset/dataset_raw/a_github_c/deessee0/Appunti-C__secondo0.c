#include <stdio.h>
#include <malloc.h>

struct elemento{ int info; struct elemento* next; };

typedef struct elemento ElementodiLista;
typedef ElementodiLista* ListadiElementi;

int main(void) 
{
    
  
    return 0;
}

void inserisci(ListadiElementi *l, int x, int v)
{
    ListadiElementi prec, corr;

    corr = *l;
    int trovato = 0;
    prec = NULL;

    while(corr != NULL && !trovato)
    {
        if(corr->info == x) trovato = 1;
        else
        {
            prec = corr;
            corr = corr->next;
        }
    }

    if(trovato)
    {
        ListadiElementi new = malloc(sizeof(ElementodiLista));
        new->info = v;   
        new->next = corr;

        if(prec != NULL) prec->next = new;
        else *l = new;
    }
}

