#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define MIN 10
#define MAX 100
typedef struct cvor* pozicija;
struct cvor {
    int el;
    pozicija next;
};
int stog(pozicija);
int red(pozicija);
int push(pozicija);
int pop(pozicija);
int pushR(pozicija);
int ispis(pozicija);
int main()
{
    srand(time(NULL));
    struct cvor HeadS;
    HeadS.next = NULL;
    struct cvor HeadR;
    HeadR.next = NULL;
    char c;
    while (1) {
        printf("Unesi 1 za implementaciju stoga, a 2 za implementaciju reda, 0 za izlaz iz programa\n");
        scanf(" %c", &c);
        if (c == '1')
            stog(&HeadS);
        else if (c == '2')
            red(&HeadR);
        else if (c == '0')
            break;
        else
            printf("Nisi unio ispravni broj!\n");
    }


    return 0;
}
int stog(pozicija p)
{
    char c;
    while (1) {
        printf("Unesi N za unos novog elementa stoga, M za micanje postojeceg elementa stoga, I za ispis elemenata stoga, X za izlaz\n");
        scanf(" %c", &c);
        if (c == 'N')
            push(p);
        else if (c == 'M')
            pop(p);
        else if (c == 'I')
            ispis(p->next);
        else if (c == 'X')
            break;
        else
            printf("Nisi unio ispravno slovo!\n");
    }
    return 0;
}
int red(pozicija p)
{
    char c;
    while (1) {
        printf("Unesi N za unos novog elementa reda, M za micanje postojeceg elementa reda, I za ispis elemenata reda, X za izlaz\n");
        scanf(" %c", &c);
        if (c == 'N')
            pushR(p);
        else if (c == 'M')
            pop(p);
        else if (c == 'I')
            ispis(p->next);
        else if (c == 'X')
            break;
        else
            printf("Nisi unio ispravno slovo!\n");
    }
    return 0;
}
int ispis(pozicija p)
{
    while (p != NULL)
    {
        printf("Element je: %d\n", p->el);
        p = p->next;
    }
    return 0;
}
int push(pozicija p)
{ 
    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(struct cvor));
    if (q == NULL)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return 1;
    }
    int broj = (rand() % (MAX - MIN + 1)) + MIN;
    q->el = broj;
    q->next = p->next;
    p->next = q;

    return 0;
}
int pop(pozicija p)
{ 
    pozicija q = NULL;
    if (p->next == NULL)
        printf("Nisi jos dodao niti jedan element!\n");
    else
    {
        printf("Skidamo element:%d\n", p->next->el);
        q = p->next;
        p->next = q->next;
        free(q);
    }
    return 0;
}
int pushR(pozicija p)
{ 
    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(struct cvor));
    if (q == NULL)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return 1;
    }
     pozicija kraj = NULL;
    if (p->next == NULL)
        kraj = p;
    int broj = (rand() % (MAX - MIN + 1)) + MIN;
    q->el = broj;
    q->next = NULL;
    kraj->next = q;
    kraj = q;
    return 0;
}