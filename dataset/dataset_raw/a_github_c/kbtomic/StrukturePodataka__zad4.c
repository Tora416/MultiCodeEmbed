#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct polinom* pozicija;
struct polinom {
    int koeficijent;
    int eksponent;
    pozicija next;
};
int unosPrvi(pozicija);
int unosDrugi(pozicija);
int ispis(pozicija);
int zbroj(pozicija, pozicija, pozicija);
int umnozak(pozicija, pozicija, pozicija);
int main() {
    struct polinom Head1;
    struct polinom Head2;
    struct polinom HeadZ;
    struct polinom HeadM;
    Head1.next = NULL;
    Head2.next = NULL;
    HeadZ.next = NULL;
    HeadM.next = NULL;
    unosPrvi(&Head1);
    unosDrugi(&Head2);
    printf("Ispis prvog polinoma:\n");
    ispis(Head1.next);
    printf("Ispis drugog polinoma:\n");
    ispis(Head2.next);
    zbroj(&Head1, &Head2, &HeadZ);
    printf("Ispis zbrojenog polinoma:\n");
    ispis(HeadZ.next);
    umnozak(&Head1, &Head2, &HeadM);
    printf("Ispis pomnozenih polinoma:\n");
    ispis(HeadM.next);
    return 0;
}
int unosPrvi(pozicija p)
{
    FILE* fp = NULL;
    fp = fopen("pol1.txt", "r");
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return 1;
    }
    while (!feof(fp))
    {
        pozicija q = NULL;
        q = (pozicija)malloc(sizeof(struct polinom));
        if (q == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return 1;
        }
        pozicija pret, temp;
        temp = p->next;
        pret = p;
        fscanf(fp, "%d %d", &q->koeficijent, &q->eksponent);
        while (temp != NULL && temp->eksponent < q->eksponent)
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
    fp = fopen("pol2.txt", "r");
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke!\n");
        return 1;
    }
    while (!feof(fp))
    {
        pozicija q = NULL;
        q = (pozicija)malloc(sizeof(struct polinom));
        if (q == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return 1;
        }
        pozicija pret, temp;
        temp = p->next;
        pret = p;
        fscanf(fp, "%d %d", &q->koeficijent, &q->eksponent);
        while (temp != NULL && temp->eksponent < q->eksponent)
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
    return 0;
}
int ispis(pozicija p)
{
    while (p != NULL)
    {
        printf("Koeficijent je: %d Eksponent je: %d\n", p->koeficijent, p->eksponent);
        p = p->next;
    }
    return 0;
}
int zbroj(pozicija p, pozicija q, pozicija r)
{
    while (p->next != NULL && q->next != NULL)
    {
        pozicija s = NULL;
        s = (pozicija)malloc(sizeof(struct polinom));
        if (s == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return 1;
        }
        s->next = NULL;

        if (p->next->eksponent < q->next->eksponent)
        {
            s->eksponent = p->next->eksponent;
            s->koeficijent = p->next->koeficijent;
            p = p->next;
        }
        else if (p->next->eksponent > q->next->eksponent)
        {
            s->eksponent = q->next->eksponent;
            s->koeficijent = q->next->koeficijent;
            q = q->next;
        }
        else
        {
            s->eksponent = p->next->eksponent;
            s->koeficijent =(p->next->koeficijent + q->next->koeficijent);
            p = p->next;
            q = q->next;
        }
        r->next = s;
        r = s;
    }
    pozicija temp;
    if (p->next == NULL)
        temp = q->next;
    else
        temp = p->next;
    while (temp != NULL)
    {
        pozicija s = NULL;
        s = (pozicija)malloc(sizeof(struct polinom));
        if (s == NULL)
        {
            printf("Neuspjesna alokacija memorije!\n");
            return 1;
        }
        s->next = NULL;
        s->eksponent = temp->eksponent;
        s->koeficijent = temp->koeficijent;
        r->next = s;
        r = s;
        temp = temp->next;
    }
    return 0;
}
int umnozak(pozicija p, pozicija q, pozicija r)
{
    pozicija prvi = p->next;
    pozicija drugi = q->next;
    struct polinom P;
    pozicija s = NULL;
    s = (pozicija)malloc(sizeof(struct polinom));
    if (s == NULL)
    {
        printf("Neuspjesna alokacija memorije!\n");
        return 1;
    }
    s->next = NULL;
    P.next = s;
    while (prvi != NULL)
    {
        drugi = q->next;
        while (drugi != NULL)
        {

            s->koeficijent = prvi->koeficijent * drugi->koeficijent;
            s->eksponent = prvi->eksponent + drugi->eksponent;

            zbroj(&P, r, r);
            drugi = drugi->next;
        }
        prvi = prvi->next;
    }

    return 0;
}