#include <stdio.h>
#include <malloc.h>

struct elemento{ int info; struct elemento* next; };

typedef struct elemento ElementodiLista;
typedef ElementodiLista* ListadiElementi;

void addT(ListadiElementi* l, int x)
{
    ListadiElementi new = malloc(sizeof(ElementodiLista));
    new->info = x;
    new->next = *l;
    *l = new;
}

void addC(ListadiElementi* l, int x)
{
    
    ListadiElementi new = malloc(sizeof(ElementodiLista));
    (*new).info = x;
    (*new).next = NULL;
    
    if(*l == NULL) *l = new;
    else 
    {
        
        ListadiElementi corr = *l;
        
        while(corr->next != NULL) corr = corr->next;
        
        corr->next = new;
    }
}

int main(void) 
{
    ListadiElementi lista = NULL;
    
    addT(&lista , 2);
    addT(&lista, 3);
    addC(&lista, 1);
    
}

