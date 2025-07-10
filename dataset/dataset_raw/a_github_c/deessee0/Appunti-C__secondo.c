#include <stdio.h>
#include <malloc.h>

struct elemento{ int info; struct elemento* next; };

typedef struct elemento ElementodiLista;
typedef ElementodiLista* ListadiElementi;

int main(void) 
{
    ListadiElementi lista = NULL; 
    int N = 10;

    
    ListadiElementi new = malloc(sizeof(ElementodiLista));
    (*new).info = 1;
    
    lista = new;

    for(int i = 2; i < N; i++)
    {
        
        (*new).next = malloc(sizeof(ElementodiLista));
        
        new = new->next;
        
        (*new).info = i;
    }

    new->next=NULL;
}

