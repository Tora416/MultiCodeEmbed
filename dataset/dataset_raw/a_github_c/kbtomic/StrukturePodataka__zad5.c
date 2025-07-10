#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

typedef struct lista* pozicija;
struct lista {
    int el;
    pozicija next;
};
int unija(pozicija, pozicija, pozicija);
int presjek(pozicija, pozicija, pozicija);
int unosPrvi(pozicija);
int unosDrugi(pozicija);
int ispis(pozicija);
int main()
{
    struct lista Head1;
    struct lista Head2;
    struct lista HeadU;
    struct lista HeadP;
    Head1.next = NULL;
    Head2.next = NULL;
    HeadU.next = NULL;
    HeadP.next = NULL;
    unosPrvi(&Head1);
    unosDrugi(&Head2);
    printf("Prva lista:\n");
    ispis(Head1.next);
    printf("Druga lista:\n");
    ispis(Head2.next);
    unija(&Head1, &Head2, &HeadU);
    printf("Ispis unije listi:\n");
    ispis(HeadU.next);
    presjek(&Head1, &Head2, &HeadP);
    printf("Ispis presjeka listi:\n");
    ispis(HeadP.next);

    return 0;
}
int unija(pozicija p, pozicija q, pozicija r)
{
    while (p->next != NULL && q->next != NULL)
    {
        pozicija s = NULL;
        s = (pozicija)malloc(sizeof(struct lista));
        if (s == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return 1;
        }
        s->next = NULL;
        if (p->next->el == q->next->el) 
        {
            s->el = p->next->el;
            p = p->next;
            q = q->next;
        }
        else if(p->next->el < q->next->el) 
        {
            s->el = p->next->el;
            p = p->next;
        }
        else
        {
            s->el = q->next->el;
            q = q->next;
        }
        r->next = s;
        r = s;
    }
    if (p->next == NULL) 
    {
        while (q->next != NULL)
        {
            pozicija s = NULL;
            s = (pozicija)malloc(sizeof(struct lista));
            if (s == NULL)
            {
                printf("Neuspjesna alokacija memorije!\n");
                return 1;
            }
            s->next = NULL;
            s->el = q->next->el;
            q = q->next;
            r->next = s;
            r = s;
        }
        
    }
    else 
    {
        while (p->next != NULL)
        {
            pozicija s = NULL;
            s = (pozicija)malloc(sizeof(struct lista));
            if (s == NULL)
            {
                printf("Neuspjesna alokacija memorije!\n");
                return 1;
            }
            s->next = NULL;
            s->el = p->next->el;
            p = p->next;
            r->next = s;
            r = s;
        }
        
    }
    
    return 0;
}
int presjek(pozicija p, pozicija q, pozicija r)
{
    while (p->next != NULL && q->next != NULL) 
    {
        if (p->next->el == q->next->el)
        {
            pozicija s = NULL;
            s = (pozicija)malloc(sizeof(struct lista));
            if (s == NULL)
            {
                printf("Neuspjesna alokacija memorije!\n");
                return 1;
            }
            s->next = NULL;
            s->el = p->next->el;
            p = p->next;
            q = q->next;
            r->next = s;
            r = s;
        }
        else if (p->next->el < q->next->el) 
            p = p->next;
        else
            q = q->next;
    }
    return 0;
}
int unosPrvi(pozicija p)
{
    FILE* fp = NULL;
    fp = fopen("lista1.txt", "r");
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return 1;
    }
    while (!feof(fp))
    {
        pozicija q = NULL;
        q = (pozicija)malloc(sizeof(struct lista));
        if (q == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return 1;
        }
        
        pozicija pret, temp;
        temp = p->next;
        pret = p;
        fscanf(fp, "%d\n", &q->el);
        while (temp != NULL)
        {
            pret = temp;
            temp = temp->next;
        }
        pret->next = q;
        if (temp != NULL)
            q->next = temp;
        else
            q->next = NULL;
    }
    return 0;
}
int unosDrugi(pozicija p)
{
    FILE* fp = NULL;
    fp = fopen("lista2.txt", "r");
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return 1;
    }
    while (!feof(fp))
    {
        pozicija q = NULL;
        q = (pozicija)malloc(sizeof(struct lista));
        if (q == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return 1;
        }
        pozicija pret, temp;
        temp = p->next;
        pret = p;
        fscanf(fp, "%d\n", &q->el);
        while (temp != NULL)
        {
            pret = temp;
            temp = temp->next;
        }
        pret->next = q;
        if (temp != NULL)
            q->next = temp;
        else
            q->next = NULL;
    }
    return 0;
}
int ispis(pozicija p)
{
    while (p != NULL)
    {
        printf("Element liste je: %d\n", p->el);
        p = p->next;
    }
    return 0;
}